#include "../util.hpp"

#include <iostream>
#include <regex>

auto parse_input(std::invocable<std::string const&> auto const& solve) {
    int res = 0;

    util::input_by_line([&](std::string const& line) -> void {
        res += solve(line);
    });

    return res;
}

int solve_part_1(std::string const& in) {
    std::regex mul_re("mul\\(([0-9]+),([0-9]+)\\)");
    int res = 0;
    auto it = in.begin();
    do {
        std::smatch mul_result;
        std::regex_search(it, in.end(), mul_result, mul_re);

        if (mul_result.size()) {
            it = mul_result[0].second;
            res += (util::int_from_iterators(mul_result[1].first, mul_result[1].second) *
                    util::int_from_iterators(mul_result[2].first, mul_result[2].second));
        } else
            it = in.end();
    } while (it != in.end());
    return res;
}

int main() {

    // part 1
    {
        auto res = parse_input(solve_part_1);
        std::cout << "part 1 result: " << res << std::endl;
    }
}
