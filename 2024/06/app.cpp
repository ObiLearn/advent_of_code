#include "../util.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <unordered_set>
#include <vector>

#include <boost/algorithm/string.hpp>


struct position {
    std::size_t x = 0;
    std::size_t y = 0;
};

enum struct direction : std::uint8_t {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

constexpr direction turn_right(direction dir) {
    return direction((std::uint8_t(dir) + 1) % 4);
}

static_assert(turn_right(direction::NORTH) == direction::EAST );
static_assert(turn_right(direction::EAST) == direction::SOUTH );
static_assert(turn_right(direction::SOUTH) == direction::WEST );
static_assert(turn_right(direction::WEST) == direction::NORTH );

std::optional<position> move(position pos, direction dir, std::vector<std::string> const& m) {
    // returns new pos or nullpt if exiting the field
    auto max_y = m.size()-1;
    auto max_x = m.front().size()-1;
    switch (dir) {
        case direction::NORTH: {
            if (pos.y == 0) return std::nullopt;
            --pos.y;
            break;
        }
        case direction::EAST: {
            if (pos.x == max_x) return std::nullopt;
            ++pos.x;
            break;
        }
        case direction::SOUTH:
            if (pos.y == max_y) return std::nullopt;
            ++pos.y;
            break;
        case direction::WEST:
            if (pos.x == 0) return std::nullopt;
            --pos.x;
            break;
    }
    return pos;
}

position find_guard(std::vector<std::string> const& matrix) {
    for (std::size_t y=0; y < matrix.size(); ++y) {
        for (std::size_t x=0; x < matrix[y].size(); ++x) {
            if (matrix[y][x] == '^') return { .x = x, .y = y};
        }
    }
    throw std::invalid_argument("input has not guard");
}

void print_matrix(std::vector<std::string> const& m) {
    std::cout << std::endl;
    for (auto const& line: m) std::cout << line << std::endl;
    std::cout << std::endl;
}


int main() {
    //auto m = util::read_lines("./input-small.txt");
    auto m = util::read_lines("./input.txt");
    auto const start_pos = find_guard(m);
    std::cout << "guard at: " << start_pos.x << " "  << start_pos.y << std::endl;
    // part 1
    {
        int result = 1;
        auto pos = std::optional(start_pos);
        m[pos->y][pos->x] = 'X';
        direction dir = direction::NORTH;
        while(pos) {
            //std::cout << "current pos: " << pos->x << " " << pos->y
            //          << " direcetion: " << int(dir)
            //          << " count: " << result << std::endl;
            //print_matrix(m);
            auto new_pos = move(pos.value(), dir, m);
            if(new_pos && m[new_pos->y][new_pos->x] == '#') {
                dir = turn_right(dir);
                continue;
            }
            pos = new_pos;
            if(m[pos->y][pos->x] != 'X')
            {
                m[pos->y][pos->x] = 'X';
                ++result;
            }
        }
        std::cout << "part 1 :" << result << std::endl;
    }
    // part 2 -- pretty bad
    {

    }
}
