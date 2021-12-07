#include <iostream>
#include <algorithm>
#include <iomanip>
#include <array>
#include <valarray>
#include "aoc/parse_tuple.h"

struct Board
{
    std::array<size_t, 5> rows, cols;
    std::valarray<size_t> values;
    bool won = false;

    Board() :
        rows{ 0 },
        cols{ 0}
    {
        values.resize(rows.size()* cols.size(), 0);
    }

    template<typename Iterator>
    Board(Iterator& i) :
        rows{ 0 },
        cols{ 0 }
    {
        values.resize(rows.size()* cols.size(), 0);
        for (auto& v : values) v = *i++;
    }

    size_t Match(size_t num)
    {
        for (size_t row = 0; row < rows.size(); ++row)
        {
            for (size_t col = 0; col < cols.size(); ++col)
            {
                auto& v = values[row * cols.size() + col];
                if (v == num)
                {
                    v = 0;
                    rows[row]++;
                    cols[col]++;
                    if ((rows[row] == 5) || (cols[col] == 5))
                    {
                        won = true;
                        return values.sum() * num;
                    }
                }
            }
        }
        return size_t(-1);
    }
};

std::vector<size_t> readNumbers(std::istream& strm)
{
    std::vector<size_t> result;
    while (strm.good())
    {
        size_t val;
        strm >> val;
        if ((!strm.good()) || (strm.peek() != ',')) return result;
        strm.get();
        result.push_back(val);
    }
    return result;
}

int main(int argc, char** argv)
{
    std::ifstream ifile("4a.txt");

    auto numbers = readNumbers(ifile);
    auto values = aoc::parse_tuples<size_t>(ifile);

    std::vector<Board> boards;

    for (auto it = values.begin(); it != values.end();)
    {
        boards.emplace_back(it);
    }

    std::cout << numbers.size() << " numbers, and " << boards.size() << " boards. Let the games begin!!" << std::endl;

    size_t rank = 0;
    for (auto&& num : numbers)
    {
        for (auto& board : boards)
        {
            if (board.won) continue;

            auto win = board.Match(num);
            if (win != size_t(-1))
            {
                std::cout << "Winning score #" << rank++ << " is " << win << std::endl;
                //return 0;
            }
        }
    }

    std::cout << "No winner!" << std::endl;
}