#include "Timestamp.h"

#include <time.h>

m_muduo::Timestamp::Timestamp() : microSecondsSinceEpoch_(0)
{
}

m_muduo::Timestamp::Timestamp(int64_t microSecondsSinceEpoch) : microSecondsSinceEpoch_(microSecondsSinceEpoch)
{

}

m_muduo::Timestamp m_muduo::Timestamp::now()
{
    time_t ti = time(NULL);
    return m_muduo::Timestamp(ti);
}

std::string m_muduo::Timestamp::toString() const
{
    char buf[128] = { 0 };
    tm* tm_time = localtime(&microSecondsSinceEpoch_);

    snprintf(buf, 128, "%4d-%02d-%02d %02d:%02d:%02d",
        tm_time->tm_year + 1900,
        tm_time->tm_mon + 1,
        tm_time->tm_mday,
        tm_time->tm_hour,
        tm_time->tm_min,
        tm_time->tm_sec);

    return buf;
}

/**
 *  test
 */

/*
                    Test

    int main() 
    {
        std::cout << m_muduo::Timestamp::now().toString();

        return 0;
    }

*/
