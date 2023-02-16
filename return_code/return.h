#ifndef RETURN_CODE_H
#define RETURN_CODE_H


#include <tuple>
#include <string>
#include <iterator>
#include <deque>
#include <array>


struct return_code
{
    int c;

#ifdef RETURN_CODE_ONLY_INT
    std::array<std::string, 0> d;
#else
    std::deque<std::string> d;
#endif

    bool operator==(const int& left)
    {
        return left == c;
    }

    operator int() const
    {
        return c;
    }
};


typedef struct return_code rc_t;


//#ifdef RETURN_CODE_ONLY_INT
//#   include <array>
//    typedef std::tuple<int, std::array<std::string, 0>> rc_t;
//#else
//#   include <deque>
//    typedef std::tuple<int, std::deque<std::string>> rc_t;
//#endif
//
//
//namespace rc
//{
//    rc_t return_code_success(const int success);
//    rc_t return_code_failure(const int failure, const std::string& desc);
//    rc_t return_code_failure_chain(rc_t& r, const std::string& desc);
//};


#endif // RETURN_CODE_H

