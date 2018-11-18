/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * CException.h
 *
 *  Created on: 2015/05/05
 *      Author: xronia
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#ifndef EXCEPTION_EXCEPTION_H_
#define EXCEPTION_EXCEPTION_H_

#include <Logger/logger.h>
#include <cstdarg>
#include <string>

#include <stdexcept>
#include <sstream>

namespace Exception {

/*--------1---------2---------3---------4---------5---------6---------7------*/
class except {

};
/*--------1---------2---------3---------4---------5---------6---------7------*/
#define EXECPTION_CLASS_(CLASS_NAME_, BASE_NAME_)                           \
class CLASS_NAME_ : public BASE_NAME_, public except {                      \
public:                                                                     \
    (CLASS_NAME_)(const char* msg);                                         \
    (CLASS_NAME_)(const ::std::string& msg);                                \
                                                                            \
    (CLASS_NAME_)(                                                          \
            const ::std::string&,                                           \
            const ::std::string&,                                           \
            const uint,                                                     \
            const char*,                                                    \
            ...                                                             \
    );                                                                      \
    (CLASS_NAME_)(                                                          \
            const ::std::string&,                                           \
            const ::std::string&,                                           \
            const uint,                                                     \
            const ::std::string&                                            \
    );                                                                      \
                                                                            \
    virtual (~CLASS_NAME_)();                                               \
};

#define EXECPTION_CLASS_2_(CLASS_NAME_, BASE_NAME_)                         \
class CLASS_NAME_ : public BASE_NAME_ {                                     \
public:                                                                     \
    (CLASS_NAME_)(const char* msg);                                         \
    (CLASS_NAME_)(const ::std::string& msg);                                \
                                                                            \
    (CLASS_NAME_)(                                                          \
            const ::std::string&,                                           \
            const ::std::string&,                                           \
            const uint,                                                     \
            const char*,                                                    \
            ...                                                             \
    );                                                                      \
    (CLASS_NAME_)(                                                          \
            const ::std::string&,                                           \
            const ::std::string&,                                           \
            const uint,                                                     \
            const ::std::string&                                            \
    );                                                                      \
                                                                            \
    virtual (~CLASS_NAME_)();                                               \
};

/*--------1---------2---------3---------4---------5---------6---------7------*/

#define EXECPTION_FUNCTION_(CLASS_NAME_, BASE_NAME_, MESSAGE_)              \
CLASS_NAME_::CLASS_NAME_(const char* msg) : BASE_NAME_(msg) {               \
                                                                            \
}                                                                           \
                                                                            \
CLASS_NAME_::CLASS_NAME_(const ::std::string& msg) : BASE_NAME_(msg) {      \
                                                                            \
}                                                                           \
                                                                            \
CLASS_NAME_::CLASS_NAME_(                                                   \
        const ::std::string& file,                                          \
        const ::std::string& func,                                          \
        const uint    line,                                                 \
        const char*   fmt,                                                  \
        ...                                                                 \
) : BASE_NAME_(#MESSAGE_) {                                                 \
    ::Logger::logger& logger = ::Logger::logger::Instance();                \
    if(nullptr == fmt)                                                      \
        throw ::std::invalid_argument("nullptr exception");                 \
    ::std::string format = ::std::string(#MESSAGE_ " ") + fmt;              \
    va_list va;                                                             \
    va_start(va, fmt);                                                      \
    logger.Trace(::Logger::logger::EXCEPTION, file, func, line,             \
        format.c_str(), va);                                                \
    va_end(va);                                                             \
    CLASS_NAME_(logger.getLast().message);                                  \
}                                                                           \
                                                                            \
CLASS_NAME_::CLASS_NAME_(                                                   \
        const ::std::string& file,                                          \
        const ::std::string& func,                                          \
        const uint    line,                                                 \
        const ::std::string& message                                        \
) : BASE_NAME_(#MESSAGE_) {                                                 \
    ::Logger::logger& logger = ::Logger::logger::Instance();                \
    logger.Trace(::Logger::logger::EXCEPTION, file, func, line,             \
            ::std::string(#MESSAGE_ " ") + message);                        \
    CLASS_NAME_(logger.getLast().message);                                  \
}                                                                           \
                                                                            \
CLASS_NAME_::~CLASS_NAME_() {                                               \
                                                                            \
}

/*--------1---------2---------3---------4---------5---------6---------7------*/

EXECPTION_CLASS_(domain_error,      ::std::domain_error);
EXECPTION_CLASS_(invalid_argument,  ::std::invalid_argument);
EXECPTION_CLASS_(length_error,      ::std::length_error);
EXECPTION_CLASS_(out_of_range,      ::std::out_of_range);
EXECPTION_CLASS_(runtime_error,     ::std::runtime_error);
EXECPTION_CLASS_(range_error,       ::std::range_error);
EXECPTION_CLASS_(overflow,          ::std::overflow_error);
EXECPTION_CLASS_(underflow,         ::std::underflow_error);
/*--------1---------2---------3---------4---------5---------6---------7------*/
EXECPTION_CLASS_2_(nullpointer,     invalid_argument);
EXECPTION_CLASS_2_(size_mismatch,   length_error);
EXECPTION_CLASS_2_(memoryfull,      length_error);
EXECPTION_CLASS_2_(not_define,      runtime_error);
EXECPTION_CLASS_2_(multi_define,    runtime_error);
EXECPTION_CLASS_2_(fileIO_error,    runtime_error);
EXECPTION_CLASS_2_(timeout,         runtime_error);
EXECPTION_CLASS_2_(regex_error,     runtime_error);
EXECPTION_CLASS_2_(lock_failed,     runtime_error);

/*--------1---------2---------3---------4---------5---------6---------7------*/

} /* end namespace Exception */

#define EXCEPTION_EXCEPTION_H_CHAR_(CLASS_, ...)                            \
    throw CLASS_(__FILE__, __PRETTY_FUNCTION__, __LINE__,                   \
            ## __VA_ARGS__);

#define EXCEPTION_EXCEPTION_H_STRING_(CLASS_, MESSAGE_) {                   \
        ::std::stringstream __stream; __stream << MESSAGE_;                 \
        throw CLASS_(__FILE__,                                              \
        __PRETTY_FUNCTION__, __LINE__, __stream.str());                     \
}

#define EXCEPTION_EXCEPTION_H_0_ EXCEPTION_EXCEPTION_H_STRING_
#define EXCEPTION_EXCEPTION_H_1_ EXCEPTION_EXCEPTION_H_CHAR_
#define EXCEPTION_EXCEPTION_H_2_ EXCEPTION_EXCEPTION_H_CHAR_
#define EXCEPTION_EXCEPTION_H_3_ EXCEPTION_EXCEPTION_H_CHAR_
#define EXCEPTION_EXCEPTION_H_4_ EXCEPTION_EXCEPTION_H_CHAR_
#define EXCEPTION_EXCEPTION_H_5_ EXCEPTION_EXCEPTION_H_CHAR_
#define EXCEPTION_EXCEPTION_H_6_ EXCEPTION_EXCEPTION_H_CHAR_
#define EXCEPTION_EXCEPTION_H_7_ EXCEPTION_EXCEPTION_H_CHAR_
#define EXCEPTION_EXCEPTION_H_8_ EXCEPTION_EXCEPTION_H_CHAR_
#define EXCEPTION_EXCEPTION_H_9_ EXCEPTION_EXCEPTION_H_CHAR_

#define EXCEPTION_EXCEPTION_H_GET_MACRO_(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,     \
        NAME_,...) NAME_

#define EXCEPTION_EXCEPTION_H_THROW_(CLASS_, ...)                           \
        EXCEPTION_EXCEPTION_H_GET_MACRO_(__VA_ARGS__,                       \
                EXCEPTION_EXCEPTION_H_9_,                                   \
                EXCEPTION_EXCEPTION_H_8_,                                   \
                EXCEPTION_EXCEPTION_H_7_,                                   \
                EXCEPTION_EXCEPTION_H_6_,                                   \
                EXCEPTION_EXCEPTION_H_5_,                                   \
                EXCEPTION_EXCEPTION_H_4_,                                   \
                EXCEPTION_EXCEPTION_H_3_,                                   \
                EXCEPTION_EXCEPTION_H_2_,                                   \
                EXCEPTION_EXCEPTION_H_1_,                                   \
                EXCEPTION_EXCEPTION_H_0_)                                   \
                (CLASS_, __VA_ARGS__)

/*--------1---------2---------3---------4---------5---------6---------7------*/

#define DOMAIN_ERROR(...)       EXCEPTION_EXCEPTION_H_THROW_(::Exception::domain_error,     __VA_ARGS__)
#define INVALID_ARGUMENT(...)   EXCEPTION_EXCEPTION_H_THROW_(::Exception::invalid_argument, __VA_ARGS__)
#define LENGTH_ERROR(...)       EXCEPTION_EXCEPTION_H_THROW_(::Exception::length_error,     __VA_ARGS__)
#define OUT_OF_RANGE(...)       EXCEPTION_EXCEPTION_H_THROW_(::Exception::out_of_range,     __VA_ARGS__)
#define RUNTIME_ERROR(...)      EXCEPTION_EXCEPTION_H_THROW_(::Exception::runtime_error,    __VA_ARGS__)
#define RANGE_ERROR(...)        EXCEPTION_EXCEPTION_H_THROW_(::Exception::range_error,      __VA_ARGS__)
#define OVERFLOW(...)           EXCEPTION_EXCEPTION_H_THROW_(::Exception::overflow,         __VA_ARGS__)
#define UNDERFLOW(...)          EXCEPTION_EXCEPTION_H_THROW_(::Exception::underflow,        __VA_ARGS__)

/*--------1---------2---------3---------4---------5---------6---------7------*/
#define NULLPOINTER(...)        EXCEPTION_EXCEPTION_H_THROW_(::Exception::nullpointer,      __VA_ARGS__)
#define MEMORYFULL(...)         EXCEPTION_EXCEPTION_H_THROW_(::Exception::memoryfull,       __VA_ARGS__)
#define SIZE_MISMATCH(...)      EXCEPTION_EXCEPTION_H_THROW_(::Exception::size_mismatch,   __VA_ARGS__)
#define NOT_DEFINE(...)         EXCEPTION_EXCEPTION_H_THROW_(::Exception::not_define,       __VA_ARGS__)
#define MULTI_DEFINE(...)       EXCEPTION_EXCEPTION_H_THROW_(::Exception::multi_define,     __VA_ARGS__)
#define FILEIO_ERROR(...)       EXCEPTION_EXCEPTION_H_THROW_(::Exception::fileIO_error,     __VA_ARGS__)
#define TIMEOUT(...)            EXCEPTION_EXCEPTION_H_THROW_(::Exception::timeout,          __VA_ARGS__)
#define REGEX_ERROR(...)        EXCEPTION_EXCEPTION_H_THROW_(::Exception::regex_error,      __VA_ARGS__)
#define LOCK_FAILED(...)        EXCEPTION_EXCEPTION_H_THROW_(::Exception::lock_failed,      __VA_ARGS__)

/*--------1---------2---------3---------4---------5---------6---------7------*/

#endif /* EXCEPTION_EXCEPTION_H_ */
