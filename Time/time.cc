/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * CTime.cpp
 *
 *  Created on: 2015/05/04
 *      Author: xronia
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#include <Exception/exception.h>
#include <Time/time.h>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <algorithm>


namespace Time {

using ::std::string;

const string time::WEEK[] = {
        "Sun",
        "Mon",
        "Tue",
        "Wed",
        "Thu",
        "Fri",
        "Sat"
};

const string time::MONTH[] = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
};

const string time::WEEK_FULL[] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
};

const string time::MONTH_FULL[] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
};

const char time::WEEK_PTN[]       = "Sun|Mon|Tue|Wed|Thu|Fri|Sat";
const char time::WEEK_FULL_PTN[]  = "Sunday|Monday|Tuesday|Wednesday|Thursday|Friday|Saturday";
const char time::MONTH_PTN[]      = "Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec";
const char time::MONTH_FULL_PTN[] = "January|February|March|April|May|June|July|August|September|October|November|December";

void time::set(const time* tm) {
    if(nullptr == tm) NULLPOINTER("tm");
    this->sec = tm->sec;
}

void time::set(struct tm* tm) {
    if(nullptr == tm) NULLPOINTER("tm");
    this->sec = ::mktime(tm);
}

void time::get(struct tm* tm) const {
    if(nullptr == tm) NULLPOINTER("tm");
    ::memcpy(tm, ::localtime(&this->sec), sizeof(struct tm));
}

void time::get(time_t* tm) const {
    if(nullptr == tm) NULLPOINTER("tm");
    *tm = this->sec;
}

void time::set(const short year, const short mon, const short day,
        const short hour, const short min, const short sec) {
    struct tm tm = { 0 };
    tm.tm_year = year - 1900;
    tm.tm_mon  = mon - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min  = min;
    tm.tm_sec  = sec;
    this->sec = ::mktime(&tm);
}

void time::get(short* year, short* mon, short* day,
        short* hour, short* min, short* sec) const {
    if(nullptr == year) NULLPOINTER("year");
    if(nullptr == mon) NULLPOINTER("mon");
    if(nullptr == day) NULLPOINTER("day");
    struct tm* tm = ::localtime(&this->sec);
    *year = tm->tm_year + 1900;
    *mon  = tm->tm_mon + 1;
    *day  = tm->tm_mday;
    if(nullptr != hour) *hour = tm->tm_hour;
    if(nullptr != min ) *min  = tm->tm_min;
    if(nullptr != sec ) *sec  = tm->tm_sec;
}

string time::toString() const {
//    char* str = ::ctime(&this->tm);
//    if(nullptr == str) THROW_EXP("std::ctime(ret=NULL)");
//    string ret = str;
//    return ret.substr(0, ret.length() - 1);
    return toString("%Y-%m-%dT%T");
}

string time::toString(const string& fmt) const {
    char buf[256];
    size_t ret = ::strftime(buf, 256, fmt.c_str(), ::localtime(&this->sec));
    if(0 == ret) RUNTIME_ERROR("::strftime(ret=%u)", ret);
    return string(buf);
}

void time::stringTo(const string& in) {
    struct tm tm = { 0, 0, 0, 1, 0, 70 };
//    char* ret = ::strptime(in.c_str(), "%a %b %d %T %Y", &tm);
    char* ret = ::strptime(in.c_str(), "%Y-%m-%dT%T", &tm);
    if(nullptr == ret || ::strlen(ret) > 0)
        RUNTIME_ERROR("::strptime(in=%s,ret=%s)", in.c_str(), ret);
    this->sec = ::mktime(&tm);
}

void time::stringTo(const string& in, const ::std::string& fmt) {
    struct tm tm = { 0, 0, 0, 1, 0, 70 };
    char* ret = ::strptime(in.c_str(), fmt.c_str(), &tm);
    if(nullptr == ret || ::strlen(ret) > 0)
        RUNTIME_ERROR("::strptime(in=%s,fmt=%s,ret=%s)", in.c_str(), fmt.c_str(), ret);
    this->sec = mktime(&tm);
}

::std::ostream& operator<<(::std::ostream& out, const time& tgt) {
    out << tgt.toString();
    return out;
}

/*--------1---------2---------3---------4---------5---------6---------7------*/

} // end namespace Time
