#pragma once

#include "Poller.h"

#include <vector>
#include <sys/epoll.h>

namespace m_muduo
{
    namespace net
    {
        class EPollPoller : public m_muduo::net::Poller
        {
        public:
            EPollPoller(EventLoop* loop);
            ~EPollPoller() override;

            
            class Channel;

            // 重写 基类 Poller 的 抽象方法
            m_muduo::Timestamp poll(int timeoutMs, ChannelList* activeChannels) override;
            void updateChannel(m_muduo::net::Channel* channel) override;
            void removeChannel(m_muduo::net::Channel* channel) override;

        private:
            static const int kInitEventListSize = 16;

            // 填写活跃的连接
            void fillActiveChannels(int numsEvents, ChannelList* activeChannels) const;
            // 更新 Channel 通道
            void update(int operation, m_muduo::net::Channel* channel);
            

            using EventList = std::vector<epoll_event>;

            int epollfd_;
            EventList events_;
        };
    }
}
