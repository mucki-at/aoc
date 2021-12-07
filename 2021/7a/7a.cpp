#include <iostream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <valarray>
#include "aoc/parse_tuple.h"

template<typename container>
int sumDist(const container& values, typename container::value_type x)
{
    int sum = 0;
    for (auto&& v : values)
    {
        int dist = std::abs(v - x);
        sum += dist;
    }
    return sum;
}

template<typename container>
int sumDistSq(const container& values, typename container::value_type x)
{
    int sum = 0;
    for (auto&& v : values)
    {
        int dist = std::abs(v - x);
        sum += dist*(dist+1)/2;
    }
    return sum;
}

int main(int argc, char** argv)
{
    auto values = aoc::regex_tuples<int>(argc >= 2 ? argv[1] : "-", std::regex("(\\d+),?"));

    std::cout << "Number of values: " << values.size() << std::endl;

    std::sort(values.begin(), values.end());
    int minFuel = std::numeric_limits<int>::max();
    size_t median = values.size() / 2;
    for (int loc = values[median-2]; loc <= values[median+2]; ++loc)
    {
        int val = sumDist(values, loc);
        std::cout << "Fuel for " << loc << " = " << val << std::endl;
        minFuel = std::min(val, minFuel);
    }
    std::cout << "Minimum Fuel = " << minFuel << std::endl;
    std::cout << std::endl;

    minFuel = std::numeric_limits<int>::max();
    for (int loc = values.front(); loc <= values.back(); ++loc)
    {
        int val = sumDistSq(values, loc);
        std::cout << "Fuel(sq) for " << loc << " = " << val << std::endl;
        minFuel = std::min(val, minFuel);
    }
    std::cout << "Minimum Fuel(sq) = " << minFuel << std::endl;

}

