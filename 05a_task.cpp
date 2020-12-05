#include <string>
#include <iostream>

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
    std::string line;
    std::size_t result = 0;
    while(std::getline(std::cin, line)) {
        result=std::max(result, toId(line));
    }
    std::cout << "\nresult:" << result << "\n";
}
