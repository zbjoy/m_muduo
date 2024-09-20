#include "EventLoop.h"
#include "Logger.h"
#include "Poller.h"
#include "Channel.h"

#include <sys/eventfd.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <memory>

namespace m_muduo
{
    namespace net
    {

        // 防止一个线程创建多个 EventLoop 
        __thread m_muduo::net::EventLoop *t_loopInThisThread = 0;

        // 定义默认 Poller IO 复用接口的超时时间
        const int kPollTimeMs = 100000;

        // 创建 wakeupfd, 用来 notify 唤醒 subReactor 处理 新来的 channel
        int createEventfd()
        {
            int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
            if (evtfd < 0)
            {
                LOG_FATAL("func=%s , eventfd error: %d\n", __FUNCTION__, errno);
            }
            return evtfd;
        }

        EventLoop::EventLoop()
                : looping_(false)
                , quit_(false)
                , callingPendingFunctors_(false)
                , threadId_(CurrentThread::tid())
                , poller_(m_muduo::net::Poller::newDefaultPoller(this))
                , wakeupFd_(createEventfd())
                , wakeupChannel_(new m_muduo::net::Channel(this, wakeupFd_))
                , currentActiveChannel_(nullptr)
        {
            LOG_DEBUG("EventLoop created %p in thread %d\n", this, threadId_);
            if (t_loopInThisThread)
            {
                LOG_FATAL("Another EvetLoop %p exists in this thread %d\n", t_loopInThisThread, threadId_);
            }
            else
            {
                t_loopInThisThread = this;
            }

            // 设置 wakeupFd 的 事件类型 以及 发生事件后的 回调操作
            wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this));
            // 每一个 EventLoop 都将监听 wakeupChannel 的 EPOLLIN 读事件
            wakeupChannel_->enableReading();
        }

        EventLoop::~EventLoop()
        {
            wakeupChannel_->disableAll();
            wakeupChannel_->remove();
            ::close(wakeupFd_);
            t_loopInThisThread = nullptr;
        }

        void EventLoop::loop()
        {
            looping_ = true;
            quit_ = false;
        
            LOG_INFO("EventLoop %p start looping\n", this);

            while (!quit_)
            {
                activeChannels_.clear();
                // 监听 两类 fd, 一种是 client 的 fd, 一种是 wakeup 的 fd
                pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);

                for (auto channel : activeChannels_)
                {
                    currentActiveChannel_ = channel;
                    currentActiveChannel_->handleEvent(pollReturnTime_);
                }

                // 执行当前 EventLoop 事件循环需要处理的回调操作
                /**
                 * 
                 * IO 线程: mainLoop 主要 accept 新连接, 返回 fd. (已经连接的 channel 分发给 subLoop)
                 * mainLoop 事先执行一个回调cb (需要 subLoop 执行),  wakeup subLoop 后, 执行下面的 doPendingFunctors 方法, 执行之前 mainLoop 注册的 cb 操作
                 * mainLoop 拿到一个 channel 后会 wakeup 一个 subLoop
                 *  
                 */
                doPendingFunctors();
            }

            LOG_INFO("EventLoop %p stop looping. \n", this);
            looping_ = false;
        }

        // 退出事件循环     1. loop 在 自己的线程中调用 quit    2. 在 非loop 的线程中, 调用 loop 的 quit
        void EventLoop::quit()
        {
            quit_ = true;

            // 如果在其他线程中调用了 quit, eg: 在 subLoop(work thread) 中调用了 mainLoop(IO 线程) 的 quit
            if (!isInLoopThread()) 
            {
                wakeup();
            }
        }

        void EventLoop::runInLoop(Functor cb)
        {
            if (isInLoopThread()) // 在 当前的 loop 线程中, 执行 cb
            {
                cb();
            }
            else // 在 非loop 线程中 执行 cb, 需要唤醒 loop 所在线程, 执行 cb
            {
                queueInLoop(cb);
            }
        }

        void EventLoop::queueInLoop(Functor cb)
        {
            std::unique_lock<std::mutex> lock(mutex_);
            // pendingFunctors_.push_back(cb);
            pendingFunctors_.emplace_back(cb);

            // 唤醒相应的, 需要执行上面回调操作的 loop 线程了
            if (!isInLoopThread() || callingPendingFunctors_)
            {
                wakeup(); // 唤醒 loop 所在线程
            }
        }

        // 用来唤醒 loop 所在的线程, 向 wakeupFd 写一个数据, wakeupChannel 就发生读事件, 当前 loop 线程就会被唤醒
        void EventLoop::wakeup()
        {
            // 向 wakeupFd 写一个数据
            uint64_t one = 1;
            ssize_t n = write(wakeupFd_, &one, sizeof one);
            if (n != sizeof one)
            {
                LOG_ERROR("EventLoop::wakeup() writes %lu bytes instead of 8\n", n);
            }
        }

        void EventLoop::updateChannel(m_muduo::net::Channel *channel)
        {
            poller_->updateChannel(channel);
        }

        void EventLoop::removeChannel(m_muduo::net::Channel *channel)
        {
            poller_->removeChannel(channel);
        }

        bool EventLoop::hasChannel(m_muduo::net::Channel *channel)
        {
            return poller_->hasChannel(channel);
        }

        void EventLoop::handleRead()
        {
            uint64_t one = 1;
            ssize_t n = read(wakeupFd_, &one, sizeof one);
            if (n != sizeof one)
            {
                LOG_ERROR("EventLoop::handleRead() reads %ld bytes instead of 8", n);
            }
        }

        void EventLoop::doPendingFunctors()
        {
            std::vector<Functor> functors;
            callingPendingFunctors_ = true;

            {
                // MutexLockGuard lock(mutex_);
                std::unique_lock<std::mutex> lock(mutex_);
                functors.swap(pendingFunctors_);
            }

            for (const Functor& functor : functors)
            {
                functor(); // 执行 当前 loop 需要执行的回调操作
            }

            callingPendingFunctors_ = false;
        
        }
    }
}
