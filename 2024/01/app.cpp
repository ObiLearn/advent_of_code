#include "../util.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <ranges>
#include <string_view>
#include <unordered_set>
#include <vector>

std::tuple<std::vector<int>, std::vector<int>> parse_input() {

    std::vector<int> vec_a, vec_b;

    util::input_by_line([&](std::string const& line) -> void {
        auto it = std::find_if(line.begin(), line.end(), [](const char x) {
            return std::isspace(x);
        });
        {
            if (it == line.end())
                throw std::runtime_error("invalid input");

            // NOTE - unfortunately `std::from_chars` is not able to take string iterator.
            // imo it should, I might sit on a broken implementation.
            //int var;
            //auto [ptr, ec] = std::from_chars(line.begin(), it, var); // <<-- no matching function to call
            /*
             * /usr/include/c++/14/charconv:552:5: note:   template argument deduction/substitution failed:
               app.cpp:26:56: note:   cannot convert ‘(& line)->std::__cxx11::basic_string<char>::begin()’ (type ‘std::__cxx11::basic_string<char>::const_iterator’) to type ‘const char*’
                  26 |             auto [ptr, ec] = std::from_chars(line.begin(), it, var); // <<-- no matching function to call
             */
            // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2007r0.html

            auto offset = std::distance(line.begin(), it);
            char const* begin = line.data();
            std::string_view view_a(begin, offset);
            vec_a.push_back(util::int_from_view(view_a));
        }

        it = std::find_if_not(it, line.end(), [](const char x) {
            return std::isspace(x);
        });
        {
            if (it == line.end())
                throw std::runtime_error("invalid input");
            auto offset = std::distance(line.begin(), it);
            char const* begin = line.data() + offset;
            std::string_view view_b(begin, line.size() - offset);
            vec_b.push_back(util::int_from_view(view_b));
        }

        return;
    });

    return std::tuple{std::move(vec_a), std::move(vec_b)};
}

int main() {
    auto [v1, v2] = parse_input();
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    // part 1 - simple
    {
        int res = 0;
        for (std::size_t i = 0; i < v1.size(); i++) res += std::abs(v1[i] - v2[i]);
        std::cout << res << std::endl;
    }
    // part 1 - rages
    {
        auto abs = [](auto a, auto b) {
            return std::abs(a - b);
        };
        auto tmp = std::views::zip_transform(abs, v1, v2);
        auto res = std::ranges::fold_right(tmp, 0, std::plus<>());
        std::cout << res << std::endl;
    }
    // part 2 - simple
    {
        std::map<int, int> m;
        for (auto num : v1) m[num] = 0;
        for (auto num : v2) {
            if (m.contains(num))
                m[num]++;
        }
        auto res = 0;
        for (auto it : m) res += it.first * it.second;
        std::cout << res << std::endl;
    }
    // part 2 - simple - faster
    {
        std::unordered_set<int> s;
        for (auto num : v1) s.insert(num);
        auto res = 0;
        for (auto num : v2) {
            if (s.contains(num))
                res += num;
        }
        std::cout << res << std::endl;
    }
}
