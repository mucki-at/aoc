#include <iostream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <valarray>
#include "aoc/parse_tuple.h"

int main(int argc, char** argv)
{
    auto values = aoc::regex_tuples<size_t, size_t, size_t, size_t>(argc >= 2 ? argv[1] : "-", std::regex("\\s*(\\d+),(\\d+) -> (\\d+),(\\d+)\\s*"));

    std::cout << "Number of values: " << values.size() << std::endl;
    
    std::vector<std::slice> lines;
    size_t width = 1000;
    size_t height = 1000;

    for (auto&& val : values)
    {
        auto x0 = std::get<0>(val);
        auto y0 = std::get<1>(val);
        auto x1 = std::get<2>(val);
        auto y1 = std::get<3>(val);


        if (y0 > y1)
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        if (y0 == y1) // horizontal
        {
            //std::tie(x0, x1) = std::minmax(x0, x1);
            if (x0 > x1) std::swap(x0, x1);
            lines.emplace_back(y0 * width + x0, x1 - x0 + 1, 1);
        }
        else if (x0 == x1) // vertical
        {
            lines.emplace_back(y0 * width + x0, y1 - y0 + 1, width);
        }
        else // diagonal
        {
            if (x1 > x0)    lines.emplace_back(y0 * width + x0, y1 - y0 + 1, width + 1);
            else            lines.emplace_back(y0 * width + x0, y1 - y0 + 1, width - 1);
        }
    }

    std::cout << "Lines: " << lines.size() << std::endl;

    std::valarray<size_t> field;
    field.resize(width*height, 0);

    for (auto&& line : lines)
    {
        auto ones = std::valarray<size_t>(1, line.size());
        field[line]+=ones;
    }

    auto crossings = std::count_if(std::begin(field), std::end(field), [](size_t v) { return v > 1; });
    std::cout << "Crossings: " << crossings << std::endl;


}

