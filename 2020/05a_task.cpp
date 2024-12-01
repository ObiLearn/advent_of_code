#include <string>
#include <iostream>

#include <ext/util/scoped_timer.hpp>

int compare(std::string const& first, std::string const& second) {
    auto index = 0;
    for(char c : first) {
        switch(c) {
            case 'R': if ( second[index] != 'R') return  1 ; break;
            case 'L': if ( second[index] != 'L') return -1 ; break;
            case 'B': if ( second[index] != 'B') return  1 ; break;
            case 'F': if ( second[index] != 'F') return -1 ; break;
            default: throw std::runtime_error("invalid arguemnt");
        }
        ++index;
    }
    return 0;
}

std::size_t toId(std::string const& in) {
    std::size_t rv = 0;
    for(char c : in) {
        rv = rv << 1;
        std::size_t b = 0;
        switch(c) {
            case 'B': b = 1; break;
            case 'R': b = 1; break;
            case 'F': b = 0; break;
            case 'L': b = 0; break;
            default: throw std::runtime_error("invalid arguemnt");
        }
        rv += b;
    }
    return rv;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ext::util::scoped_timer time{};

    std::string line;
    std::string max = "FFFFFFFLLL";
    while(std::getline(std::cin, line)) {
        if(compare(max, line) == -1) {
            std::swap(max,line);
        }
    }

    std::size_t result = toId(max);

    time.add_step("done");
    time.run();

    std::cout << "\nresult:" << result << "\n";
}
