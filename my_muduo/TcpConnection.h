#pragma once

#include "nocopyable.h"
#include "InetAddress.h"
#include "Callbacks.h"
#include "Buffer.h"
#include "Timestamp.h"

#include <memory>
#include <string>
#include <atomic>
#include <string>

namespace m_muduo
{
    namespace net
    {
        class Channel;
        class EventLoop;
        class Socket;


        /**
         * 
         * TcpServer ==> Acceptor ==> 有一个新用户连接, 通过 accept 函数拿到 connfd
         * ==> TcpConnection 设置回调 ==> Channel ==> Poller ==> Channel的回调操作
         * 
         */
        class TcpConnection : m_muduo::nocopyable, public std::enable_shared_from_this<TcpConnection>
        {
        public:
            TcpConnection(EventLoop* loop, const std::string& name, int sockfd, const InetAddress& localAddr, const InetAddress& peerAddr);
            ~TcpConnection();

            EventLoop* getLoop() const
            {
                return loop_;
            }

            const std::string& name() const
            {
                return name_;
            }

            const InetAddress& localAddress() const 
            {
                return localAddr_;
            }

            const InetAddress& peerAddress() const
            {
                return peerAddr_;
            }

            bool connected() const
            {
                return state_ == kConnected;
            }

            // 发送数据
            void send(const std::string& buf);
            // void send(const void* message, int len);
            // 关闭连接
            void shutdown();

            void setConnectionCallback(const ConnectionCallback& cb)
            {
                connectionCallback_ = cb;
            }

            void setMessageCallback(const MessageCallback& cb)
            {
                messageCallback_ = cb;
            }

            void setWriteCompleteCallback(const WriteCompleteCallback& cb)
            {
                writeCompleteCallback_ = cb;
            }

            void setHighWaterMarkCallback(const HighWaterMarkCallback& cb, size_t hightWaterMark)
            {
                highWaterMarkCallback_ = cb;
                highWaterMark_ = hightWaterMark;
            }

            void setCloseCallback(const CloseCallback& cb)
            {
                closeCallback_ = cb;
            }

            // 连接建立
            void connectEstablished();
            // 连接销毁
            void connectDestroyed();



        private:


            void handleRead(m_muduo::Timestamp receiveTime);
            void handleWrite();
            void handleClose();
            void handleError();

            void sendInLoop(const void* message, size_t len);

            // void shutdown();
            void shutdownInLoop();

            enum StateE
            {
                kDisconnected,
                kConnecting,
                kConnected,
                kDisconnecting,
            };

            void setState(StateE state)
            {
                state_ = state;
            }

            std::atomic_int state_;
            bool reading_;

            std::unique_ptr<Socket> socket_;
            std::unique_ptr<Channel> channel_;

            const m_muduo::net::InetAddress localAddr_;
            const m_muduo::net::InetAddress peerAddr_;

            ConnectionCallback connectionCallback_;
            MessageCallback messageCallback_;
            WriteCompleteCallback writeCompleteCallback_;
            HighWaterMarkCallback highWaterMarkCallback_;
            CloseCallback closeCallback_;

            size_t highWaterMark_;

            Buffer inputBuffer_; // 接收数据的缓冲区
            Buffer outputBuffer_; // 发送数据的缓冲区

            EventLoop* loop_; // 不是 baseLoop(mainLoop), 因为 TcpConnection 都是在 subLoop 中 管理的
            const std::string name_;

        };
    }
}
