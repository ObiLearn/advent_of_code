#include <vector>
#include <iostream>
#include <algorithm>

#include <ext/math/math_types.hpp>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    std::vector<std::string> string_array;
    std::size_t n = 0;

    while(std::getline(std::cin, line)) {
        if ( n == 0 ) {
            n = line.size();
        } else {
            if ( n != line.size() ) {
                return 1;
            }
        }

        string_array.push_back(line);
    }

    std::size_t m = string_array.size();
    ext::math::dynamic_matrix<short,true,true> matrix(m,n);
    matrix.init_all_to(0);


    for(std::size_t i = 0; i < m; i++) {
        auto const& line = string_array[i];
        for(std::size_t j = 0; j < line.size(); j++) {
            matrix.set(i,j,  line[j] == '#' ? 1 : 0);
        }
    }


    int result = 1;
    std::vector<std::pair<std::size_t, std::size_t>> pairs = {
        {1,1}, {3,1}, {5,1}, {7,1}, {1,2}
    };

    for(auto const& pair : pairs) {
        int tmp = 0;
        std::size_t j = 0;
        for(std::size_t i = 0; i < m; i += pair.second) {
            tmp += matrix.get(i,j%n);
            j += pair.first;
        }
        result *= tmp;
    }

    std::cout << "result: " << result << std::endl;
}
