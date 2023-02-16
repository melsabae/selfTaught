#include "return.h"


//namespace rc
//{
//    rc_t return_code_success(const int success)
//    {
//        return { success, {} };
//    }
//
//
//    rc_t return_code_failure(const int failure, const std::string& desc)
//    {
//#ifdef RETURN_CODE_ONLY_INT
//        return { failure, {} };
//        (void) desc;
//#else
//        return { failure, { desc } };
//#endif
//    }
//
//
//    rc_t return_code_failure_chain(rc_t& r, const std::string& desc)
//    {
//#ifdef RETURN_CODE_ONLY_INT
//        return r;
//        (void) desc;
//#else
//        std::get<1>(r).emplace_front(desc);
//        return r;
//#endif
//    }
//};

