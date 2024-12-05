#include "../util.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <unordered_set>
#include <vector>
#include <cassert>

auto parse_input() {
    std::multimap<int, int> mmap;
    std::vector<std::vector<int>> vecs;

    util::input_by_line([&](std::string const& line) -> void {
        if (line.contains('|')) {
            int pos = line.find('|');
            int num_before_num = util::int_from_iterators(line.begin(), line.begin() + pos);
            int num = util::int_from_iterators(line.begin() + pos + 1, line.end());
            mmap.emplace(num, num_before_num);
        } else if (line.contains(',')) {
            auto it = line.begin();
            auto sp = line.begin();
            auto end = line.end();
            std::vector<int> vec;
            while (sp != end) {
                sp = std::find(it, end, ',');
                int num = util::int_from_iterators(it, sp);
                vec.push_back(num);
                it = sp + 1;
            }
            vecs.push_back(std::move(vec));
        }
    });

    return std::tuple(std::move(mmap), std::move(vecs));
}

std::pair<bool, std::size_t> good_vec_part_1(std::vector<int> const& vec, std::multimap<int, int> const& map) {
    std::unordered_set<int> forbidden;
    for (std::size_t i = 0; i < vec.size(); ++i) {
        int num = vec[i];
        if (forbidden.contains(num))
            return {false, i};
        std::transform(
            map.lower_bound(num), map.upper_bound(num), std::inserter(forbidden, forbidden.begin()), [](auto const& x) {
                return x.second;
            });
    }
    return {true, 0};
}

void fix_vec_for_part2(std::vector<int>& vec, std::multimap<int, int> const& map) {
    auto [done, pos] = good_vec_part_1(vec, map);
    while (!done) {
        // move first not matching number one position towards the front
        auto from_start = vec.begin() + pos;
        auto from_end  = from_start + 1;
        auto to = from_start - 1; // vec.begin()
        std::rotate(to, from_start, from_end);
        std::tie(done, pos) = good_vec_part_1(vec, map);
    }
}

int main() {
    auto [mmap, vecs] = parse_input();
    // part 1
    {
        int result = 0;
        for (auto const& vec : vecs) {
            assert(vec.size() % 2 == 1);
            if (!good_vec_part_1(vec, mmap).first)
                continue;
            result += vec[(vec.size() / 2)];
        }
        std::cout << result << std::endl;
    }
    // part 2 -- pretty bad
    {
        int result = 0;
        for (auto& vec : vecs) {
            assert(vec.size() % 2 == 1);
            if (good_vec_part_1(vec, mmap).first)
                continue;
            fix_vec_for_part2(vec, mmap);
            result += vec[(vec.size() / 2)];
        }
        std::cout << result << std::endl;
    }
}
