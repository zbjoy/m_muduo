#include "EPollPoller.h"

#include "Logger.h"
#include "Channel.h"

#include <unistd.h>
#include <errno.h>
#include <strings.h>

const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;

m_muduo::net::EPollPoller::EPollPoller(EventLoop *loop)
                        : m_muduo::net::Poller(loop)
                        , epollfd_(::epoll_create1(EPOLL_CLOEXEC))
                        , events_(kInitEventListSize)
{
    if (epollfd_ < 0)
    {
        LOG_FATAL("epoll_create error: %d \n", errno);
    }
}

m_muduo::net::EPollPoller::~EPollPoller()
{
    ::close(epollfd_);
}

m_muduo::Timestamp m_muduo::net::EPollPoller::poll(int timeoutMs, ChannelList *activeChannels)
{
    LOG_INFO("func=%s => fd total count: %lu\n", __FUNCTION__, channels_.size());

    int numEvents = ::epoll_wait(epollfd_, &*events_.begin(), static_cast<int>(events_.size()), timeoutMs);

    int saveErrno = errno;
    m_muduo::Timestamp now(m_muduo::Timestamp::now());

    if (numEvents > 0)
    {
        LOG_INFO("%d events happened\n", numEvents);
        fillActiveChannels(numEvents, activeChannels);
        if (numEvents == events_.size())
        {
            events_.resize(events_.size() * 2);
        }
    }
    else if (numEvents == 0)
    {
        LOG_DEBUG("%s timeout\n", __FUNCTION__);
    }
    else
    {
        if (saveErrno != EINTR)
        {
            errno = saveErrno;
            // LOG_ERROR("EPollPoller::poll() error!!(func: %s)", __FUNCTION__);
            LOG_ERROR("EPollPoller::poll() error!!");
        }
    }
    return now;
}

void m_muduo::net::EPollPoller::updateChannel(m_muduo::net::Channel *channel)
{
    const int index = channel->index();
    LOG_INFO("func=%s => fd = %d events= %d index = %d\n", __FUNCTION__, channel->fd(), channel->events(), index);

    if (index == kNew || index == kDeleted)
    {
        if (index == kNew)
        {
            if (index == kNew)
            {
                int fd = channel->fd();
                channels_[fd] = channel;
            }

            channel->set_index(kAdded);
            update(EPOLL_CTL_ADD, channel);
        }
        else // channel 已经 在 Poller 注册了
        {
            int fd = channel->fd();
            if (channel->isNoneEvent())
            {
                update(EPOLL_CTL_DEL, channel);
                channel->set_index(kDeleted);
            }
            else
            {
                update(EPOLL_CTL_MOD, channel);
            }
        }
    }
}

// 从 Poller 中 删除 channel
void m_muduo::net::EPollPoller::removeChannel(m_muduo::net::Channel *channel)
{
    int fd = channel->fd();
    channels_.erase(fd);

    LOG_INFO("func=%s => fd=%d\n", __FUNCTION__, fd);

    int index = channel->index();
    if (index == kAdded)
    {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->set_index(kNew);
}

// 填写活跃的连接
void m_muduo::net::EPollPoller::fillActiveChannels(int numsEvents, ChannelList *activeChannels) const
{
    for (int i = 0; i < numsEvents; ++i)
    {
        m_muduo::net::Channel* channel = static_cast<m_muduo::net::Channel*>(events_[i].data.ptr);
        channel->set_revents(events_[i].events);
        // EventLoop 拿到 Poller 返回的 所有发生事件 的 channel 列表
        activeChannels->push_back(channel);
    }
}

// 更新 channel 通道 epoll_ctl add/mod/del
void m_muduo::net::EPollPoller::update(int operation, m_muduo::net::Channel *channel)
{
    epoll_event event;
    bzero(&event, sizeof event);

    int fd = channel->fd();

    event.events = channel->events();
    event.data.ptr = channel;

    if (::epoll_ctl(epollfd_, operation, fd, &event) < 0)
    {
        if (operation == EPOLL_CTL_DEL)
        {
            LOG_ERROR("epoll_ctl del error: %d\n", errno);
        }
        else
        {
            LOG_FATAL("epoll_ctl add/mod error: %d\n", errno);
        }
    }
}
