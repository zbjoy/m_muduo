#pragma once

#include "nocopyable.h"
#include "Socket.h"
#include "Channel.h"

#include <functional>

namespace m_muduo
{
    namespace net
    {
        class EventLoop;
        class InetAddress;

        class Acceptor : m_muduo::nocopyable
        {
        public:
            using NewConnectionCallback = std::function<void (int sockfd, const InetAddress&)>;

            Acceptor(EventLoop* loop, const InetAddress& listenAddr, bool reuseport);
            ~Acceptor();

            void setNewConnectionCallback(const NewConnectionCallback& cb)
            {
                newConnectionCallback_ = cb;
            }

            bool listenning() const 
            {
                return listenning_;
            }

            void listen();

        private:
            void handleRead();

            EventLoop* loop_; // Acceptor 用的就是用户定义的那个 baseLoop, 也称作 mainLoop
            Socket acceptSocket_;
            Channel acceptChannel_;
        
            NewConnectionCallback newConnectionCallback_;
            bool listenning_;
        };
    }
}
