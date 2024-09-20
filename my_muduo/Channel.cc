#include "Channel.h"

#include "Logger.h"
#include "EventLoop.h"

#include <sys/epoll.h>

const int m_muduo::net::Channel::kNoneEvent = 0;
const int m_muduo::net::Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int m_muduo::net::Channel::kWriteEvent = EPOLLOUT;

m_muduo::net::Channel::Channel(EventLoop *loop, int fd) 
                    : loop_(loop)
                    , fd_(fd)
                    , events_(0)
                    , revents_(0)
                    , index_(-1)
                    , tied_(false)
{
    
}

m_muduo::net::Channel::~Channel() 
{

}


void m_muduo::net::Channel::tie(const std::shared_ptr<void>& obj)
{
    tie_ = obj;

    tied_ = true;
}


/**
 * 当改变 Channel 所表示的 fd 的 events 事件后, update 负责在 poller 里面更改 fd 相应的事件 epoll_ctl
 * EventLoop ==> ChannnelList  Poller
 */
void m_muduo::net::Channel::update()
{
    // 通过 channel 所属的 EventLoop, 调用 poller 的 相应方法注册 fd 的 events 事件
    loop_->updateChannel(this);

}


// 在 Channel 所属的 EventLoop 中, 把当前的 Channel 删除掉
void m_muduo::net::Channel::remove()
{
    loop_->removeChannel(this);
}

// fd 得到 Poller 通知以后, 处理事件
void m_muduo::net::Channel::handleEvent(Timestamp receiveTime)
{
    if (tied_)
    {
        std::shared_ptr<void> guard = tie_.lock();
        if (guard)
        {
            handleEventWithGuard(receiveTime);
        }
    }
    else
    {
        handleEventWithGuard(receiveTime);
    }
}

// 根据 Poller 通知的 Channel 发生的具体事件, 由 Channel 负责调用具体的回调操作
void m_muduo::net::Channel::handleEventWithGuard(Timestamp receiveTime)
{
    LOG_INFO("channel handleEvent revents: %d", revents_);
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        if (closeCallback_)
        {
            closeCallback_();
        }
    }

    if (revents_ & EPOLLERR)
    {
        if (errorCallback_)
        {
            errorCallback_();
        }
    }

    if (revents_ & EPOLLIN)
    {
        if (readCallback_)
        {
            readCallback_(receiveTime);
        }
    }

    if (revents_ & EPOLLOUT)
    {
        if (writeCallback_)
        {
            writeCallback_();
        }
    }
}
