#include <iostream>
#include <format>
#include <functional>
#include <vector>
#include <optional>


// let y = f(x, z)
// let g(x) = f(x, z), for some fixed value of z
// let Y = {g(x) | x in X}
//      Y can be a set, it can be a single integer, it's not relevant to the remainder of this
// let f contain if/else logic based on z, that is z alters f's behavior
// then f's compiled code contains some performance penalty due to branching
//      shout out to compiler authors and CPU architects that have done work on optimizing these situations
// we want to show compile time branch deletion
//      std::bind/partial application, or wrapping/creating a functor, would still contain the branching overhead
// we create g that is templated via z, so the compiler generates variants of g based on static logic, thereby deleting some of the if/else branching
// we then introduce a lookup function, that applies facts of z to the template parameters, to retrieve the correct g
// the have then hoisted some amount of if/else branching out of f, and removed it at compile time
//      we have also given the compiler more information to optimize with
// the trade-offs:
//      pros:
//          repeated application of g should be faster than repeated application of f
//      cons:
//          more complex code base
//          larger code size
//          lookup function adds overhead (expected to be negligible)


template <size_t prefix_level>
int processing_function(const std::string& str)
{
    // let this function be analogous to g
    // let prefix_level be an element of z that we will branch on in if
    // then we demonstrate deleting that branching logic at compile time

    // essentially prefix_level denotes how much metadata we add, as f operates as a sort of logging function
    // then g is simply a function that has the correct prefix logic in it, without the if/else if/else
    // because we have 3 outcomes, the compiler generates 3 versions of g
    if constexpr(0 == prefix_level)
    {
        std::cout << str << std::endl;
    }
    else if constexpr(1 == prefix_level)
    {
        std::cout << std::format("{}:{}", __FUNCTION__, str) << std::endl;
    }
    else
    {
        std::cout << std::format("{}:{}:{}", __FUNCTION__, __LINE__, str) << std::endl;
    }

    return 0;
}


std::optional<std::function<int (const std::string&)>> get_function(const size_t prefix_level)
{
    // this would be the lookup function
    // it would be trivial to map all values of prefix_level to a valid function
    // but we opt to use a failure case here simply to allow it

    switch (prefix_level)
    {
        case 0: return processing_function<0>;
        case 1: return processing_function<1>;
        case 2: return processing_function<2>;
        // no default since we want this example to allow a failure case
    }

    return std::nullopt;
}


int long_running_function(const size_t prefix_level, const std::vector<std::string> data)
{
    // in this case: Y is an int, prefix_level is z, and data is X

    // do a single function lookup based on runtime parameters
    const std::optional<std::function<int (const std::string&)>> f = get_function(prefix_level);

    // handle the failure case
    if (not f)
    {
        return -__LINE__;
    }

    for (size_t i = 0; i < data.size(); ++ i)
    {
        std::ignore = f.value()(data[i]);
    }

    return 0;
}


int main(int argc, char** argv)
{
    // we use argc as a runtime parameter, since we can easily alter its value without recompilation
    // we then treat z = argc - 1
    const size_t prefix_level = argc - 1;

    // X
    const std::vector<std::string> data =
    {
          "ahoy"
        , "user"
    };

    // main = Y = map(g, X)
    return long_running_function(prefix_level, data);

    std::ignore = argv;
}

