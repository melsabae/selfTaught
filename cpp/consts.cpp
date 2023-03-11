#include <iostream>

constexpr double haha_hwat(const int x)
{
    return static_cast<double>(x + 17);
}


const double sol = 299'792'458; // just some constant that maybe compiles in as machine-code-literal
constexpr double sol2 = 299'792'458; // as good as a macro, which will compile in as machine-code-literal

// constinit applies to the evaluation of the value, not the variable, hence it is constinit const
constinit const static double sol3 = haha_hwat(55);


// may be expanded as a compile-time constant
constexpr double sol_scaled(const double n)
{
    return sol2 * n;
}

// must be expanded as a compile-time constant
consteval double sol_scaled2(const double n)
{
    return sol2 * n;
}

constexpr void mut_x(const int& x)
{
    // const is just a compiler hint, if the storage is not in ROM, then you can mutate it
    // this will segfault if x is actually non-mutable
    // this is even constexpr if we want
    auto& non_const_x = const_cast<int&>(x);
    non_const_x = x + 5;
}

int main(int argc, char** argv)
{
    //auto& non_const_sol = const_cast<double&>(sol);
    //non_const_sol = 77; // will sigsegv


    //constexpr double print_sol = sol; sol is not constexpr despite being const
    constexpr double print_sol2 = sol2;
    constexpr double print_scaled_sol = sol_scaled(0.00007);
    constexpr double print_scaled_sol2 = sol_scaled2(0.0007);

    // these can only exist if they were static or thread-local
    //constinit double xyz = sol_scaled(0.07);
    //constinit double xyz2 = sol_scaled2(0.07);


    std::cout << sol << std::endl;
    std::cout << sol2 << std::endl;
    //std::cout << print_sol << std::endl;
    std::cout << print_sol2 << std::endl;
    std::cout << print_scaled_sol << std::endl;
    std::cout << print_scaled_sol2 << std::endl;


    int x = 77;
    std::cout << x << std::endl;
    mut_x(x);
    std::cout << x << std::endl;

    std::cout << sol3 << std::endl;

    return 0;
}

