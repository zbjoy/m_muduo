#include "Thread.h"

#include "CurrentThread.h"

#include <semaphore.h>

// std::atomic_int m_muduo::Thread::Thread::numCreated_ = 0;
std::atomic_int m_muduo::Thread::numCreated_(0);

m_muduo::Thread::Thread(ThreadFunc func, const std::string &name)
            : started_(false)
            , joined_(false)
            , tid_(0)
            , func_(std::move(func))
            , name_(name)
{
    setDefaultName();
}

m_muduo::Thread::~Thread()
{
    if (started_ && !joined_)
    {
        thread_->detach(); // thread 类 提供的 设置分离线程的方法
    }
}

// 一个 thread 对象, 记录的就是一个新线程的详细信息
void m_muduo::Thread::start()
{
    started_ = true;
    sem_t sem;
    sem_init(&sem, false, 0);

    // 开启 线程
    thread_ = std::shared_ptr<std::thread>(new std::thread([&](){
        // 获取线程的 tid 值
        tid_ = CurrentThread::tid();

        sem_post(&sem);

        // 开启一个新线程, 专门执行 该线程函数
        func_(); 
    }));

    // 这里必须等待获取上面新创建的线程的 tid 值
    sem_wait(&sem);
}

void m_muduo::Thread::join()
{
    joined_ = true;
    thread_->join();
}

void m_muduo::Thread::setDefaultName()
{
    int num = ++numCreated_;

    if (name_.empty())
    {
        char buf[32] = { 0 };
        snprintf(buf, sizeof buf, "Thread%d", num);
        name_ = buf;
    }
}
