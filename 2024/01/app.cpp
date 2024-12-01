#include "../util.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <ranges>
#include <unordered_set>
#include <vector>

std::tuple<std::vector<int>, std::vector<int>> parse_input() {
    std::vector<int> vec_a, vec_b;

    util::input_by_line([&](std::string const& line) -> void {
        // vec_a
        auto it = std::find_if(line.begin(), line.end(), [](const char x) {
            return std::isspace(x);
        });
        if (it == line.end())
            throw std::runtime_error("invalid input");
        vec_a.push_back(util::int_from_iterators(line.begin(), it));
        // vec_b
        it = std::find_if_not(it, line.end(), [](const char x) {
            return std::isspace(x);
        });
        if (it == line.end())
            throw std::runtime_error("invalid input");
        vec_b.push_back(util::int_from_iterators(it, line.end()));
        // done
        return;
    });

    return std::tuple{std::move(vec_a), std::move(vec_b)};
}

int main() {
    auto [v1, v2] = parse_input();
    std::ranges::sort(v1);
    std::ranges::sort(v2);
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
    // no need to sort
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
