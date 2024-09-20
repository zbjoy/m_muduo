#pragma once

#include "nocopyable.h"
#include "Thread.h"

#include <functional>
#include <mutex>
#include <condition_variable>
#include <string>

namespace m_muduo
{
    namespace net
    {
        class EventLoop;

        class EventLoopThread : m_muduo::nocopyable
        {
        public:
            using ThreadInitCallback = std::function<void (EventLoop*)>;
            
            EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(),
                        const std::string& name = std::string()); 
            ~EventLoopThread();

            EventLoop* startLoop();
        private:

            void threadFunc();

            EventLoop* loop_;
            bool exiting_;
            m_muduo::Thread thread_;
            std::mutex mutex_;
            std::condition_variable cond_;
            ThreadInitCallback callback_;

        };
    }
}
