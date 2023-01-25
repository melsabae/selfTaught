#include <string>
#include <tuple>
#include <deque>
#include <iostream>


typedef std::tuple<int, std::deque<std::string>> return_code_t;


return_code_t
do_a_thing(void)
{
    if (true)
    {
        return { -__LINE__, { std::string(__FUNCTION__) + ":" + std::to_string(__LINE__) + ":this is a sample of a failure diagnostic - the if case is hardcoded true you dum" }};
    }

    return { 0, {} };
}


return_code_t
do_other_thing(void)
{
    return_code_t ret = do_a_thing();

    if (0 != std::get<int>(ret))
    {
        std::deque<std::string>& errors = std::get<1>(ret);
        errors.emplace_front( std::string(__FUNCTION__) + ":" + std::to_string(__LINE__) + ":prior errors, aborting");
    }

    return ret;
}


int main(int argc, char** argv)
{
    return_code_t ret = do_other_thing();

    const int& error_code = std::get<int>(ret);
    std::deque<std::string>& errors = std::get<1>(ret);

    if (0 != error_code)
    {
        for (const std::string& error: errors)
        {
            std::cout << error << std::endl << std::flush;
        }
    }

    return error_code;
}

