#include "EventLoopThread.h"
#include "EventLoop.h"

m_muduo::net::EventLoopThread::EventLoopThread(const ThreadInitCallback &cb, const std::string &name)
    : loop_(nullptr), exiting_(false), thread_(std::bind(&m_muduo::net::EventLoopThread::threadFunc, this), name), mutex_(), cond_(), callback_(cb)
{
}

m_muduo::net::EventLoopThread::~EventLoopThread()
{
    exiting_ = true;
    if (loop_ != nullptr)
    {
        loop_->quit();
        thread_.join();
    }
}

m_muduo::net::EventLoop *m_muduo::net::EventLoopThread::startLoop()
{
    thread_.start(); // 启动底层的新线程

    m_muduo::net::EventLoop* loop = nullptr;

    {
        std::unique_lock<std::mutex> lock(mutex_);
        
        while (loop_ == nullptr)
        {
            cond_.wait(lock);
        }
        loop = loop_;
    }
    return loop;
}

// 在 单独的 新线程中 运行
void m_muduo::net::EventLoopThread::threadFunc()
{
    m_muduo::net::EventLoop loop; // 创建一个独立的 EventLoop, 和上面的线程是 一一 对应的, one loop per thread

    if (callback_)
    {
        callback_(&loop);
    }

    {
        std::unique_lock<std::mutex> lock(mutex_);
        loop_ = &loop;
        cond_.notify_one();
    }

    loop.loop(); //EventLoop loop ==> Poller.poll()

    std::unique_lock<std::mutex> lock(mutex_);
    loop_ = nullptr;
}
