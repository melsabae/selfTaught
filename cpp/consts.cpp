#include <iostream>


const double sol = 299'792'458; // just some constant that maybe compiles in as machine-code-literal
constexpr double sol2 = 299'792'458; // as good as a macro, which will compile in as machine-code-literal


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

    return 0;
}

