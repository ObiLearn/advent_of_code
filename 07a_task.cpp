#include <bits/c++config.h>
#include <cmath>
#include <iterator>
#include <string_view>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>

#include <charconv>
#include <ios>
#include <cassert>

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
        //using ext::util::pretty::operator<<;
        //std::cout << item << std::endl;

        translation_t translation;
        for(std::size_t i = 1; i < item.size(); ++i) {
            std::size_t num;
            auto const & str = item[i];
            auto res = std::from_chars(str.data(), str.data() + str.size(), num);
            std::string_view name(res.ptr+1, str.size() - 1 - std::distance(str.data(), res.ptr));

            //std::cout << "name: '" << name << "' num: " << num << std::endl;

            translation.emplace_back(std::pair<std::size_t, std::size_t>{str_to_id[name], num});
        }
        //using ext::util::pretty::operator<<;
        //std::cout << translation << std::endl;
        translations[str_to_id[item[0]]] = std::move(translation);
    }
    timer.add_step("translations created");

    std::vector<std::set<std::size_t>> contained_in_map(translations.size());
    for(std::size_t found_in=1; found_in < translations.size(); ++found_in) {
        for(auto const& pair : translations[found_in]) {
            contained_in_map[pair.first].insert(found_in);
        }
    }
    timer.add_step("created mapping from id to set which contains id ");


    std::unordered_set<std::size_t> reaches;
    std::unordered_set<std::size_t> expand;
    expand.insert(str_to_id["shiny gold"]);

    using ext::util::pretty::operator<<;

    std::size_t last_size = 1;

    while (reaches.size() != last_size) {
        last_size = reaches.size();
        std::unordered_set<std::size_t> expand_next;

        for(auto item : expand) {
            for (auto id : contained_in_map[item]) {
                if(reaches.find(item) == reaches.end()) {
                    expand_next.insert(id);
                }
            }
            reaches.insert(item);
        }

        expand = std::move(expand_next);
    }
    timer.add_step("graph expanded");


    std::size_t result = reaches.size() - 1; //the gold bag itself
    std::cout << "\nresult:" << result << "\n";
}
