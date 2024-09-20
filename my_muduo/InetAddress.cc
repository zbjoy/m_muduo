#include "InetAddress.h"

#include <strings.h>
#include <iostream>
#include <string.h>
#include <arpa/inet.h>

m_muduo::net::InetAddress::InetAddress(uint16_t port, std::string ip)
{
    bzero(&addr_, sizeof(addr_));

    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}

std::string m_muduo::net::InetAddress::toIp() const
{
    char buf[64] = { 0 };
    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
    return buf;
}

std::string m_muduo::net::InetAddress::toIpPort() const
{
    // ip:port
    char buf[64] = { 0 };
    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
    size_t end = strlen(buf);
    uint16_t port = ntohs(addr_.sin_port);
    sprintf(buf + end, ":%u", port);
    return buf;
}

uint16_t m_muduo::net::InetAddress::toPort() const
{
    return ntohs(addr_.sin_port);
}

/**
 * test
 */

int main()
{
    m_muduo::net::InetAddress addr(8080);
    std::cout << addr.toIpPort();

    return 0;
}
