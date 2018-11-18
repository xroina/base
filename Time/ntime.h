/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * CmTime.h
 *
 *  Created on: 2015/04/22
 *      Author: xronia
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#ifndef TIME_NTIME_H_
#define TIME_NTIME_H_

#include <Time/time.h>
#include <string>

namespace Time {

class ntime : public time {
private:
    typedef long nsec_t;
    nsec_t nsec;
    static constexpr nsec_t USEC = 1000;
    static constexpr nsec_t MSEC = USEC * 1000;
    static constexpr nsec_t SEC = MSEC * 1000;
    static constexpr long double DUSEC = 1000.0L;
    static constexpr long double DMSEC = DUSEC * 1000.0L;
    static constexpr long double DSEC = DMSEC * 1000.0L;
public:
    ntime() : time(), nsec(0) {}
    ntime(const ntime& tm)        { set(tm); }
    ntime(const ntime* tm)        { set(tm); }
    ntime(const time& tm)         { set(tm); }
    ntime(const time* tm)         { set(tm); }
    ntime(const long double tm)   { set(tm); }
    ntime(const time_t sec, const nsec_t nsec) { set(sec, nsec); }
    ntime(const timespec& tm)     { set(tm); }
    ntime(const timespec* tm)     { set(tm); }
    ntime(struct tm& tm)    { set(tm); }
    ntime(struct tm* tm)    { set(tm); }
    ntime(const ::std::string& tm) { set(tm); }
    ntime(const ::std::string& tm, const ::std::string& fmt) { set(tm, fmt); }
    ntime(const short year, const short mon, const short day,
            const short hour = 0, const short min = 0, const short sec = 0,
            const short msec = 0, const short usec = 0, const short nsec = 0) {
        set(year, mon, day, hour, min, sec, msec, usec, nsec);
    }

    ~ntime() {}

    void set(const ntime&);
    void set(const ntime*);
    void set(const time&);
    void set(const time*);
    void set(const long double tm);
    void set(const time_t sec, const nsec_t nsec) { this->sec = sec; this->nsec = nsec; }
    void set(const timespec&);
    void set(const timespec*);
    void set(struct tm&);
    void set(struct tm*);
    void set(const ::std::string& tm) { stringTo(tm); }
    void set(const ::std::string& tm, const ::std::string& fmt) { stringTo(tm, fmt); }
    void set(const short, const short, const short,
            const short = 0, const short = 0, const short = 0,
            const short = 0, const short = 0, const short = 0);

    long double get() const;
    void get(time_t* tm) const    { time::get(tm); }
    void get(struct tm& tm) const { time::get(tm); }
    void get(struct tm* tm) const { time::get(tm); }
    void get(timespec&) const;
    void get(timespec*) const;
    void get(short*, short*, short*,
            short* = nullptr, short* = nullptr, short* = nullptr,
            short* = nullptr, short* = nullptr, short* = nullptr) const;

    void  setMSec(short in) { nsec = static_cast<nsec_t>(in) * MSEC + nsec % MSEC; adjustment(); }
    short getMSec() const   { return static_cast<short>(nsec / MSEC); }
    void  setUSec(short in) { nsec = (nsec / MSEC) * MSEC + static_cast<nsec_t>(in) * USEC + nsec % USEC; adjustment(); }
    short getUSec() const   { return static_cast<short>(nsec / USEC % USEC); }
    void  setNSec(short in) { nsec = (nsec / USEC) * USEC + static_cast<nsec_t>(in); adjustment(); }
    short getNSec() const   { return static_cast<short>(nsec % USEC); }

    ntime& operator=(const ntime& in) { sec = in.sec; nsec = in.nsec; return *this; }

#define operator_if_(OP) {          \
    bool ret = this->sec OP in.sec; \
    if(this->sec == in.sec)         \
        ret = this->nsec OP in.nsec;\
    return ret;                     \
}
    bool operator==(const ntime& in) const { return sec == in.sec && nsec == in.nsec; }
    bool operator!=(const ntime& in) const { return sec != in.sec || nsec != in.nsec; }
    bool operator< (const ntime& in) const operator_if_(<)
    bool operator<=(const ntime& in) const operator_if_(<=)
    bool operator> (const ntime& in) const operator_if_(>)
    bool operator>=(const ntime& in) const operator_if_(>=)
#undef operator_if_

    ntime operator+=(const ntime&);
    ntime operator-=(const ntime&);
    ntime operator+(const ntime&) const;
    ntime operator-(const ntime&) const;

    operator time()          const { return *this; }
    operator time&()         const { return *static_cast<time*>(const_cast<ntime*>(this)); }
    operator time_t()        const { return sec; }
    operator struct tm()     const { return *::localtime(&sec); }
    operator ::std::string() const { return toString(); }
    operator long double()   const { return get(); }
    operator timespec()      const { timespec ret = {this->sec, nsec}; return ret; }

    template<typename T> ntime& operator= (const T& in)       { *this = ntime(in); return *this; }
    template<typename T> bool   operator==(const T& in) const { return *this == ntime(in); }
    template<typename T> bool   operator!=(const T& in) const { return *this != ntime(in); }
    template<typename T> bool   operator< (const T& in) const { return *this <  ntime(in); }
    template<typename T> bool   operator<=(const T& in) const { return *this <= ntime(in); }
    template<typename T> bool   operator> (const T& in) const { return *this >  ntime(in); }
    template<typename T> bool   operator>=(const T& in) const { return *this >= ntime(in); }
    template<typename T> ntime  operator+=(const T& in)       { *this += ntime(in); return *this; }
    template<typename T> ntime  operator-=(const T& in)       { *this -= ntime(in); return *this; }
    template<typename T> ntime  operator+ (const T& in) const { ntime ret; ret = *this + ntime(in); return ret; }
    template<typename T> ntime  operator- (const T& in) const { ntime ret; ret = *this - ntime(in); return ret; }

    void now();

    ::std::string toString() const;
    ::std::string toString(const ::std::string& fmt) const;
    void stringTo(const ::std::string& in);
    void stringTo(const ::std::string& in, const ::std::string& fmt);

private:
    void adjustment();
};

::std::ostream& operator<<(::std::ostream&, const ntime&);

/*--------1---------2---------3---------4---------5---------6---------7------*/

} // end namespace Time

#endif /* TIME_NTIME_H_ */
