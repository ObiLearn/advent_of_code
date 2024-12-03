#include "../util.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <ranges>
#include <unordered_set>
#include <vector>

#include <boost/algorithm/string.hpp>

auto parse_input() {
    std::vector<std::vector<int>> vec;

    util::input_by_line([&](std::string const& line) -> void {
        std::vector<std::string> strs;
        boost::algorithm::split(strs, line, [](const char x) {
            return x == ' ';
        });
        std::vector<int> ints(strs.size());
        std::transform(strs.begin(), strs.end(), ints.begin(), [](std::string const& x) {
            return util::int_from_iterators(x.begin(), x.end());
        });
        vec.push_back(std::move(ints));
    });

    return vec;
}

int main() {
    auto vecs = parse_input();

    // part 1
    {
        auto check_vec = [](std::vector<int> const& vec) {
            if (vec.size() == 0)
                return false;
            if (vec.size() == 1)
                return true;

            int last = vec[0];
            bool asc = vec[0] < vec[1];
            for (auto it = vec.begin() + 1; it != vec.end(); ++it) {
                auto curr = *it;
                if (asc && (curr < last))
                    return false;
                if (!asc && (curr > last))
                    return false;

                int abs = std::abs(curr - last);
                if (abs < 1 || abs > 3)
                    return false;

                last = curr;
            }
            return true;
        };

        int res = 0;
        for (auto const& vec : vecs) {
            if (check_vec(vec))
                res += 1;
        }
        std::cout << "result part 1: " << res << std::endl;
    }
    // part 2 - ranges unoptimized
    /*
    {
        auto check_range = [](std::ranges::random_access_range auto const& vec) {
            if(vec.size() == 0)
                return false;
            if(vec.size() == 1)
                return true;

            int last = vec[0];
            bool asc = vec[0] < vec[1];
            for (auto it = vec.begin()+1; it != vec.end(); ++it )
            {
                auto curr = *it;
                if (asc && (curr < last)) return false;
                if (!asc && (curr > last)) return false;

                int abs = std::abs(curr-last);
                if (abs < 1 || abs > 3)
                    return false;

                last = curr;
            }
            return true;
        };

        int res = 0;
        for (auto const& vec : vecs) {
            if (check_range(vec))
                res += 1;
            else {
                for(std::size_t i = 0; i < vec.size(); ++i) {
                    const auto filter_func = [&](auto &&pair){ return std::get<0>(pair) != i; };
                    auto view = vec | std::views::enumerate | std::views::filter(filter_func) | std::views::values;  // <-- only bidi range
                    if (check_range(view)) {
                        res += 1; break;
                    }
                }
            }
        }
        std::cout << "result part 2: " << res << std::endl;
    }
    */
    // part 2 - unoptimized copy:(
    {
        auto check_range = [](std::ranges::random_access_range auto const& vec) {
            if (vec.size() == 0)
                return false;
            if (vec.size() == 1)
                return true;

            int last = vec[0];
            bool asc = vec[0] < vec[1];
            for (auto it = vec.begin() + 1; it != vec.end(); ++it) {
                auto curr = *it;
                if (asc && (curr < last))
                    return false;
                if (!asc && (curr > last))
                    return false;

                int abs = std::abs(curr - last);
                if (abs < 1 || abs > 3)
                    return false;

                last = curr;
            }
            return true;
        };

        int res = 0;
        for (auto const& vec : vecs) {
            if (check_range(vec))
                res += 1;
            else {
                for (std::size_t i = 0; i < vec.size(); ++i) {
                    auto copy = vec;
                    copy.erase(copy.begin() + i);
                    if (check_range(copy)) {
                        res += 1;
                        break;
                    }
                }
            }
        }
        std::cout << "result part 2: " << res << std::endl;
    }
}
