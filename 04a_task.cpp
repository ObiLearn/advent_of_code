#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

#include <ext/util/show.hpp>

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

std::vector<std::string> prefixes = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };
std::set<std::string> required = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);


    std::vector<std::string> details;
    std::string line;

    std::size_t result = 0;
    while(std::getline(std::cin, line)) {
        if ( line.empty() ) {

            //using ext::util::operator<<;
            //std::cout << details << "\n";

            std::size_t found = 0;
            for(auto const& detail : details) {
                if (required.find(detail.substr(0,3)) != required.end()) {
                    ++found;
                }
            }

            if (found == required.size()) {
                ++result;
            }

            details.clear();
        }

        auto parts = split(line, std::vector<std::string>{" "});
        for(auto view : parts) {
            details.push_back(std::string(view));
        }
    }

    std::cout << "\nresult:" << result << "\n";
}
