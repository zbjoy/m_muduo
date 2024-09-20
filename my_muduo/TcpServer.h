#pragma once

#include "EventLoop.h"
#include "Acceptor.h"
#include "InetAddress.h"
#include "nocopyable.h"
#include "EventLoopThreadPool.h"
#include "Callbacks.h"
#include "TcpConnection.h"
#include "Buffer.h"

#include <functional>
#include <string>
#include <memory>
#include <atomic>
#include <unordered_map>

// 对外的服务器编程使用的类
namespace m_muduo
{

    namespace net
    {

        /**
         * 用户使用muduo编写服务器程序
         */

        // 对外的服务器使用的类
        class TcpServer : m_muduo::nocopyable
        {
        public:
            using ThreadInitCallback = std::function<void (m_muduo::net::EventLoop*)>;

            enum Option
            {
                kNoReusePort,
                kReusePort,
            };

            TcpServer(m_muduo::net::EventLoop* loop_, const m_muduo::net::InetAddress& listenAddr, const std::string& nameArg,  Option option = kNoReusePort);
            ~TcpServer();

            void setThreadInitCallback(const ThreadInitCallback& cb)
            {
                threadInitCallback_ = cb;
            }

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

            // 设置底层 subLoop 的 个数
            void setThreadNum(int numThreads);

            // 开启服务器监听
            void start();

        private:
            void newConnection(int sockfd, const m_muduo::net::InetAddress& peerAddr);
            void removeConnection(const TcpConnectionPtr& conn);
            void removeConnectionInLoop(const TcpConnectionPtr& conn);


            using ConnectionMap = std::unordered_map<std::string, TcpConnectionPtr>;

            m_muduo::net::EventLoop* loop_; // baseLoop 用户定义的 loop
            const std::string ipPort_;
            const std::string name_;

            std::unique_ptr<m_muduo::net::Acceptor> acceptor_; // 运行在mainLoop, 任务就是监听新连接事件

            std::shared_ptr<m_muduo::net::EventLoopThreadPool> threadPool_; // one loop per thread
        
            ConnectionCallback connectionCallback_; // 有新连接时的回调
            MessageCallback messageCallback_; // 有读写消息时的回调
            WriteCompleteCallback writeCompleteCallback_; // 消息发送完成后的回调

            ThreadInitCallback threadInitCallback_; // loop 线程初始化的回调
            std::atomic_int started_;

            int nextConnId_;
            ConnectionMap connections_; // 保存所有的连接
        };

    }

}
