#include "Buffer.h"

#include <errno.h>
#include <sys/uio.h>
#include <unistd.h>

/**
 * 从 fd 上 读取数据, Poller 工作在 LT 模式
 * Buffer 缓冲区是有大小的, 但是从 fd 上读取数据的时候, 却不知道 tcp 数据最终的大小
 */
ssize_t m_muduo::net::Buffer::readFd(int fd, int *saveErrno)
{
    char extrabuf[65536] = { 0 }; // 栈上的内存空间 64kB
    struct iovec vec[2];
    const size_t writeable = writeableBytes(); // Buffer 底层缓冲区 剩余的 可写空间大小
    vec[0].iov_base = begin() + writerIndex_;
    vec[0].iov_len = writeable;

    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof extrabuf;

    const int iovcnt = (writeable < sizeof extrabuf ? 2 : 1);
    const ssize_t n = ::readv(fd, vec, iovcnt);
    if (n < 0)
    {
       *saveErrno = errno; 
    }
    else if (n <= writeable) // Buffer 的 可写缓冲区已经足够存储读出的数据
    {
        writerIndex_ += n;
    }
    else // extrabuf 中也写入了数据
    {
        writerIndex_ = buffer_.size();
        append(extrabuf, n - writeable); // writerIndex_ 开始写 n - writeable 大小的数据
    }

    return n;
}

ssize_t m_muduo::net::Buffer::writeFd(int fd, int *saveErrno)
{
    ssize_t n = ::write(fd, peek(), readableBytes());
    if (n < 0)
    {
        *saveErrno = errno;
    }
    return n;
}
