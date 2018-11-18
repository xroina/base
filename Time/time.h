/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * CTime.h
 *
 *  Created on: 2015/04/22
 *      Author: xronia
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#ifndef TIME_TIME_H_
#define TIME_TIME_H_

#include <ctime>
#include <string>
#include <cstring>
#include <iostream>

namespace Time {

class time {
protected:
    time_t sec;

    static const ::std::string WEEK[];
    static const ::std::string MONTH[];
    static const ::std::string WEEK_FULL[];
    static const ::std::string MONTH_FULL[];
    static const char WEEK_PTN[];
    static const char WEEK_FULL_PTN[];
    static const char MONTH_PTN[];
    static const char MONTH_FULL_PTN[];

public:
    time() : sec(0) {}
    time(const time&  tm) { set(tm); }
    time(const time*  tm) { set(tm); }
    time(const time_t tm) { set(tm); }
    time(struct tm& tm) { set(tm); }
    time(struct tm* tm) { set(tm); }
    time(const ::std::string& tm) { set(tm); }
    time(const ::std::string& tm, const ::std::string& fmt) { set(tm, fmt); }
    time(const short year, const short mon, const short day,
            const short hour = 0, const short min = 0, const short sec = 0)
    { set(year, mon, day, hour,min, sec); }

    ~time() {}

    void set(const time& tm) { this->sec = tm.sec; }
    void set(const time*);
    void set(const time_t tm) { this->sec = tm; }
    void set(struct tm& tm) { this->sec = ::mktime(&tm); }
    void set(struct tm*);
    void set(const short, const short, const short,
            const short = 0, const short = 0, const short = 0);
    void set(const ::std::string& tm) { stringTo(tm); }
    void set(const ::std::string& tm, const ::std::string& fmt) { stringTo(tm, fmt); }

    time_t get() const { return this->sec; }
    void get(time_t* tm) const;
    void get(struct tm& tm) const { tm = *::localtime(&this->sec); }
    void get(struct tm*) const;
    void get(short*, short*, short*, short* = nullptr, short* = nullptr, short* = nullptr) const;

#define struct_tm_set_(PARM, IN) { \
    struct tm* tm = ::localtime(&this->sec); \
    tm->PARM = (IN); \
    this->sec = ::mktime(tm);\
}
    short getYear() const   { return ::localtime(&this->sec)->tm_year + 1900; }
    void  setYear(short in) struct_tm_set_(tm_year, in - 1900)
    short getMon() const    { return ::localtime(&this->sec)->tm_mon + 1; }
    void  setMon(short in)  struct_tm_set_(tm_mon, in - 1)
    short getDay() const    { return ::localtime(&this->sec)->tm_mday; }
    void  setDay(short in)  struct_tm_set_(tm_mday, in)
    short getHour() const   { return ::localtime(&this->sec)->tm_hour; }
    void  setHour(short in) struct_tm_set_(tm_hour, in)
    short getMin() const    { return ::localtime(&this->sec)->tm_min; }
    void  setMin(short in)  struct_tm_set_(tm_min, in);
    short getSec() const    { return ::localtime(&this->sec)->tm_sec; }
    void  setSec(short in)  struct_tm_set_(tm_sec, in)
#undef struct_tm_set_

    time& operator=(const time& in) { this->sec = in.sec; return *this; }

    bool operator==(const time& in) const { return this->sec == in.sec; }
    bool operator!=(const time& in) const { return this->sec != in.sec; }
    bool operator< (const time& in) const { return this->sec <  in.sec; }
    bool operator<=(const time& in) const { return this->sec <= in.sec; }
    bool operator> (const time& in) const { return this->sec >  in.sec; }
    bool operator>=(const time& in) const { return this->sec >= in.sec; }

    time operator+=(const time& in) { this->sec += in.sec; return *this; }
    time operator-=(const time& in) { this->sec -= in.sec; return *this; }

    time operator+(const time& in) const { time ret; ret.sec = this->sec + in.sec; return ret; }
    time operator-(const time& in) const { time ret; ret.sec = this->sec - in.sec; return ret; }

    operator time_t()        const { return this->sec; }
    operator struct tm()     const { return *::localtime(&this->sec); }
    operator ::std::string() const { return toString(); }
    operator long double()   const { return this->get(); }
    operator double()        const { return static_cast<double>(this->get()); }
    operator timespec()      const { timespec ret = {this->sec, 0}; return ret; }

    template<typename T> time&  operator= (const T& in)       { *this = time(in); return *this; }
    template<typename T> bool   operator==(const T& in) const { return *this == time(in); }
    template<typename T> bool   operator!=(const T& in) const { return *this != time(in); }
    template<typename T> bool   operator< (const T& in) const { return *this <  time(in); }
    template<typename T> bool   operator<=(const T& in) const { return *this <= time(in); }
    template<typename T> bool   operator> (const T& in) const { return *this >  time(in); }
    template<typename T> bool   operator>=(const T& in) const { return *this >= time(in); }
    template<typename T> time   operator+=(const T& in)       { *this += time(in); return *this; }
    template<typename T> time   operator-=(const T& in)       { *this -= time(in); return *this; }
    template<typename T> time   operator+ (const T& in) const { time ret; ret = *this + time(in); return ret; }
    template<typename T> time   operator- (const T& in) const { time ret; ret = *this - time(in); return ret; }

    void now() { this->sec = ::time(nullptr); }

    ::std::string toString() const;
    ::std::string toString(const ::std::string& fmt) const;
    void stringTo(const ::std::string& in);
    void stringTo(const ::std::string& in, const ::std::string& fmt);
};

::std::ostream& operator<<(::std::ostream&, const time&);

/*--------1---------2---------3---------4---------5---------6---------7------*/

}   // end namespace Time

#endif /* TIME_TIME_H_ */
