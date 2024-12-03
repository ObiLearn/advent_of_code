#include "../util.hpp"

#include <iostream>
#include <regex>
#include <cassert>

std::regex const mul_re("mul\\(([0-9]+),([0-9]+)\\)");
std::regex const dont_re("don't\\(\\)");
std::regex const do_re("do\\(\\)");
std::regex const all_in_one_re(R"(mul\(([0-9]+),([0-9]+)\)|do\(\)|don't\(\))");

int sum_mults_in_range(std::string::const_iterator it, std::string::const_iterator end) {
    int res = 0;
    do {
        std::smatch match;
        if (std::regex_search(it, end, match, mul_re)) {
            it = match[0].second;
            res += (util::int_from_iterators(match[1].first, match[1].second) *
                    util::int_from_iterators(match[2].first, match[2].second));
        } else
            it = end;
    } while (it != end);
    return res;
}

int solve_part_1(std::string const& line) {
    return sum_mults_in_range(line.begin(), line.end());
}

std::string::const_iterator
    it_after_next(std::regex const& re, std::string::const_iterator begin, std::string::const_iterator end) {
    std::smatch match;
    if (std::regex_search(begin, end, match, re))
        return match[0].second;
    else
        return end;
}

int solve_part_2(std::string const& line) {
    auto res = 0;
    auto it = line.begin();

    while (it != line.end()) {
        auto dont_it = it_after_next(dont_re, it, line.end());
        res += sum_mults_in_range(it, dont_it);
        it = dont_it;
        if (it != line.end())
            it = it_after_next(do_re, it, line.end());
    }

    return res;
}

int main() {
    auto input = util::read_file();
    // part 1
    {
        auto res = solve_part_1(input);
        std::cout << "part 1 result: " << res << std::endl;
    }
    // part 2
    int res_part2 = 0;
    {
        auto res = solve_part_2(input);
        std::cout << "part 2 result: " << res << std::endl;
        res_part2 = res;
    }
    {
        auto const begin = std::sregex_iterator(input.begin(), input.end(), all_in_one_re);
        auto const end = std::sregex_iterator();
        int res = 0;
        bool add = true;
        for(auto it = begin; it != end; ++it)
        {
            auto m = *it; //match
            if(m.str().starts_with("don"))
                add = false;
            else if(m.str().starts_with("do"))
                add = true;
            else if (add) {
                // mul case
                res += std::stoi(m[1].str()) * std::stoi(m[2].str());
            }

        }
        std::cout << "part 2 result: " << res << std::endl;
        assert(res == res_part2);
    }
}
