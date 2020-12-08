#include <bits/c++config.h>
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

using memory_t = std::vector<std::pair<cmd,std::int32_t>>;

std::pair<std::size_t,std::size_t> simulate(memory_t const& memory){
    std::unordered_set<std::size_t> visited;
    std::size_t current=1;
    std::int64_t acc=0;

    while (true) {
        if(!visited.empty() && visited.find(current) != visited.end()) {
            break;
        }
        visited.insert(current);

        if(current >= memory.size()) {
            return {acc, current};
        }

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
                using ext::util::pretty::operator<<;
                std::cout << current << " found in visited" << std::endl;
                std::cout << visited << std::endl;
                throw std::runtime_error("invalid input");
            }
        }

    }

    return {acc, current};
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ext::util::scoped_timer timer{};


    std::vector<std::pair<cmd,std::int32_t>> memory;
    memory.emplace_back(std::pair{cmd::invalid,0});
    std::string line;
    while(std::getline(std::cin, line)) {
        auto cmd_view = std::string_view(line.data(), 3);
        auto num_view = std::string_view(line.data()+5, line.size()-5);

        int num = 0;
        std::from_chars(num_view.data(), num_view.data()+num_view.size(),num);
        if (line[4] == '-') {
            num *= -1;
        }

        memory.emplace_back(std::pair{v2e(cmd_view), num});
    };

    timer.add_step("input read");

    std::size_t result = 0;
    std::size_t current = 0;

    for(std::size_t i = 1; i < memory.size(); ++i) {

        auto cell = memory[i];

        switch (cell.first) {
            case cmd::jmp: memory[i].first = cmd::nop; break;
            case cmd::nop: memory[i].first = cmd::jmp; break;
            default: continue;
        }

        std::tie(result, current) = simulate(memory);

        if (current == memory.size()) break;

        memory[i] = cell;

    }


    timer.add_step("simulation done");
    std::cout << "\nresult:" << result << "\n";
}
