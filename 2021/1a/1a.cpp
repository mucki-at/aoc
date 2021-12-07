#include <iostream>
#include <algorithm>
#include "aoc/parse_tuple.h"

template<typename iter>
std::tuple<size_t, size_t, size_t> updown(iter begin, iter end, size_t smooth)
{
    size_t higher = 0;
    size_t lower = 0;
    size_t equal = 0;
    for (auto i1 = begin, i2 = i1 + smooth; i2 < end; ++i1, ++i2)
    {
        if (*i2 > *i1) ++higher;
        else if (*i2 < *i1) ++lower;
        else ++equal;
    }
    return { higher, lower, equal };
}

int main(void)
{
    auto values = aoc::parse_tuples<int>("1a.txt");

    {
        auto [higher, lower, equal] = updown(values.begin(), values.end(), 1);

        std::cout << "singles" << std::endl;
        std::cout << "higher: " << higher << std::endl;
        std::cout << "lower: " << lower << std::endl;
        std::cout << "equal: " << equal << std::endl;
        std::cout << std::endl;
    }

    {
        auto [higher, lower, equal] = updown(values.begin(), values.end(), 3);

        std::cout << "triples" << std::endl;
        std::cout << "higher: " << higher << std::endl;
        std::cout << "lower: " << lower << std::endl;
        std::cout << "equal: " << equal << std::endl;
        std::cout << std::endl;
    }

    return 0;
}