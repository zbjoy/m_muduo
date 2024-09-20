#pragma once

#include <string>

#include "nocopyable.h"

// TODO:    将 __FUNCTION__ 嵌入到 Logger 中

#ifdef MMUDUODEBUG
#define LOG_DEBUG(logMsgFormat, ...) \
    do \
    { \
        Logger& logger = Logger::instance(); \
        logger.setLogLevel(DEBUG); \
        char buf[1024] = { 0 }; \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0);
#else
#define LOG_DEBUG(logMsgFormat, ...)

#endif


#define LOG_INFO(logMsgFormat, ...) \
    do \
    { \
        Logger& logger = Logger::instance(); \
        logger.setLogLevel(INFO); \
        char buf[1024] = { 0 }; \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0);

#define LOG_ERROR(logMsgFormat, ...) \
    do \
    { \
        Logger& logger = Logger::instance(); \
        logger.setLogLevel(ERROR); \
        char buf[1024] = { 0 }; \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0);

#define LOG_FATAL(logMsgFormat, ...) \
    do \
    { \
        Logger& logger = Logger::instance(); \
        logger.setLogLevel(FATAL); \
        char buf[1024] = { 0 }; \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
        exit(-1); \
    } while(0);

// 定义日志的级别   DEBUG, INFO, ERROR, FATAL
enum LogLevel
{
    DEBUG,  // 调试信息
    INFO,   // 普通信息
    ERROR,  // 错误信息
    FATAL,  // 调试信息
};

// 输出一个日志类
class Logger : m_muduo::nocopyable
{
public:
    // 获取日志唯一的实例对象
    static Logger& instance();

    // 设置日志级别
    void setLogLevel(int level);

    // 写日志
    void log(std::string msg);

private:
    int logLevel_;
};

