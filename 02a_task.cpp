#include <vector>
#include <iostream>
#include <algorithm>

#include <charconv>
#include <ios>

#include <ext/util/scoped_timer.hpp>

struct candidate {
    std::size_t length;
    std::string::value_type const* pointer;
    };

std::size_t first_matches(
        std::string::value_type const c,
        std::vector<std::string> const& seperators,
        std::vector<candidate> positions) {

    std::size_t rv = 0;
    positions.clear();

    for(auto const& sep : seperators) {
        if ( sep.empty() ) continue;

        if ( c == sep.front() ) {
            auto const length = sep.size();
            if (length == 1) {
                return 1;
            } else {
                rv = std::max(rv, length);
                positions.push_back(candidate{length, sep.data()});
            }
        }
    }
    return rv;
}


std::vector<std::string_view> split(std::string const& to_split, std::vector<std::string> const& seperators = { " " }) {
    std::vector<std::string_view> rv;

    auto begin = to_split.begin();
    auto start = begin;
    auto current = begin;
    std::vector<candidate> positions;

    auto add_word = [&](){
        auto offset = std::distance(begin, start);
        auto pointer = to_split.data() + offset;
        auto length = std::distance(start, current);

        std::string_view part(pointer, length);

        rv.push_back(part);
    };

    while(current != to_split.end()) {
        auto length = first_matches(*current, seperators, positions);
        if(length == 0) {
            //no match
            current++;
        } else if ( length == 1 ) {
            add_word();
            current++;
            start = current;
        } else {
            throw std::logic_error("not implemented");
        }
    }

    if(start != current) {
        add_word();
    }

    return rv;
}

struct entry {
    int low;
    int high;
    char sym;
    std::string pass;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ext::util::scoped_timer timer{};

    std::vector<entry> entries(1000);
    std::string line;

    while(std::getline(std::cin, line)) {
        auto parts = split(line, std::vector<std::string>{ " ", "-", ":"});

        int low = std::stoi(std::string(parts[0]));
        int high = std::stoi(std::string(parts[1]));
        char c = parts[2].front();

        entries.push_back( entry{
                low, high, c, std::string(parts[4])
        });
    }

    timer.add_step("input parsed");

    std::size_t result = 0;
    for(auto const& entry : entries) {
        int hits = 0;
        for(const char c : entry.pass) {
            hits += (c == entry.sym) ? 1 : 0;
        }
        if ( hits >= entry.low && hits <= entry.high ) {
             ++result;
        }
    }
    std::cout << "\nresult:" << result << "\n";
}
