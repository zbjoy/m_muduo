#pragma once

#include <functional>
#include <vector>
#include <atomic>
#include <memory>
#include <mutex>

#include "nocopyable.h"
#include "Timestamp.h"
#include "CurrentThread.h"

namespace m_muduo
{
    namespace net
    {
        class Channel;
        class Poller;
        
        // 事件循环类, 主要为 Channel 与 Poller (epoll 的 抽象)
        class EventLoop : m_muduo::nocopyable
        {
        public:
            using Functor = std::function<void()>;

            EventLoop();
            ~EventLoop();

            // 开启事件循环
            void loop();

            // 退出事件循环
            void quit();
        

            m_muduo::Timestamp pollReturnTime() const
            {
                return pollReturnTime_;
            }

            // 在 当前 loop 中 执行 cb
            void runInLoop(Functor cb);
            // 把 cb 放入 队列, 唤醒 loop 所在的线程, 执行 cb
            void queueInLoop(Functor cb);

            // 用来唤醒 loop 所在的线程
            void wakeup();

            // EventLoop 的 方法 ==> Poller 的 方法
            void updateChannel(m_muduo::net::Channel* channel);
            void removeChannel(m_muduo::net::Channel* channel);
            bool hasChannel(m_muduo::net::Channel* channel);

            // 判断 EventLoop 对象 是否在自己的线程中
            bool isInLoopThread() const
            {
                return threadId_ == CurrentThread::tid();
            }
        private:

            void handleRead(); // wake up
            void doPendingFunctors(); // 执行回调

            using ChannelList = std::vector<m_muduo::net::Channel*>;
            
            std::atomic_bool looping_; // 原子操作的, 通过 CAS 实现
            std::atomic_bool quit_; // 标志退出 loop 主循环


            const pid_t threadId_; // 记录当前 loop 所在 线程id

            m_muduo::Timestamp pollReturnTime_; // Poller 返回发生事件的 channels 的时间点
            std::unique_ptr<m_muduo::net::Poller> poller_;

            int wakeupFd_; // 主要作用: 当 mainLoop 获取一个新用户的 channel, 通过 轮询算法 选择一个 subloop, 通过该成员通知唤醒 subloop 处理 channel 
            std::unique_ptr<m_muduo::net::Channel> wakeupChannel_;

            ChannelList activeChannels_;
            m_muduo::net::Channel* currentActiveChannel_;


            std::atomic_bool callingPendingFunctors_; // 标识当前 loop 是否有需要执行的回调操作
            std::vector<Functor> pendingFunctors_; // 存储 loop 需要执行的所有回调操作
            std::mutex mutex_; // 互斥锁用来保护上面容器 vector 的线程安全操作
        };
    }
}
