#pragma once

#include "nocopyable.h"
#include "Timestamp.h"

#include <vector>
#include <unordered_map>

namespace m_muduo
{
    namespace net
    {
        class Channel;
        class EventLoop;

        // muduo 库中 多路事件分发器的核心 io 模块
        class Poller : m_muduo::nocopyable
        {
        public:
            using ChannelList = std::vector<m_muduo::net::Channel*>;

            Poller(EventLoop* loop);
            virtual ~Poller();

            // 保留统一的 给所有 IO 复用的接口
            virtual m_muduo::Timestamp poll(int timeoutMs, ChannelList* activeChannels) = 0;

            virtual void updateChannel(m_muduo::net::Channel* channel) = 0;
            virtual void removeChannel(m_muduo::net::Channel* channel) = 0;


            // 判断参数 channel 是否在当前 Poller 当中
            bool hasChannel(m_muduo::net::Channel* channel) const;

            // EventLoop 事件循环 可以通过该接口获取默认的 IO 复用 的接口具体实现
            static Poller* newDefaultPoller(EventLoop* loop);


        protected:
            // map 的 key 为 sockfd, value 为 sockfd 所属的 Channel 通道类型
            using ChannelMap = std::unordered_map<int, m_muduo::net::Channel*>;
            ChannelMap channels_;

        private:
            EventLoop* ownerLoop; // 定义了 Poller 所属的事件循环 EventLoop
        };
    }
}
