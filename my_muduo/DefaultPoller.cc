#include "Poller.h"
#include "EPollPoller.h"

#include <stdlib.h>

m_muduo::net::Poller* m_muduo::net::Poller::newDefaultPoller(m_muduo::net::EventLoop* loop)
{
    // 默认使用 epoll
    if (::getenv("MUDUO_USE_POLL"))
    {
        // TODO: 生成 POLL 实例
        return nullptr;
    }
    else
    {
        // TODO: 生成 EPOLL 实例
        // return nullptr;
        return new m_muduo::net::EPollPoller(loop);
    }
}
