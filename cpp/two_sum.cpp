#include <map>
#include <vector>
#include <tuple>
#include <iostream>


std::tuple<int, int> two_sum(const std::vector<int> ns, const int t)
{
    std::map<int, std::size_t> m;

    for (std::size_t i = 0; i < ns.size(); ++ i)
    {
        const int other_value = t - ns[i];

        if (m.find(other_value) != m.end())
        {
            return { i, m[ns[i]] };
        }

        m[ns[i]] = i;
    }

    return { -1, -1 };
}


int main(int argc, char** argv)
{
    const int t = 7;
    const std::vector<int> ns = { 4, 5, 1, 3, 8 };

    const std::tuple<int, int> answer = two_sum(ns, t);

    std::cout << '[' << std::get<0>(answer) << ", " <<  std::get<1>(answer) << ']' << std::endl;

    return 0;
}

