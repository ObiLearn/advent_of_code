#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <charconv>

#include <ext/util/string.hpp>

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

std::set<std::string> required = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

bool is_digit(char c) {
    return (c >= '0' && c <= '9');
}

bool is_hexchar(char c) {
    if(is_digit(c)) return true;
    return (c >= 'a' && c <= 'f');
}


std::size_t checkItem(std::string const& item){
    //std::cout << item << std::endl;
    std::string_view view;
    if(item.size() > 4) {
        view = std::string_view(item.data() + 4, item.size() - 4);
    }

    try {
        if(ext::util::starts_with(item,"byr") && view.size() == 4) {
            int year=0;
            std::from_chars(view.begin(), view.end(), year);

            if(year >= 1920 && year <= 2002) {
                //std::cout << year << std::endl;
                return 1;
            }
        } else if(ext::util::starts_with(item,"iyr") && view.size() == 4) {
            int year=0;
            std::from_chars(view.begin(), view.end(), year);

            if(year >= 2010 && year <= 2020) {
                //std::cout << year << std::endl;
                return 1;
            }
        } else if(ext::util::starts_with(item,"eyr") && view.size() == 4) {
            int year=0;
            std::from_chars(view.begin(), view.end(), year);
            //std::cout << year << std::endl;

            if(year >= 2020 && year <= 2030) {
                //std::cout << year << std::endl;
                return 1;
            }
        } else if(ext::util::starts_with(item,"hgt")) {
            int hgt=0;
            std::from_chars(view.begin(), view.end(), hgt);
            //std::cout << hgt << std::endl;

            if(view.size() == 4) {
                if( !(view[2] == 'i') || !(view[3] == 'n')) return 0;
                if(hgt >= 59 && hgt <= 76) return 1;
            }

            if(view.size() == 5) {
                if( !(view[3] == 'c') || !(view[4] == 'm')) return 0;
                if(hgt >= 150 && hgt <= 193) return 1;
            }
        } else if(ext::util::starts_with(item,"hcl") && view.size() == 7) {
            auto current = view.begin();
            if(*current != '#') return 0;
            for(++current; current != view.end(); ++current) {
                if ( !is_hexchar(*current) ) return 0;
            }
            //std::cout << "ishex" << std::endl;
            return 1;
        } else if(ext::util::starts_with(item,"ecl") && view.size() == 3) {
            std::vector<std::string> const allowed = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
            if(std::any_of(allowed.begin(), allowed.end(), [&](auto const& a){ return a == view; })) {
                //std::cout << "eye color" << std::endl;
                return 1;
            }
        } else if(ext::util::starts_with(item,"pid") && view.size() == 9) {
            for(char const c : view) {
                if ( !is_digit(c) ) return 0;
            }
            //std::cout << "9 digits" << std::endl;
            return 1;
        }
    } catch(...) {}

    return 0;
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::string> details;
    std::string line;

    std::size_t result = 0;
    while(std::getline(std::cin, line)) {
        if ( line.empty() ) {
            std::size_t found = 0;

            //using ext::util::operator<<;
            //std::cout << details << "\n";

            for(std::string const& item : details) {
                found += checkItem(item);
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
