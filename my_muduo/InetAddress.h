#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

namespace m_muduo
{

    namespace net
    {

        class InetAddress
        {
        public:
            // explicit 会阻止 c++ 的 隐式类型转换
            explicit InetAddress(uint16_t port = 0, std::string ip = "127.0.0.1");
            explicit InetAddress(const sockaddr_in& addr) : addr_(addr) {}

            std::string toIp() const;
            std::string toIpPort() const;
            uint16_t toPort() const;

            const sockaddr_in* getSockAddr() const 
            {
                return &addr_;
            }

            void setSockAddr(const sockaddr_in& addr)
            {
                addr_ = addr;
            }

        private:
            sockaddr_in addr_;
        };

    }

}
