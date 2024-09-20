#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"
#include "EventLoop.h"

#include <memory>

m_muduo::net::EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop, const std::string &nameArg)
                                : baseLoop_(baseLoop)
                                , name_(nameArg)
                                , started_(false)
                                , numThreads_(0)
                                , next_(0)
{

}

m_muduo::net::EventLoopThreadPool::~EventLoopThreadPool()
{
}

void m_muduo::net::EventLoopThreadPool::start(const ThreadInitCallBack &cb)
{
    started_ = true;

    for (int i = 0; i < numThreads_; ++i)
    {
        char buf[name_.size() + 32] = { 0 };
        snprintf(buf, sizeof buf, "%s%d", name_.c_str(), i);
        EventLoopThread* t = new EventLoopThread(cb, buf);
        threads_.push_back(std::unique_ptr<EventLoopThread>(t));
        loops_.push_back(t->startLoop()); // 底层创建线程, 绑定一个新的 EventLoop, 并返回该 loop 的地址
    }

    // 整个服务端只有一个线程运行着 baseloop
    if (numThreads_ == 0 && cb)
    {
        cb(baseLoop_);
    }
}

m_muduo::net::EventLoop *m_muduo::net::EventLoopThreadPool::getNextLoop()
{
    EventLoop* loop = baseLoop_;

    if (!loops_.empty()) // 通过轮询获取下一个处理事件的 loop
    {
        loop = loops_[next_];
        ++next_;
        if (next_ >= loops_.size())
        {
            next_ = 0;
        }
    }

    return loop;
}

std::vector<m_muduo::net::EventLoop *> m_muduo::net::EventLoopThreadPool::getAllLoops()
{
    if (loops_.empty())
    {
        return std::vector<m_muduo::net::EventLoop*>(1, baseLoop_);
    }
    else
    {
        return loops_ ;
    }

    // return std::vector<EventLoop *>();
}
