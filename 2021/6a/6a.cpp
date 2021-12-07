#include <iostream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <valarray>
#include "aoc/parse_tuple.h"

template<typename T>
void printFish(size_t day, const std::valarray<T>& arr)
{
    std::cout << "Fish at day " << day << std::endl;
    size_t sum = 0;
    for (size_t i = 0; i < arr.size(); ++i)
    {
        std::cout << i << ": " << arr[i] << std::endl;
        sum += arr[i];
    }
    std::cout << "Total: " << sum << std::endl << std::endl;
}

int main(int argc, char** argv)
{
    auto values = aoc::regex_tuples<size_t>(argc >= 2 ? argv[1] : "-", std::regex("(\\d),?"));

    std::cout << "Number of values: " << values.size() << std::endl;

    std::valarray<size_t> fish;
    fish.resize(9, 0);
    for (auto&& v : values)
    {
        fish[v]++;
    }

    printFish(0, fish);

    size_t day = 0;
    while (day < 80)
    {
        fish = fish.cshift(1);
        fish[6] += fish[8];
        ++day;
    }
    printFish(day, fish);

    while (day < 256)
    {
        fish = fish.cshift(1);
        fish[6] += fish[8];
        ++day;
    }
    printFish(day, fish);
}

