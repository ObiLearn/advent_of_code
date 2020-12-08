#include <algorithm>
#include <iterator>
#include <optional>
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
    bool first = true;

    std::set<std::string::value_type> current_set;
    std::set<std::string::value_type> new_set;
    while(std::getline(std::cin, line)) {
        if (line.empty()) {
            result += current_set.size();
            current_set.clear();
            new_set.clear();
            first = true;
            continue;
        }

        if(first) {
            first = false;
            for(std::string::value_type const c : line) {
                current_set.insert(c);
            }
        } else {
            for(std::string::value_type const c : line) {
                new_set.insert(c);
            }


            std::set<std::string::value_type> intersected;
            std::set_intersection(
                current_set.begin(), current_set.end(),
                new_set.begin(), new_set.end(),
                std::inserter(intersected, intersected.begin())
            );
            new_set.clear();
            current_set = std::move(intersected);
        }
    }


    time.add_step("done");
    time.run();

    std::cout << "\nresult:" << result << "\n";
}
