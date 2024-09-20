#include "TcpServer.h"
#include "Logger.h"
#include "TcpConnection.h"

#include <strings.h>
#include <functional>

static m_muduo::net::EventLoop* CheckLoopNotNull(m_muduo::net::EventLoop* loop)
{
    if (loop == nullptr)
    {
        LOG_FATAL("%s:%s:%d mainLoop is null!!\n", __FILE__, __FUNCTION__, __LINE__);
    }

    return loop;
}

m_muduo::net::TcpServer::TcpServer(m_muduo::net::EventLoop *loop, const m_muduo::net::InetAddress &listenAddr, const std::string &nameArg, Option option) : loop_(CheckLoopNotNull(loop)), ipPort_(listenAddr.toIpPort()), name_(nameArg), acceptor_(new m_muduo::net::Acceptor(loop, listenAddr, true)), threadPool_(new m_muduo::net::EventLoopThreadPool(loop, name_)), connectionCallback_(), messageCallback_(), nextConnId_(1), started_(0)
{
    // 当有新用户连接时, 会执行 TcpServer::newConnection 回调
    acceptor_->setNewConnectionCallback(std::bind(&m_muduo::net::TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2));

}

m_muduo::net::TcpServer::~TcpServer()
{
    for (auto& item : connections_)
    {
        // 这个 局部的 shared_ptr 智能指针对象, 出右括号, 可以自动释放 new 出来的 TcpConnection 对象资源了
        TcpConnectionPtr conn(item.second); 
        item.second.reset();

        // 销毁连接
        conn->getLoop()->runInLoop(
            std::bind(&m_muduo::net::TcpConnection::connectDestroyed, conn)
        );
    }
}

// 有一个 新的客户端的连接, acceptor 会 执行 这个回调
void m_muduo::net::TcpServer::newConnection(int sockfd, const m_muduo::net::InetAddress &peerAddr)
{
    // 轮询算法, 选择一个 subLoop, 来管理 channel
    m_muduo::net::EventLoop* ioLoop = threadPool_->getNextLoop();
    char buf[64] = { 0 };
    snprintf(buf, sizeof buf, "-%s#%d", ipPort_.c_str(), nextConnId_);
    ++nextConnId_;
    std::string connName = name_ + buf;

    LOG_INFO("TcpServer::newConnection [%s] - new connection [%s] from %s\n", name_.c_str(), connName.c_str(), peerAddr.toIpPort().c_str());

    // 通过 sockfd 获取其绑定的本机的ip地址和端口信息
    sockaddr_in local;
    ::bzero(&local, sizeof local);
    socklen_t addrLen = sizeof local;
    if (::getsockname(sockfd, (sockaddr*)&local, &addrLen))
    {
        LOG_ERROR("sockets::getLocalAddr\n");
    }

    m_muduo::net::InetAddress localAddr(local);

    // 根据连接成功的 sockfd 创建 TcpConnection 连接对象
    TcpConnectionPtr conn(new m_muduo::net::TcpConnection(
                                        ioLoop,
                                        connName,
                                        sockfd, // Socket Channel
                                        localAddr,
                                        peerAddr
                                    ));

    connections_[connName] = conn;
    // 下面的回调是 用户 设置 给 TcpServer ==> TcpConnection ==> Channel ==> Poller ==> notify channel 调用回调
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);

    // 设置了如何关闭连接的回调 用户会调用 conn->shutdown
    conn->setCloseCallback(
        std::bind(&m_muduo::net::TcpServer::removeConnection, this, std::placeholders::_1)
    );

    // 直接调用 TcpConnection::connectEstablished
    ioLoop->runInLoop(std::bind(&m_muduo::net::TcpConnection::connectEstablished, conn));
}

void m_muduo::net::TcpServer::setThreadNum(int numThreads)
{
    threadPool_->setThreadNum(numThreads);
}

void m_muduo::net::TcpServer::start()
{
    if (started_++ == 0) // 防止一个 TcpServer 对象 被 多次 start
    {
        threadPool_->start(threadInitCallback_); // 启动底层的 loop 线程池
        loop_->runInLoop(std::bind(&m_muduo::net::Acceptor::listen, acceptor_.get()));
    }
}

void m_muduo::net::TcpServer::removeConnection(const TcpConnectionPtr &conn)
{
    loop_->runInLoop(
        std::bind(&m_muduo::net::TcpServer::removeConnectionInLoop, this, conn)
    );
}

void m_muduo::net::TcpServer::removeConnectionInLoop(const TcpConnectionPtr &conn)
{
    LOG_INFO("TcpServer::removeConnectionInLoop [%s] - connection %s\n", name_.c_str(), conn->name().c_str());

    connections_.erase(conn->name());

    m_muduo::net::EventLoop* ioLoop = conn->getLoop();
    ioLoop->queueInLoop(
        std::bind(&m_muduo::net::TcpConnection::connectDestroyed, conn)
    );
}
