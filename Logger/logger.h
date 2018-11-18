/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * CLogger.h
 *
 *  Created on: 2015/05/05
 *      Author: xronia
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <list>
#include <sstream>

namespace Logger {

class logger {
public:
    enum LEVEL {
        EXCEPTION,
        ERROR,
        WARNING,
        INFO,
        DEBUG,
        TRACE,
    };

    class Log {
    public:
        LEVEL level;
        uint    index;
        timespec time;
        ::std::string file;
        ::std::string func;
        uint    line;
        ::std::string message;
    };

private:
    static const size_t MAX_LINE;

    static const ::std::string LOG_LEVEL[];
    static LEVEL level;
    static ::std::list<Log> log;

    static logger instance;

    logger();
    virtual ~logger();

public:
    static logger& Instance();

    void Trace(
            const LEVEL          level,
            const ::std::string& file,
            const ::std::string& func,
            const uint           line,
            const char*          fmt,
            ...
    );
    void Trace(
            const LEVEL        level,
            const ::std::string& file,
            const ::std::string& func,
            const uint           line,
            const char*          fmt,
            va_list              va
    );

    void Trace(
            const LEVEL          level,
            const ::std::string& file,
            const ::std::string& func,
            const uint           line,
            const ::std::string& message
    );

    LEVEL getLogLevel() const;
    void setLogLevel(LEVEL level);
    void flash();
    bool find(const ::std::string& str) const;
    Log& getLast() const;

private:

    class LogStrMatcher {
        const ::std::string str;
    public:
        LogStrMatcher(const ::std::string&);

        bool operator()(const Log& t);
    };
};
/*--------1---------2---------3---------4---------5---------6---------7------*/

} /* end namespace Logger */

#define LOGGER_LOGGER_H_CHAR_(LEVEL_, ...) {                                \
    ::Logger::logger& __ins = ::Logger::logger::Instance();                 \
    if(::Logger::logger::LEVEL_ <= __ins.getLogLevel())                     \
        __ins.Trace(::Logger::logger::LEVEL_,                               \
                 __FILE__, __PRETTY_FUNCTION__, __LINE__, __VA_ARGS__);     \
}

#define LOGGER_LOGGER_H_STRING_(LEVEL_, MESSAGE_) {                         \
    ::Logger::logger& __ins = ::Logger::logger::Instance();                 \
    if(::Logger::logger::LEVEL_ <= __ins.getLogLevel()) {                   \
        ::std::stringstream __stream; __stream << MESSAGE_;                 \
        __ins.Trace(::Logger::logger::LEVEL_,                               \
                 __FILE__, __PRETTY_FUNCTION__, __LINE__, __stream.str());  \
    }                                                                       \
}

#define LOGGER_LOGGER_H_0_ LOGGER_LOGGER_H_STRING_
#define LOGGER_LOGGER_H_1_ LOGGER_LOGGER_H_CHAR_
#define LOGGER_LOGGER_H_2_ LOGGER_LOGGER_H_CHAR_
#define LOGGER_LOGGER_H_3_ LOGGER_LOGGER_H_CHAR_
#define LOGGER_LOGGER_H_4_ LOGGER_LOGGER_H_CHAR_
#define LOGGER_LOGGER_H_5_ LOGGER_LOGGER_H_CHAR_
#define LOGGER_LOGGER_H_6_ LOGGER_LOGGER_H_CHAR_
#define LOGGER_LOGGER_H_7_ LOGGER_LOGGER_H_CHAR_
#define LOGGER_LOGGER_H_8_ LOGGER_LOGGER_H_CHAR_
#define LOGGER_LOGGER_H_9_ LOGGER_LOGGER_H_CHAR_

#define LOGGER_LOGGER_H_GET_MACRO_(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,           \
        NAME_,...) NAME_

#define LOGGER_LOGGER_H_LOG_(LEVEL_, ...)                                   \
        LOGGER_LOGGER_H_GET_MACRO_(__VA_ARGS__,                             \
                LOGGER_LOGGER_H_9_,                                         \
                LOGGER_LOGGER_H_8_,                                         \
                LOGGER_LOGGER_H_7_,                                         \
                LOGGER_LOGGER_H_6_,                                         \
                LOGGER_LOGGER_H_5_,                                         \
                LOGGER_LOGGER_H_4_,                                         \
                LOGGER_LOGGER_H_3_,                                         \
                LOGGER_LOGGER_H_2_,                                         \
                LOGGER_LOGGER_H_1_,                                         \
                LOGGER_LOGGER_H_0_)                                         \
                (LEVEL_, __VA_ARGS__)

#define ERROR_LOG(...)  LOGGER_LOGGER_H_LOG_(ERROR,   __VA_ARGS__)
#define WARN_LOG(...)   LOGGER_LOGGER_H_LOG_(WARNING, __VA_ARGS__)
#define INFO_LOG(...)   LOGGER_LOGGER_H_LOG_(INFO,    __VA_ARGS__)
#define DEBUG_LOG(...)  LOGGER_LOGGER_H_LOG_(DEBUG,   __VA_ARGS__)
#define TRACE_LOG(...)  LOGGER_LOGGER_H_LOG_(TRACE,   __VA_ARGS__)
/*--------1---------2---------3---------4---------5---------6---------7------*/

#endif /* LOGGER_LOGGER_H_ */
