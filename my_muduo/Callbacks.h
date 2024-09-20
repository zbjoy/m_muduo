#pragma once

#include <memory>
#include <functional>

// class m_muduo::net::Buffer;
// class m_muduo::net::TcpConnection;
// class m_muduo::net::Timestamp;


namespace m_muduo
{
    class Timestamp;
    namespace net
    {
        class Buffer;
        class TcpConnection;

        using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
        using ConnectionCallback = std::function<void(const TcpConnectionPtr &)>;
        using CloseCallback = std::function<void(const TcpConnectionPtr &)>;
        using WriteCompleteCallback = std::function<void(const TcpConnectionPtr &)>;

        using MessageCallback = std::function<void(const TcpConnectionPtr &, Buffer*, m_muduo::Timestamp)>;

        using HighWaterMarkCallback = std::function<void (const TcpConnectionPtr&, size_t)>;

    }
}


        // using TcpConnectionPtr = std::shared_ptr<m_muduo::net::TcpConnection>;
        // using ConnectionCallback = std::function<void(const TcpConnectionPtr &)>;
        // using CloseCallback = std::function<void(const TcpConnectionPtr &)>;
        // using WriteCompleteCallback = std::function<void(const TcpConnectionPtr &)>;

        // using MessageCallback = std::function<void(const TcpConnectionPtr &, m_muduo::net::Buffer *, m_muduo::Timestamp)>;