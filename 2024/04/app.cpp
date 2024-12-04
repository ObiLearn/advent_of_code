#include "../util.hpp"

#include <iostream>

int check_pos_part1(
    std::vector<std::string> const& m, std::size_t x, std::size_t y, std::size_t max_x, std::size_t max_y) {
    if (m[y][x] != 'X')
        return 0;

    int res = 0;
    // north
    if (int(y) - 3 >= 0 && m[y - 1][x] == 'M' && m[y - 2][x] == 'A' && m[y - 3][x] == 'S')
        ++res;
    // north-east
    if (int(y) - 3 >= 0 && x + 3 < max_x && m[y - 1][x + 1] == 'M' && m[y - 2][x + 2] == 'A' && m[y - 3][x + 3] == 'S')
        ++res;
    // east
    if (x + 3 < max_x && m[y][x + 1] == 'M' && m[y][x + 2] == 'A' && m[y][x + 3] == 'S')
        ++res;
    // south-east
    if (y + 3 < max_y && x + 3 < max_x && m[y + 1][x + 1] == 'M' && m[y + 2][x + 2] == 'A' && m[y + 3][x + 3] == 'S')
        ++res;
    // south
    if (y + 3 < max_y && m[y + 1][x] == 'M' && m[y + 2][x] == 'A' && m[y + 3][x] == 'S')
        ++res;
    // south-west
    if (y + 3 < max_y && int(x) - 3 >= 0 && m[y + 1][x - 1] == 'M' && m[y + 2][x - 2] == 'A' && m[y + 3][x - 3] == 'S')
        ++res;
    // west
    if (int(x) - 3 >= 0 && m[y][x - 1] == 'M' && m[y][x - 2] == 'A' && m[y][x - 3] == 'S')
        ++res;
    // north-west
    if (int(y) - 3 >= 0 && int(x) - 3 >= 0 && m[y - 1][x - 1] == 'M' && m[y - 2][x - 2] == 'A' &&
        m[y - 3][x - 3] == 'S')
        ++res;
    return res;
};

int solve_part_1(std::vector<std::string> const& input) {
    int res = 0;
    auto max_y = input.size();
    auto max_x = input.front().size();
    for (int y = 0; y < max_y; ++y) {
        for (int x = 0; x < max_x; ++x) {
            res += check_pos_part1(input, x, y, max_x, max_y);
        }
    }
    return res;
}

int check_pos_part2(
    std::vector<std::string> const& m, std::size_t x, std::size_t y, std::size_t max_x, std::size_t max_y) {
    if (m[y][x] != 'A')
        return 0;
    // M.S
    // .A.
    // M.S
    if (m[y - 1][x - 1] == 'M' && m[y - 1][x + 1] == 'S' && m[y + 1][x - 1] == 'M' && m[y + 1][x + 1] == 'S')
        return 1;
    // S.S
    // .A.
    // M.M
    if (m[y - 1][x - 1] == 'S' && m[y - 1][x + 1] == 'S' && m[y + 1][x - 1] == 'M' && m[y + 1][x + 1] == 'M')
        return 1;
    // M.M
    // .A.
    // S.S
    if (m[y - 1][x - 1] == 'M' && m[y - 1][x + 1] == 'M' && m[y + 1][x - 1] == 'S' && m[y + 1][x + 1] == 'S')
        return 1;
    // S.M
    // .A.
    // S.M
    if (m[y - 1][x - 1] == 'S' && m[y - 1][x + 1] == 'M' && m[y + 1][x - 1] == 'S' && m[y + 1][x + 1] == 'M')
        return 1;
    return 0;
};

int solve_part_2(std::vector<std::string> const& input) {
    int res = 0;
    auto max_y = input.size();
    auto max_x = input.front().size();
    for (int y = 1; y < max_y - 1; ++y) {
        for (int x = 1; x < max_x - 1; ++x) {
            res += check_pos_part2(input, x, y, max_x, max_y);
        }
    }
    return res;
}

int main() {
    auto input = util::read_lines();
    // part 1
    {
        auto res = solve_part_1(input);
        std::cout << "part 1 result: " << res << std::endl;
    }
    // part 2
    {
        auto res = solve_part_2(input);
        std::cout << "part 2 result: " << res << std::endl;
    }
}
