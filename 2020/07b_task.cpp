#include <bits/c++config.h>
#include <iostream>

#include <string_view>
#include <charconv>

#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>


#include <ext/util/pretty.hpp>
#include <ext/util/scoped_timer.hpp>
#include <ext/util/string.hpp>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ext::util::scoped_timer timer{};

    std::vector<std::vector<std::string>> splitted;
    std::string line;
    while(std::getline(std::cin, line)) {
        if (line.empty()) continue;
        auto parts = ext::util::split_on_multiple(line, std::vector<std::string>{ " bags contain ", " bag, ", " bags, ", " bag.", " bags."});
        std::vector<std::string> item;
        for(auto const& str : parts) {
            item.push_back(std::string(str));
        }
        splitted.push_back(std::move(item));
    }
    timer.add_step("read and split input");

    std::vector<std::string_view> id_to_str;
    std::unordered_map<std::string_view, std::size_t> str_to_id;

    std::string invalid("INVALID");
    id_to_str.push_back(invalid);
    str_to_id[invalid] = 0;

    for (auto const& item : splitted) {
        id_to_str.push_back(item[0]);
        str_to_id[item[0]] = id_to_str.size() - 1;
    }
    timer.add_step("strings mapped to ids");


    using translation_t = std::vector<std::pair<std::size_t,std::size_t>>;
    std::vector<translation_t> translations(id_to_str.size());

    for (auto const& item : splitted) {

        translation_t translation;
        for(std::size_t i = 1; i < item.size(); ++i) {
            std::size_t num = 0;
            auto const & str = item[i];
            auto res = std::from_chars(str.data(), str.data() + str.size(), num);

            if(num == 0 && res.ec == std::errc::invalid_argument) {
                continue;
            }

            std::string_view name(res.ptr+1, str.size() - 1 - std::distance(str.data(), res.ptr));
            translation.emplace_back(std::pair<std::size_t, std::size_t>{str_to_id[name], num});
        }
        translations[str_to_id[item[0]]] = std::move(translation);
    }
    timer.add_step("translations created");


    //for (std::size_t index = 0; index < translations.size(); ++index)  {
    //    std::cout << id_to_str[index] << " contains: ";
    //    for(auto item : translations[index]) {
    //        std::cout << id_to_str[item.first] << " (" << item.second << "), ";
    //    }
    //    std::cout << "\n";
    //}

    std::vector<std::pair<std::size_t,std::size_t>> expand;

    std::size_t result = 0;
    expand.push_back(std::pair{str_to_id["shiny gold"],1});

    do  {


        auto const& item = expand.back();
        auto const& expanded = translations[item.first];
        auto const size = item.second;
        result += size;
        expand.pop_back();

        for(std::size_t i=0; i < size; ++i) {
            std::copy(expanded.begin(),expanded.end(), std::back_inserter(expand));
        }

    } while (!expand.empty());
    timer.add_step("bags collected");


    std::cout << "\nresult:" << result - 1 << "\n";
}
