#include <bits/c++config.h>
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

bool findPair(std::size_t begin, std::size_t end, std::vector<std::size_t> const& code) {

    auto num = code[end];

    for(std::size_t i = begin; i < end; i++) {
        auto outer = code[i];
        for(std::size_t j = begin; j < end; j++) {
            if( i == j ) continue;
            if( outer + code[j] == num) return true;
        }
    }

    return false;
}

int main() {
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
        if(!findPair(current - preamble_len, current, code)) {
            result = code[current];
            break;
        }
    }

    timer.add_step("simulation done");

    std::cout << "\nresult: " << result << "\n";
}
