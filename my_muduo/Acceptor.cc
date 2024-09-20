#include "Acceptor.h"
#include "Logger.h"
#include "Socket.h"
#include "InetAddress.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

static int createNoneblocking()
{
    // int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if (sockfd < 0)
    {
        LOG_FATAL("%s:%s:%d listen socket create err: %d\n", __FILE__, __FUNCTION__, __LINE__, errno);
    }
}

m_muduo::net::Acceptor::Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport)
                    : loop_(loop)
                    , acceptSocket_(createNoneblocking())
                    , acceptChannel_(loop, acceptSocket_.fd())
                    , listenning_(false)
{
    acceptSocket_.setReuseAddr(true);
    acceptSocket_.setReusePort(true);
    acceptSocket_.bindAddress(listenAddr); // bind

    // TcpServer::start()  会启动   Acceptor.listen   有新用户连接, 要执行一个回调 (connfd ==> channel)
    // baseLoop ==> acceptChannel_(listenfd) ==> 
    acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead, this));

}

m_muduo::net::Acceptor::~Acceptor()
{
    acceptChannel_.disableAll();
    acceptChannel_.remove();
}

void m_muduo::net::Acceptor::listen()
{
    listenning_ = true;
    acceptSocket_.listen(); // listen
    acceptChannel_.enableReading(); // acceptChannel_ ==> Poller
}

// listenfd 有 事件发生了, 就是有 新用户 连接了
void m_muduo::net::Acceptor::handleRead()
{
    // InetAddress peerAddr;
    InetAddress peerAddr;
    int connfd = acceptSocket_.accept(&peerAddr);
    if (connfd >= 0)
    {
        if (newConnectionCallback_)
        {
            newConnectionCallback_(connfd, peerAddr); // 轮询找到 subLoop, 唤醒, 分发当前的新客户端的 Channel
        }
        else
        {
            ::close(connfd);
        }
    }
    else
    {
        LOG_ERROR("%s:%s:%d accept error: %d\n", __FILE__, __FUNCTION__, __LINE__, errno);
        if (errno == EMFILE)
        {
            LOG_ERROR("%s:%s:%d sockfd reached limit error!!\n", __FILE__, __FUNCTION__, __LINE__);
        }
    }
}
