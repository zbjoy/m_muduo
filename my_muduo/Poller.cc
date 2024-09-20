#include "Poller.h"

#include "Channel.h"

m_muduo::net::Poller::Poller(EventLoop *loop) 
                : ownerLoop(loop)
{
}

m_muduo::net::Poller::~Poller()
{
}

bool m_muduo::net::Poller::hasChannel(m_muduo::net::Channel *channel) const
{
    auto it = channels_.find(channel->fd());
    // if (it == channels_.end())
    // {
// 
    // }
    // return false;
    return it != channels_.end() && it->second == channel;
}


