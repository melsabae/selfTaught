#include <criterion/criterion.h>
#include "return.h"


Test(Test_RC, Test_RC_Success)
{
    const rc_t ret = rc::return_code_success(0);
    cr_assert(std::get<0>(ret) == 0);
    cr_assert(std::get<1>(ret).size() == 0);
}


Test(Test_RC, Test_RC_Failure)
{
    rc_t ret = rc::return_code_failure(-1, "");
    cr_assert(std::get<0>(ret) == -1);
    cr_assert(std::get<1>(ret).size() == 0);

    ret = rc::return_code_failure(-2, "todo");

    cr_assert(std::get<0>(ret) != -1);
    cr_assert(std::get<0>(ret) == -2);
    cr_assert(std::get<1>(ret).size() == 0);
}


Test(Test_RC, Test_RC_Chaining)
{
    rc_t ret = rc::return_code_failure(-3, "");

    // function will mutate and return the input ret, no need to capture it since we have a ref to it
    (void) rc::return_code_failure_chain(ret, "todo");
    (void) rc::return_code_failure_chain(ret, "todo2");

    cr_assert(std::get<0>(ret) != -1);
    cr_assert(std::get<0>(ret) != -2);
    cr_assert(std::get<0>(ret) == -3);

    cr_assert(std::get<1>(ret).size() == 0);
}

