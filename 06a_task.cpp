#include <bits/c++config.h>
#include <string>
#include <iostream>

#include <ext/util/scoped_timer.hpp>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ext::util::scoped_timer time{};

    std::size_t result = 0;
    std::string line;

    std::set<std::string::value_type> chars;
    while(std::getline(std::cin, line)) {
        if (line.empty()) {
            result += chars.size();
            chars.clear();
        }

        for(std::string::value_type const c : line) {
            chars.insert(c);
        }
    }


    time.add_step("done");
    time.run();

    std::cout << "\nresult:" << result << "\n";
}
