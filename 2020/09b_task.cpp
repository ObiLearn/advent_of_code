#include <bits/c++config.h>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <charconv>

#include <algorithm>

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>

#include <ext/util/pretty.hpp>
#include <ext/util/scoped_timer.hpp>
#include <ext/util/string.hpp>
#include <ext/algorithm/knapsack.hpp>

bool findPair(std::size_t begin, std::size_t end, std::vector<std::size_t> const& code, std::size_t num) {
    for(std::size_t i = begin; i < end; i++) {
        auto outer = code[i];
        for(std::size_t j = begin; j < i; j++) {
            if( outer + code[j] == num) return true;
        }
    }
    return false;
}

struct foo {
    std::size_t i;
    std::size_t j;
    std::size_t k;
};

std::set<std::size_t> findNumbers(std::vector<std::size_t> const& code, std::size_t num) {
    std::set<std::size_t> rv;
    std::cerr << "test1" << std::endl;


    for(auto it = code.begin(); it != code.end(); ++it) {
        std::size_t count = 0;
        for (auto current = it; it != code.end(); ++current) {
            if(*current >= num) break;
            count += *current;
            if(count == num) {
                std::copy(it, current +1, std::inserter(rv, rv.begin()));
                break;
            }
        }
    }


    return rv;
}

int main() {

    std::vector<foo> blarg(1000 * 1000);
    std::vector<foo> blargw(0);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ext::util::scoped_timer timer{};

    std::size_t preamble_len = 25;

    std::vector<std::size_t> code;
    code.reserve(1000);

    std::string line;
    while(std::getline(std::cin, line)) {
        code.push_back(std::stoul(line));
    };
    timer.add_step("input read");

    std::size_t result = 0;
    for(std::size_t current = preamble_len; current < code.size(); current++) {
        if(!findPair(current - preamble_len, current, code, code[current])) {
            result = code[current];
            break;
        }
    }
    std::cout << "\nresult part one : " << result << "\n";

    std::cout << "calling find numbers" << std::endl;
    auto invalid = findNumbers(code, result);

    using ext::util::pretty::operator<<;
    std::cout << invalid << std::endl;

    timer.add_step("simulation done");
    std::cout << "\nfirst, last: " << *invalid.begin() << " - " << *invalid.rbegin() << "\n";
    std::cout << "\nresult: " << *invalid.begin() + *invalid.rbegin() << "\n";
}
