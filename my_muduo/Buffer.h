#pragma once

#include "nocopyable.h"

#include <vector>
#include <string>
#include <algorithm>

namespace m_muduo
{
    namespace net
    {
        /* 网络库底层缓冲区类型定义 */
        class Buffer : m_muduo::nocopyable
        {
        public:
            static const size_t kCheapPrepend = 8;
            static const size_t kInitialSize = 1024;

            explicit Buffer(size_t initialSize = kInitialSize) 
                        : buffer_(kCheapPrepend + initialSize)
                        , readerIndex_(kCheapPrepend)
                        , writerIndex_(kCheapPrepend)
            {
            }

            size_t readableBytes() const
            {
                return writerIndex_ - readerIndex_;
            }

            size_t writeableBytes() const
            {
                return buffer_.size() - writerIndex_;
            }

            size_t prependableBytes() const 
            {
                return readerIndex_;
            }

            // 返回 缓冲区中 可读数据 的 起始地址
            const char* peek() const
            {
                return begin() + readerIndex_;
            }

            // onMessage string <- Buffer
            void retrieve(size_t len)
            {
                if (len < readableBytes())
                {
                    readerIndex_ += len; // 应用只读取了可读缓冲区数据的一部分, 就是 len, 还剩下 readerIndex_ += len -- writerIndex_
                }
                else // len == readableBytes()
                {
                    retrieveAll();
                }
            }

            void retrieveAll()
            {
                readerIndex_ = writerIndex_ = kCheapPrepend;
            }

            // 把 onMessage 函数 上报的 Buffer 数据, 转成 string 类型的数据返回
            std::string retrieveAllAsString()
            {
                return retrieveAsString(readableBytes()); // 应用可读取数据的长度
            }

            std::string retrieveAsString(size_t len)
            {
                std::string result(peek(), len);
                retrieve(len); // 上面已经将缓冲区中的可读取的数据读取出来了, 要对 缓冲区 进行复位操作
                return result;
            }

            // buffer_.size() - writerIndex_
            void ensureWriteableBytes(size_t len)
            {
                if (writeableBytes() < len)
                {
                    makeSpace(len); // 扩容函数
                }
            }

            // 将 [data, data+len] 内存上的数据, 添加到 writable 缓冲区当中
            void append(const char* data, size_t len)
            {
                ensureWriteableBytes(len);
                std::copy(data, data+len, beginWrite());
                writerIndex_ += len;
            }

            char* beginWrite()
            {
                return begin() + writerIndex_;
            }

            const char* beginWrite() const
            {
                return begin() + writerIndex_;
            }

            // 从 fd 上 读取数据
            ssize_t readFd(int fd, int* saveErrno);

            // 通过 fd 发送数据
            ssize_t writeFd(int fd, int* saveErrno);

        private:
            char* begin()
            {
                // &(it.operator*())
                return &*buffer_.begin(); // vector 底层 数组首元素的地址
            }

            const char* begin() const
            {
                return &*buffer_.begin();
            }

            void makeSpace(size_t len)
            {
                /**
                 * kCheapPrepend | readerIndex_ | writerIndex_
                 * 
                 */
                if (writeableBytes() + prependableBytes() < len + kCheapPrepend)
                {
                    buffer_.resize(writerIndex_ + len);
                }
                else
                {
                    size_t readable = readableBytes();
                    std::copy(begin() + readerIndex_, begin() + writerIndex_, begin() + kCheapPrepend);
                    readerIndex_ = kCheapPrepend;
                    writerIndex_ = readerIndex_ = readable;
                }
            }

            std::vector<char> buffer_;
            size_t readerIndex_;
            size_t writerIndex_;
        };
    }
}
