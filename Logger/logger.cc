/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * CLogger.cpp
 *
 *  Created on: 2015/05/05
 *      Author: xronia
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#include <Logger/logger.h>
#include <Time/ntime.h>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <cstdio>
#include <string>
#include <list>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>


namespace Logger {

using ::std::string;
using ::std::stringstream;
using ::std::list;
using ::std::cout;
using ::std::cerr;
using ::std::endl;

const size_t logger::MAX_LINE = 1000;

const string logger::LOG_LEVEL[] = {
        "EXCEPTION",
        "ERROR",
        "WARNING",
        "INFO",
        "DEBUG",
        "TRACE",
};

logger::LEVEL logger::level = TRACE;

list<logger::Log> logger::log;

logger logger::instance;

logger::logger() {
}

logger::~logger() {
}

logger& logger::Instance() {
    return instance;
}

void logger::Trace(
        const LEVEL   level,
        const string& file,
        const string& func,
        const uint    line,
        const char*   fmt,
        ...
) {
    va_list va;
    va_start(va, fmt);
    Trace(level, file, func, line, fmt, va);
    va_end(va);

}

void logger::Trace(
        const LEVEL   level,
        const string& file,
        const string& func,
        const uint    line,
        const char*   fmt,
        va_list       va
) {
    if(level > logger::level) return;
    if(nullptr == fmt) throw ::std::invalid_argument("nullptr exception");
    char buf[256] = { 0 };
    ::vsnprintf(buf, sizeof(buf), fmt, va);
    Trace(level, file, func, line, string(buf));
}

void logger::Trace(
        const LEVEL   level,
        const string& file,
        const string& func,
        const uint    line,
        const string& message
) {
    if(level > logger::level) return;

    Log data;
    data.level = level;
    if (log.empty()) data.index = 0;
    else data.index = log.back().index + 1;
    Time::ntime now;
    now.now();
    data.time = now;
    data.file  = file.substr(file.find_last_of('/') + 1);
    data.func  = func;
    data.line  = line;
    data.message = message;

    stringstream s;
    s << data.index << "[" << LOG_LEVEL[level] << "]" <<
            now.toString("%Y-%m-%d %H:%M:%S.%MS%US%NS") << " " <<
            data.file << "(" << line << ") " << func << " > " << message;

    log.push_back(data);
    while(log.size() > MAX_LINE)
        log.pop_front();

    // TODO(MDBに登録する)
    // TODO(ファイルに出す)

    if (level < INFO)
        cerr << s.str() << endl;
    else
        cout << s.str() << endl;
}

logger::LEVEL logger::getLogLevel() const {
    return logger::level;
}

void logger::setLogLevel(LEVEL level) {
    logger::level = level;
}

void logger::flash() {
    log.clear();
}

bool logger::find(const string& str) const {
    return log.rend() != std::find_if(log.rbegin(), log.rend(), LogStrMatcher(str));
}

logger::Log& logger::getLast() const {
    if(log.empty()) throw ::std::out_of_range("out of range exception");
    return log.back();
}

logger::LogStrMatcher::LogStrMatcher(const string& in) : str(in) {

}
bool logger::LogStrMatcher::operator()(const Log& t) {
    return t.message.find(str) == 0;
}

/*--------1---------2---------3---------4---------5---------6---------7------*/

} /* end namespace Logger */
