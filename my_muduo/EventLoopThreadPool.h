#pragma once

#include "nocopyable.h"

#include <functional>
#include <string>
#include <vector>
#include <memory>

namespace m_muduo
{
    namespace net
    {
        class EventLoop;
        class EventLoopThread;

        class EventLoopThreadPool : m_muduo::nocopyable
        {
        public:
            using ThreadInitCallBack = std::function<void (EventLoop*)>;

            EventLoopThreadPool(EventLoop* baseLoop, const std::string& nameArg);
            ~EventLoopThreadPool();

            void setThreadNum(int numThreads)
            {
                numThreads_ = numThreads;
            }

            void start(const ThreadInitCallBack& cb = ThreadInitCallBack());

            // 如果工作在多线程, baseLoop 以轮询的方式分配 channel 给 subLoop
            EventLoop* getNextLoop();

            std::vector<EventLoop*> getAllLoops();

            bool started() const
            {
                return started_;
            }

            const std::string name() const
            {
                return name_;
            }

        private:
            EventLoop* baseLoop_; // EventLoop loop;
        
            std::string name_;
            bool started_;
            int numThreads_;
            int next_;
            std::vector<std::unique_ptr<EventLoopThread>> threads_;
            std::vector<EventLoop*> loops_;
        };
    }
}
