#include "Logger.h"
#include "Timestamp.h"

#include <iostream>


Logger& Logger::instance()
{
    static Logger logger;
    return logger;
}

void Logger::setLogLevel(int level)
{
    logLevel_ = level;
}

// 写日志   [级别信息] time : msg
void Logger::log(std::string msg)
{
    switch (logLevel_)
    {
    case DEBUG:
        std::cout << "[DEBUG]";
        break;
    case INFO:
        std::cout << "[INFO]";
        break;
    case ERROR:
        std::cout << "[ERROR]";
        break;
    case FATAL:
        std::cout << "[FATAL]";
        break;
    default:
        break;
    }

    // 打印时间 和 msg
    std::cout << "print time" << m_muduo::Timestamp::now().toString() << " : " << msg << std::endl;
}
