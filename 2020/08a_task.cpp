#include <iostream>
#include <string>
#include <string_view>
#include <charconv>

#include <algorithm>

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>

#include <ext/util/pretty.hpp>
#include <ext/util/scoped_timer.hpp>
#include <ext/util/string.hpp>

enum class cmd : short {
    invalid,
    acc,
    jmp,
    nop,
};

std::string_view e2v(cmd const e) {
    switch (e) {
        case cmd::acc: return "acc";
        case cmd::jmp: return "jmp";
        case cmd::nop: return "nop";
        default: return "invalid";
    }
}

cmd v2e(std::string_view const& v) {
    if (v == "acc") {
        return cmd::acc;
    } else if ( v== "jmp" ){
        return cmd::jmp;
    } else if ( v== "nop" ){
        return cmd::nop;
    }

    return cmd::invalid;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ext::util::scoped_timer timer{};


    std::vector<std::pair<cmd,std::int32_t>> memory;
    memory.emplace_back(std::pair{cmd::invalid,0});
    std::string line;
    while(std::getline(std::cin, line)) {
        //std::cout << "<< " << line << std::endl;

        auto cmd_view = std::string_view(line.data(), 3);
        auto num_view = std::string_view(line.data()+5, line.size()-5);

        int num = 0;
        std::from_chars(num_view.data(), num_view.data()+num_view.size(),num);
        if (line[4] == '-') {
            num *= -1;
        }

        memory.emplace_back(std::pair{v2e(cmd_view), num});

        using ext::util::pretty::operator<<;
        //std::cout << (int) memory.back().first << " "  << memory.back().second << std::endl;
    };
    timer.add_step("input read");

    std::unordered_set<std::size_t> visited;
    std::size_t current=1;
    std::int64_t acc=0;

    while (true) {
        if(!visited.empty() && visited.find(current) != visited.end()) {
            std::cout << current << " found in visited" << std::endl;
            //using ext::util::pretty::operator<<;
            //std::cout << visited << std::endl;
            break;
        }
        visited.insert(current);

        auto[cmd,num] = memory.at(current);

        switch(cmd) {
            case cmd::jmp: {
                current += num;
                break;
            }
            case cmd::acc: {
                acc += num;
                current++;
                break;
            };
            case cmd::nop: {
                ++current;
                break;
            }
            case cmd::invalid: {
                std::cout << current << " found in visited" << std::endl;
                using ext::util::pretty::operator<<;
                std::cout << visited << std::endl;
                throw std::runtime_error("invalid input");
            }
        }

    }
    timer.add_step("simulation done");

    std::size_t result = acc;
    std::cout << "\nresult:" << result << "\n";
}
