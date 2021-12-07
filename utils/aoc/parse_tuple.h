#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

namespace aoc
{

template<typename Type, typename StringLike>
Type parse(StringLike&& string)
{
    std::istringstream strm(std::forward<StringLike>(string));
    Type t;
    strm >> t;
    return t;
}

template<typename... Types>
std::vector<std::tuple<Types...>> regex_tuples(std::istream& strm, const std::regex& rex, size_t max = size_t(-1))
{
    std::vector<std::tuple<Types...>> result;

    std::istreambuf_iterator<char> begin(strm), end;
    std::string content(begin, end);    // we have to buffer for regex to work
    std::sregex_iterator regBegin(content.begin(), content.end(), rex), regEnd;

    while (regBegin != regEnd)
    {
        if (result.size() >= max) return result;
        std::tuple<Types...> item;
        auto subs = regBegin->begin();
        std::apply([&subs](Types&... e)
            {
                int dummy[sizeof...(Types)] =
                {
                    ((e = parse<Types>((++subs)->str())), 0)...
                };
            },
            item);
        result.push_back(item);
        ++regBegin;
    }
    return result;
}




template<typename Type>
std::vector<Type> parse_tuples(std::istream& strm, size_t max = size_t(-1))
{
    std::vector<Type> result;

    while (!strm.eof())
    {
        if (result.size() >= max) return result;
        Type item;
        strm >> item;
        if (!strm.good()) return result;
        result.push_back(item);
    }
    return result;
}

template<typename... Types>
std::enable_if_t<
    std::integral_constant<bool, sizeof...(Types)-1>::value,
    std::vector<std::tuple<Types...>>
    >parse_tuples(std::istream& strm, size_t max = size_t(-1))
{
    std::vector<std::tuple<Types...>> result;

    while (!strm.eof())
    {
        if (result.size() >= max) return result;
        std::tuple<Types...> item;
        std::apply([&strm](auto&... e)
            {
                (strm >> ... >> e);
            },
            item
        );
        if (!strm.good()) return result;
        result.push_back(item);
    }
    return result;
}

template<typename... Types>
auto parse_tuples(const std::string& name, size_t max = size_t(-1))
{
    if (name == "-")
    {
        return parse_tuples<Types...>(std::cin, max);
    }
    else
    {
        std::fstream ifile(name);
        if (!ifile) throw std::runtime_error("Cannot open file " + name);
        return parse_tuples<Types...>(ifile, max);
    }
}

template<typename... Types>
auto regex_tuples(const std::string& name, const std::regex& rex, size_t max = size_t(-1))
{
    if (name == "-")
    {
        return regex_tuples<Types...>(std::cin, rex, max);
    }
    else
    {
        std::fstream ifile(name);
        if (!ifile) throw std::runtime_error("Cannot open file " + name);
        return regex_tuples<Types...>(ifile, rex, max);
    }
}




}