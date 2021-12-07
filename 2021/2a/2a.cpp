#include <iostream>
#include <algorithm>
#include "aoc/parse_tuple.h"

int main(int argc, char** argv)
{
    auto values = aoc::parse_tuples<std::string, int>(argc >= 2 ? argv[1] : "-");

    {
        int x = 0;
        int y = 0;
        for (auto&& [direction, amount] : values)
        {
            if (direction == "forward") x += amount;
            else if (direction == "up") y -= amount;
            else if (direction == "down") y += amount;
            else throw std::runtime_error("Invalid direction '" + direction + "'");
        }

        std::cout << "chugga chugga chugga ..." << std::endl;
        std::cout << "Final X = " << x << std::endl;
        std::cout << "Final Y = " << y << std::endl;
        std::cout << "Franky Coefficient = " << x * y << " ... SUUUUPERRRR!" << std::endl;
        std::cout << std::endl;
    }



    {
        int x = 0;
        int y = 0;
        int aim = 0;
        for (auto&& [direction, amount] : values)
        {
            if (direction == "forward")
            {
                x += amount;
                y += aim * amount;
            }
            else if (direction == "up") aim -= amount;
            else if (direction == "down") aim += amount;
            else throw std::runtime_error("Invalid direction '" + direction + "'");
        }

        std::cout << "chugga chugga chugga V2 ..." << std::endl;
        std::cout << "Final X = " << x << std::endl;
        std::cout << "Final Y = " << y << std::endl;
        std::cout << "Revised Franky Coefficient = " << x * y << " ... SUUUUPERRRR!" << std::endl;
    }
}