#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> numbers;

    std::string input;
    while(std::getline(std::cin, input)) {
        numbers.push_back(std::stoi(input));
    }

    std::sort(numbers.begin(), numbers.end());

    for (auto const& i : numbers) {
        for (auto const& j : numbers) {
            for (auto const& k : numbers) {
                if ( i + j + k == 2020) {
                    std::cout << i << " "
                              << j << " "
                              << k << " "
                              << i * j * k << "\n";
                    return 0;
                }
            }
        }
    }
}
