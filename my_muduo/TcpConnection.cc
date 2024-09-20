#include "TcpConnection.h"
#include "Logger.h"
#include "Socket.h"
#include "Channel.h"
#include "EventLoop.h"

#include <functional>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/tcp.h>
#include <sys/socket.h>


static m_muduo::net::EventLoop* CheckLoopNotNull(m_muduo::net::EventLoop* loop)
{
    if (loop == nullptr)
    {
        LOG_FATAL("%s:%s:%d mainLoop is null!!\n", __FILE__, __FUNCTION__, __LINE__);
    }

    return loop;
}

m_muduo::net::TcpConnection::TcpConnection(EventLoop *loop, const std::string &nameArg, int sockfd, const InetAddress &localAddr, const InetAddress &peerAddr)
                        : loop_(CheckLoopNotNull(loop))
                        , name_(nameArg)
                        , state_(kConnecting)
                        , reading_(true)
                        , socket_(new m_muduo::net::Socket(sockfd))
                        , channel_(new m_muduo::net::Channel(loop, sockfd))
                        , localAddr_(localAddr)
                        , peerAddr_(peerAddr)
                        , highWaterMark_(64 * 1024 * 1024) // 64MB
{
    // 给 Channel 设置 相应的 回调函数, poller 给 channel 通知感兴趣的事件结束, channel 会 回调相应的 操作函数
    channel_->setReadCallback(std::bind(&m_muduo::net::TcpConnection::handleRead, this, std::placeholders::_1));
    channel_->setWriteCallback(std::bind(&m_muduo::net::TcpConnection::handleWrite, this));
    channel_->setCloseCallback(std::bind(&m_muduo::net::TcpConnection::handleClose, this));
    channel_->setErrorCallback(std::bind(&m_muduo::net::TcpConnection::handleError, this));

    LOG_INFO("TcpConnection::ctor[%s] at fd = %d\n", name_.c_str(), sockfd);
    socket_->setKeepAlive(true);
}

m_muduo::net::TcpConnection::~TcpConnection()
{
    LOG_INFO("TcpConnection::dtor[%s] at fd = %d state = %d\n", name_.c_str(), channel_->fd(), (int)state_);
}

void m_muduo::net::TcpConnection::shutdown()
{
    if (state_ == kConnected)
    {
        setState(kDisconnecting);
        loop_->runInLoop(std::bind(&m_muduo::net::TcpConnection::shutdownInLoop, this));
    }
}

void m_muduo::net::TcpConnection::connectEstablished()
{
    setState(kConnected);
    channel_->tie(shared_from_this());
    channel_->enableReading(); // 向 poller 注册 channel 的 epollin 事件

    // 新连接建立, 执行回调
    connectionCallback_(shared_from_this());
}

void m_muduo::net::TcpConnection::connectDestroyed()
{
    if (state_ == kConnected)
    {
        setState(kDisconnected);
        channel_->disableAll(); // 把 channel 所有感兴趣的事件 通过 从 poller 中 delete 掉
        connectionCallback_(shared_from_this());
    }
    channel_->remove(); // 把 channel 从 poller 删除掉
}

void m_muduo::net::TcpConnection::send(const std::string &buf)
{
    if (state_ == kConnected)
    {
        if (loop_->isInLoopThread())
        {
            sendInLoop(buf.c_str(), buf.size());
        }
        else
        {
            loop_->runInLoop(std::bind(&m_muduo::net::TcpConnection::sendInLoop, this, buf.c_str(), buf.size()));
        }
    }
}

void m_muduo::net::TcpConnection::handleRead(m_muduo::Timestamp receiveTime)
{
    int saveErrno = 0;
    ssize_t n = inputBuffer_.readFd(channel_->fd(), &saveErrno);
    if (n > 0)
    {
        // 已建立连接的用户, 有可读事件发生, 调用用户传入的回调操作 onMessage
        messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
    }
    else if (n == 0)
    {
        handleClose();
    }
    else
    {
        errno = saveErrno;
        LOG_ERROR("TcpConnection::handleRead");
        handleError();
    }
}

void m_muduo::net::TcpConnection::handleWrite()
{
    if (channel_->isWriting())
    {
        int saveErrno = 0;
        ssize_t n = outputBuffer_.writeFd(channel_->fd(), &saveErrno);
        if (n > 0)
        {
            outputBuffer_.retrieve(n);
            if (outputBuffer_.readableBytes() == 0)
            {
                channel_->disableWriting();
                if (writeCompleteCallback_)
                {
                    // 唤醒 loop_ 对应的 thread 线程, 执行回调
                    loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
                }
                
                if (state_ == kDisconnecting)
                {
                    shutdownInLoop();
                }
            }
        }
        else
        {
            LOG_ERROR("TcpConnection::handleWrite()\n");
        }
    }
    else
    {
        LOG_ERROR("TcpConnection fd = %d is down, no more writing\n", channel_->fd());
    }
}

// Poller ==> Channel::closeCallback ==> TcpConnection::handleClose
void m_muduo::net::TcpConnection::handleClose()
{
    LOG_INFO("fd = %d state = %d\n", channel_->fd(), (int)state_);
    setState(kDisconnected);
    channel_->disableAll();

    TcpConnectionPtr connPtr(shared_from_this());
    connectionCallback_(connPtr); // 执行连接关闭的回调
    closeCallback_(connPtr); // 关闭连接的回调 执行的 是 TcpServer::removeConnection 回调方法
}

void m_muduo::net::TcpConnection::handleError()
{
    int optval;
    socklen_t optlen = sizeof optval;
    int err = 0;
    if (::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
    {
        err = errno;
    }
    else
    {
        err = optval;
    }
    LOG_ERROR("TcpConnection::handleError name: %s - SO_ERROR: %d\n", name_.c_str(), err);
}

/**
 * 发送数据 应用写的快, 内核发送的慢, 所以需要将待发送的数据写入缓冲区, 而且设置水位回调
 */
void m_muduo::net::TcpConnection::sendInLoop(const void *message, size_t len)
{
    ssize_t nwrote = 0;
    size_t remaining = len;
    bool faultError = false;

    // 之前调用过 connection 的 shutdown, 不能再进行发送了
    if (state_ == kDisconnected)
    {
        LOG_ERROR("disconnected, give up writing\n");
        return;
    }

    // 表示 channel 第一次 开始写数据, 而且缓冲区没有待发送数据
    if (!channel_->isWriting() && outputBuffer_.readableBytes() == 0)
    {
        nwrote = ::write(channel_->fd(), message, len);
        if (nwrote >= 0)
        {
            remaining = len - nwrote;
            if (remaining == 0 && writeCompleteCallback_)
            {
                // 一次性发送完数据, 就不用再给 channel 设置 EPOLLOUT 事件了
                loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
            }
        }
        else // wrote < 0
        {
            nwrote = 0;
            if (errno != EWOULDBLOCK) // EWOULDBLOCK 是 指非阻塞没有数据
            {
                LOG_ERROR("TcpConnection::sendInLoop");
                if (errno == EPIPE || errno == ECONNRESET) // SIGPIPE RESET
                {
                    faultError = true;
                    // LOG_ERROR();
                }
            }
        }
    }

    /* 
        说明当前这一次 write 并没有把数据全部发送出去, 剩余的数据需要保存到缓冲区中, 然后给 channel 注册 epollout 事件, poller 发现 tcp的发送缓冲区有空间, 会通知相应的 sock-channel, 调用 writeCallback_ 回调方法

        也就是调用 TcpConnection::handleWrite 方法, 把发送缓冲区中的数据发送完成
    */
    if (!faultError && remaining > 0) 
    {
        // 目前发送缓冲区剩余的待发送数据的长度
        size_t oldLen = outputBuffer_.readableBytes();
        if (oldLen + remaining >= highWaterMark_ && oldLen < highWaterMark_ && highWaterMarkCallback_)
        {
            loop_->queueInLoop(std::bind(highWaterMarkCallback_, shared_from_this(), oldLen + remaining));
        }
        outputBuffer_.append((char*)message + nwrote, remaining);
        if (!channel_->isWriting())
        {
            channel_->enableWriting(); // 这里要注册 channel 的 写事件, 否则 poller 不会给 channel 通知 EPOLLOUT
        }
    }
}

void m_muduo::net::TcpConnection::shutdownInLoop()
{
    if (!channel_->isWriting()) // 说明当前 outputBuffer 中 的数据已经全部发送
    {
        socket_->shutdownWrite(); // 关闭写端
    }
}
