#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    std::vector<int> numbers;

    std::string input;
    while(std::getline(std::cin, input)) {
        numbers.push_back(std::stoi(input));
    }

    std::sort(numbers.begin(), numbers.end());

    for (auto const& i : numbers) {
        for (auto const& j : numbers) {
            if ( i + j == 2020) {
                std::cout << i << " " << j << " " << i * j << "\n";
                return 0;
            }
        }
    }
}
