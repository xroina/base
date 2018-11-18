/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * CmTime.cpp
 *
 *  Created on: 2015/05/04
 *      Author: xronia
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#include <Exception/exception.h>
#include <Time/ntime.h>
#include <Logger/logger.h>
#include <regex>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <iomanip>

namespace Time {

using ::std::string;
using ::std::stringstream;
using ::std::regex;
using ::std::smatch;
using ::std::regex_search;
using ::std::map;
using ::std::vector;

void ntime::set(const ntime& tm) {
    sec = tm.sec;
    nsec = tm.nsec;
}

void ntime::set(const ntime* tm) {
    if(nullptr == tm) NULLPOINTER("tm");
    sec = tm->sec;
    nsec = tm->nsec;
    adjustment();
}
void ntime::set(const time& tm)  {
    time::set(tm);
    this->nsec = 0;
}

void ntime::set(const time* tm) {
    if(nullptr == tm) NULLPOINTER("tm");
    time::set(tm);
    this->nsec = 0;
}

void ntime::set(const long double tm) {
    time::set(static_cast<time_t>(tm));
    this->nsec = static_cast<nsec_t>((tm - static_cast<nsec_t>(tm)) * DSEC);
}

void ntime::set(const timespec& tm)  {
    this->sec = tm.tv_sec;
    this->nsec = tm.tv_nsec;
    adjustment();
}

void ntime::set(const timespec* tm) {
    if(nullptr == tm) NULLPOINTER("tm");
    this->sec = tm->tv_sec;
    this->nsec = tm->tv_nsec;
    adjustment();
}

void ntime::set(struct tm& tm) {
    time::set(tm);
    this->nsec = 0;
}

void ntime::set(struct tm* tm) {
    if(nullptr == tm) NULLPOINTER("tm");
    time::set(tm);
    this->nsec = 0;
}

void ntime::set(const short year, const short mon, const short day,
        const short hour, const short min, const short sec,
        const short msec, const short usec, const short nsec) {
    time::set(year, mon, day, hour, min, sec);
    this->nsec = static_cast<nsec_t>(msec) * MSEC +
            static_cast<nsec_t>(usec) * USEC +
            static_cast<nsec_t>(nsec);
    adjustment();
}

long double ntime::get() const {
    return static_cast<long double>(sec) +
        static_cast<long double>(nsec) / DSEC;
}

void ntime::get(timespec& tm) const {
    tm.tv_sec = sec;
    tm.tv_nsec = nsec;
}

void ntime::get(timespec* tm) const {
    if(nullptr == tm) NULLPOINTER("tm");
    tm->tv_sec = sec;
    tm->tv_nsec = nsec;
}


void ntime::get(short* year, short* mon, short* day, short* hour,
        short* min, short* sec, short* msec, short* usec, short* nsec) const {
    time::get(year, mon, day, hour, min, sec);
    if(nullptr != msec) *msec = getMSec();
    if(nullptr != usec) *usec = getUSec();
    if(nullptr != nsec) *nsec = getNSec();
}

ntime ntime::operator+=(const ntime& in) {
    sec += in.sec;
    nsec += in.nsec;
    adjustment();
    return *this;
}

ntime ntime::operator-=(const ntime& in) {
    sec -= in.sec;
    nsec -= in.nsec;
    adjustment();
    return *this;
}

ntime ntime::operator+(const ntime& in) const {
    ntime ret;
    ret.sec = sec + in.sec;
    ret.nsec = nsec + in.nsec;
    ret.adjustment();
    return ret;
}

ntime ntime::operator-(const ntime& in) const {
    ntime ret;
    ret.sec = sec - in.sec;
    ret.nsec = nsec - in.nsec;
    ret.adjustment();
    return ret;
}


void ntime::now() {
    timespec now;
    int ret = ::clock_gettime(CLOCK_REALTIME_COARSE, &now);
    if(ret < 0) RUNTIME_ERROR("clock_gettime exception");
    this->set(&now);
}

#define fillw_(n) ::std::setw(n) << ::std::setfill('0')

string ntime::toString() const {
    stringstream buf;
    buf << time::toString();
    if(nsec != 0) buf << "." << fillw_(9) << this->nsec;
    return buf.str();
}

string ntime::toString(const string& fmt) const {

    stringstream buf;
    regex re("%%|%[SMUNsmun]S");
    smatch m;
    auto i = fmt.begin();
    for (; regex_search(i, fmt.end(), m, re); i += m.position() + m.length()) {
        buf << string(i, i + m.position());
        if(m.str() == "%%") buf << m.str();
        else if(m.str() == "%SS") buf << fillw_(9) << nsec;
        else if(m.str() == "%MS") buf << fillw_(3) << getMSec();
        else if(m.str() == "%US") buf << fillw_(3) << getUSec();
        else if(m.str() == "%NS") buf << fillw_(3) << getNSec();
        else if(m.str() == "%sS") buf << ::std::fixed <<
                static_cast<long double>(this->sec) +
                static_cast<long double>(this->nsec) / DSEC;
        else if(m.str() == "%mS") buf << ::std::fixed << static_cast<long double>(nsec) / DMSEC;
        else if(m.str() == "%uS") buf << ::std::fixed << static_cast<long double>(nsec) / DUSEC;
        else if(m.str() == "%nS") buf << this->nsec;
    }
    buf << string(i, fmt.end());

    return time::toString(buf.str().c_str());
}

#undef fillw_

void ntime::stringTo(const string& in) {

    static constexpr char ptn[] = "(\\-?\\d{1,4})\\-(\\d{1,2})\\-(\\d{1,2})T"
            "(\\d{1,2}):(\\d{1,2}):(\\d{1,2})(\\.\\d+)?";
    static const regex re(ptn);
    smatch m;
    if(!regex_search(in, m, re))
        REGEX_ERROR("regex_search not match(in=" << in << ",ptn=" << ptn << ")");

    TRACE_LOG("in=" << in << " reg=" << m[1].str() << ", " << m[2].str() << ", " << m[3].str()
            << ", " << m[4].str() << ", " << m[5].str() << ", " << m[6].str() << ", " << m[7].str());

    this->setYear(stoi(m[ 1].str()));
    this->setMon (stoi(m[ 2].str()));
    this->setDay (stoi(m[ 3].str()));
    this->setHour(stoi(m[ 4].str()));
    this->setMin (stoi(m[ 5].str()));
    this->setSec (stoi(m[ 6].str()));
    if(m[7].str().length() == 0)
        nsec = 0;
    else
        nsec = static_cast<nsec_t>(stold(m[ 7].str()) * DSEC);
}

void ntime::stringTo(const string& in, const string& fmt) {

    map<string, string> regMap;

    static constexpr char regStr[] = "\\~|\\}|\\||\\{|\\^|\\]|\\\\|\\[|\\?|\\#"
            "|\\=|\\:\\;|\\,|\\.|\\-|\\+|\\*|\\)|\\(|\\$|\\!|\\<|\\>|\\&|\\'";
    regMap.emplace("%%", "%");
    regMap.emplace("%SS", "\\d+");
    regMap.emplace("%MS", "\\d+");
    regMap.emplace("%US", "\\d+");
    regMap.emplace("%NS", "\\d+");
    regMap.emplace("%sS", "\\d+|.\\d+|\\d+\\.\\d+");
    regMap.emplace("%mS", "\\d+|.\\d+|\\d+\\.\\d+");
    regMap.emplace("%uS", "\\d+|.\\d+|\\d+\\.\\d+");
    regMap.emplace("%nS", "\\d+|.\\d+|\\d+\\.\\d+");
    regMap.emplace("%a", WEEK_PTN);
    regMap.emplace("%A", WEEK_FULL_PTN);
    regMap.emplace("%b", MONTH_PTN);
    regMap.emplace("%B", MONTH_FULL_PTN);
    regMap.emplace("%Y", "\\-?\\d{1,4}");
    regMap.emplace("%y", "\\d+{1,2}");
    regMap.emplace("%m", "\\d{1,2}");
    regMap.emplace("%d", "\\d{1,2}");
    regMap.emplace("%e", " ?\\d{1,2}");
    regMap.emplace("%H", "\\d{1,2}");
    regMap.emplace("%M", "\\d{1,2}");
    regMap.emplace("%S", "\\d{1,2}");
    regMap.emplace("%T", "\\d{1,2}:\\d{1,2}:\\d{1,2}");
    regMap.emplace("%F", "\\-?\\d{1,4}\\-\\d{1,2}\\-\\d{1,2}");
    regMap.emplace("%D", "\\d{1,2}/\\d{1,2}/\\-?\\d{1,4}");

    stringstream p;
    p << regStr;
    for(auto i = regMap.rbegin(); i != regMap.rend(); i++) p << '|' << i->first;
    TRACE_LOG("regex pattern=" << p.str());
    regex re(p.str());
    smatch m;

    vector<string> patIndex;
    stringstream pat;
    auto j = fmt.begin();
    for(; regex_search(j, fmt.end(), m, re); j += m.position(0) + m.length(0)) {
        string s = m.str();
        pat << string(j, j + m.position());
        patIndex.push_back(s);
        auto pair = regMap.find(s);
        if(pair == regMap.end()) {
            pat << '(' << '\\' << s << ')';
        } else {
            pat << '(' << pair->second << ')';
        }
    }
    pat << string(j, fmt.end());

    TRACE_LOG("fmt=" << fmt <<" patIndex size=" << patIndex.size() <<
            " pat=" << pat.str() << " in=" << in);

    regex reg(pat.str());
    if(!regex_search(in, m, reg))
        REGEX_ERROR("regex_search not match(in=" << in << ",ptn=" << pat.str() << ")");
    int index = 0;
    for(auto i: patIndex) {
        index++;
        string s = m.str(index);
        TRACE_LOG("index=" << index << " patIndex=" << i << " m.str=" << s);

        if(i == "%SS") {
            s += "000000000";
            this->nsec = stol(s.substr(0, 9));
        }
        else if(i == "%MS") { setMSec(stoi(s)); }
        else if(i == "%US") { setUSec(stoi(s)); }
        else if(i == "%NS") { setNSec(stoi(s)); }
        else if(i == "%mS") { this->nsec = static_cast<nsec_t>(stold(s) * DMSEC); }
        else if(i == "%uS") { this->nsec = static_cast<nsec_t>(stold(s) * DUSEC); }
        else if(i == "%nS") { this->nsec = stol(s); }
        else if(i == "%sS") {
            long double tm = stold(s);
            this->sec  = static_cast<time_t>(tm);
            this->nsec = static_cast<nsec_t>(tm * DSEC) % SEC;
        }
        else if(i == "%a") {}
        else if(i == "%A") {}
        else if(i == "%b") { for(int i = 0; i < 12; i++) if(s == MONTH[i]) setMon(i + 1); }
        else if(i == "%B") { for(int i = 0; i < 12; i++) if(s == MONTH_FULL[i]) setMon(i + 1); }
        else if(i == "%Y") { setYear(stoi(s)); }
        else if(i == "%y") { short y = stoi(s); setYear(y < 69 ? y + 1900 : y + 2000); }
        else if(i == "%m") { setMon (stoi(s)); }
        else if(i == "%d") { setDay (stoi(s)); }
        else if(i == "%e") { setDay (stoi(s)); }
        else if(i == "%H") { setHour(stoi(s)); }
        else if(i == "%M") { setMin (stoi(s)); }
        else if(i == "%S") { setSec (stoi(s)); }
        else if(i == "%T") {
            static constexpr char ptn[] = "(\\d+)\\:(\\d+)\\:(\\d+)";
            static const regex reg(ptn);
            smatch m;
            if(!regex_search(s, m, reg))
                REGEX_ERROR("regex_search not match(in=" << in << ",ptn=" << pat.str() << ")");
            setHour(stoi(m.str(1)));
            setMin (stoi(m.str(2)));
            setSec (stoi(m.str(3)));
        }
        else if(i == "%F") {
            static constexpr char ptn[] = "(\\-?\\d+)\\-(\\d+)\\-(\\d+)";
            static const regex reg(ptn);
            smatch m;
            if(!regex_search(s, m, reg))
                REGEX_ERROR("regex_search not match(in=" << in << ",ptn=" << pat.str() << ")");
            setYear(stoi(m.str(1)));
            setMon (stoi(m.str(2)));
            setDay (stoi(m.str(3)));
        }
        else if(i == "%F") {
            static constexpr char ptn[] = "(?\\d+)/(\\d+)/(\\-\\d+)";
            static const regex reg(ptn);
            smatch m;
            if(!regex_search(s, m, reg))
                REGEX_ERROR("regex_search not match(in=" << in << ",ptn=" << pat.str() << ")");
            setYear(stoi(m.str(3)));
            setMon (stoi(m.str(2)));
            setDay (stoi(m.str(1)));
        }
    }
}

void ntime::adjustment() {
    if(nsec > SEC) {
        sec += nsec / SEC;
        nsec = nsec % SEC;
    } else if(nsec < 0) {
        sec -= nsec / SEC + 1;
        nsec = nsec % SEC + SEC;
    }
}

::std::ostream& operator<<(::std::ostream& out, const ntime& tgt) {
    out << tgt.toString();
    return out;
}

/*--------1---------2---------3---------4---------5---------6---------7------*/

} // end namespace Time
