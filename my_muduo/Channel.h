#pragma once

#include <iostream>
#include <functional>
#include <memory>

#include "nocopyable.h"
#include "Timestamp.h"

namespace m_muduo
{
    class Timestamp;
    namespace net
    {
        class EventLoop;
        
        // Channel 理解为 通道, 封装了 sockfd 和 其感兴趣的 event, eg:  EPOLLIN, EPOLLOUT 事件
        //    并且绑定了 poller 监听返回的具体事件
        class Channel : m_muduo::nocopyable
        {
        public:
            // typedef std::function<void()> EventCallback;
            using EventCallback = std::function<void()>;
            using ReadEventCallback = std::function<void(Timestamp)>;

            Channel(EventLoop* loop, int fd);
            ~Channel();

            // fd 得到 poller 之后 处理事件 : 调用相应的方法
            void handleEvent(Timestamp receiveTime);

            // 设置回调函数对象
            void setReadCallback(ReadEventCallback cb)
            {
                // readCallback_ = cb;
                readCallback_ = std::move(cb);
            }

            void setWriteCallback(EventCallback cb)
            {
                writeCallback_ = std::move(cb);
            }

            void setCloseCallback(EventCallback cb)
            {
                closeCallback_ = std::move(cb);
            }
            
            void setErrorCallback(EventCallback cb)
            {
                errorCallback_ = std::move(cb);
            }

            // 防止当 Channel 被手动 remove 掉, Channel 还在执行回调操作 (当一个 TcpConnection 新连接创建的时候, TcpConnection ==> Channel)
            void tie(const std::shared_ptr<void>&);

            int fd() const
            {
                return fd_;
            }

            int events() const
            {
                return events_;
            }

            // int set_revents(int revt)
            void set_revents(int revt)
            {
                revents_ = revt;
            }

            // 设置 fd 相应的事件状态
            void enableReading()
            {
                events_ |= kReadEvent;
                update();
            }

            void disableReading()
            {
                events_ &= ~kReadEvent;
                update();
            }

            void enableWriting()
            {
                events_ |= kWriteEvent;
                update();
            }

            void disableWriting()
            {
                events_ &= ~kWriteEvent;
                update();
            }

            void disableAll()
            {
                events_ = kNoneEvent;
                update();
            }

            // 返回 fd 当前 状态
            bool isNoneEvent() const
            {
                return events_ == kNoneEvent;
            }

            bool isReading()
            {
                return events_ & kReadEvent;
            }

            bool isWriting()
            {
                return events_ & kWriteEvent;
            }

            int index()
            {
                return index_;
            }

            void set_index(int idx)
            {
                index_ = idx;
            }

            // one loop per thread
            EventLoop* ownerLoop()
            {
                return loop_;
            }

            // 删除 Channel 使用
            void remove();

        private:
            
            void update();
            void handleEventWithGuard(Timestamp receiveTime);

            static const int kNoneEvent;
            static const int kReadEvent;
            static const int kWriteEvent;

            EventLoop* loop_; // 事件循环
            const int fd_;    // fd, Poller 监听的对象
            int events_;      // 注册 fd 感兴趣的事件
            int revents_;     // poller 返回的具体发生的事件
            int index_;

            std::weak_ptr<void> tie_;
            bool tied_;

            // 因为 Channel 通道中可以获知 fd 最终发生的事件 revents, 所以它负责调用具体事件的回调操作
            ReadEventCallback readCallback_;
            EventCallback writeCallback_;
            EventCallback closeCallback_;
            EventCallback errorCallback_;


        };
    }
}
