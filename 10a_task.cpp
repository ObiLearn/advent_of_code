#include <bits/c++config.h>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <charconv>

#include <algorithm>

#include <vector>

#include <ext/util/pretty.hpp>
#include <ext/util/scoped_timer.hpp>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ext::util::scoped_timer timer{};

    std::size_t preamble_len = 25;

    std::vector<std::size_t> input;
    input.reserve(110);

    std::string line;
    while(std::getline(std::cin, line)) {
        input.push_back(std::stoul(line));
    };
    timer.add_step("input read");

    std::sort(input.begin(), input.end());

    std::size_t one = 0;
    std::size_t three = 1; //1 for the last step
    std::size_t last = 0;
    for(auto i : input) {
        std::size_t diff = i - last;
        if (diff == 1) ++one;
        else if (diff  == 3) ++three;
        last = i;
    }

    timer.add_step("simulation done");

    std::cout << "\nresult: " << one << " " << three  << "\n";
    std::cout << "\nresult: " << one * three  << "\n";
}
