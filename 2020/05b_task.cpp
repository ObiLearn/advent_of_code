#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include <ext/util/pretty.hpp>

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

    std::string line;
    std::size_t max = 0;
    std::vector<size_t> ids;
    ids.resize(1000);
    while(std::getline(std::cin, line)) {
        ids.push_back(toId(line));
        max=std::max(max, ids.back());
    }

    std::vector<short> slots(max+1, 0);
    for (auto id : ids) {
        slots[id]=1;
    }

    auto it = std::find(slots.begin()+1, slots.end(), 1); // find first seat
    it = std::find(it, slots.end(), 0); // find empty seat

    using ext::util::pretty::operator<<;
    std::cout << "\nresult:" << std::distance(slots.begin(), it) << "\n";
}
