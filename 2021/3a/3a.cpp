#include <iostream>
#include <algorithm>
#include <iomanip>
#include "aoc/parse_tuple.h"

std::vector<size_t> count_ones(const std::vector<std::string>& values)
{
    std::vector<size_t> result;
    size_t width = values[0].size();
    result.resize(width, 0);

    for (auto&& v : values)
    {
        for (size_t i = 0; i < width; ++i)
        {
            if (v[i] == '1') ++result[i];
        }
    }
    return result;
}

size_t search(const std::vector<std::string>& values, bool high)
{
    size_t index = 0;
    size_t result = 0;

    auto begin = values.begin();
    auto end = values.end();

    size_t width = values[0].size();

    while (index < width)
    {
        result <<= 1;

        auto mid = std::lower_bound(begin, end, index, [](const std::string& val, size_t idx) { return val[idx] < '1'; });
        auto half = begin + (end - begin) / 2;
        
        bool chooseOnes = high ^ (mid > half);

        if (chooseOnes)
        {
            result |= 1;
            begin = mid;
        }
        else
        {
            end = mid;
        }

        ++index;

        if (end - begin <= 1)
        {
            // if we have only one value left record the final bits
            while (index < width)
            {
                result <<= 1;
                if (begin->at(index) == '1') result |= 1;
                ++index;
            }
            break;
        }
    }


    return result;
}

int main(int argc, char** argv)
{
    auto values = aoc::parse_tuples<std::string>(argc >= 2 ? argv[1] : "-");

    auto ones = count_ones(values);

    size_t gamma = 0;

    for (auto&& count : ones)
    {
        gamma <<= 1;
        if (count > values.size() / 2) gamma |= 1;
    }

    size_t epsilon = ~gamma & ((0x01 << ones.size()) - 1);

    std::cout << "Gamma   : " << gamma << " (0x" << std::hex << gamma << std::dec << ")" << std::endl;
    std::cout << "Epsilon : " << epsilon << " (0x" << std::hex << epsilon << std::dec << ")" << std::endl;
    std::cout << "Power   : " << epsilon*gamma << std::endl;

    std::sort(values.begin(), values.end());

    size_t co2 = search(values, true);
    size_t oxygen = search(values, false);

    std::cout << "CO2     : " << co2 << " (0x" << std::hex << co2 << std::dec << ")" << std::endl;
    std::cout << "Oxygen  : " << oxygen << " (0x" << std::hex << oxygen << std::dec << ")" << std::endl;
    std::cout << "Life    : " << oxygen * co2 << std::endl;



}