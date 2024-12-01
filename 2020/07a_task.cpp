#include <iostream>

#include <string>
#include <string_view>
#include <charconv>

#include <unordered_map>
#include <unordered_set>
#include <set>

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
    //using ext::util::pretty::operator<<;
    //std::cout << id_to_str << std::endl;
    //std::cout << str_to_id << std::endl;


    using translation_t = std::vector<std::pair<std::size_t,std::size_t>>;
    std::vector<translation_t> translations(id_to_str.size());

    for (auto const& item : splitted) {
        //using ext::util::pretty::operator<<;
        //std::cout << item << std::endl;

        translation_t translation;
        for(std::size_t i = 1; i < item.size(); ++i) {
            std::size_t num = 0;
            auto const & str = item[i];
            auto res = std::from_chars(str.data(), str.data() + str.size(), num);

            if(num == 0 && res.ec == std::errc::invalid_argument) {
                //std::cout << "data: '" << str << "' can not be splitted " << num << std::endl;
                auto id = str_to_id[str];
                auto str = id_to_str[id];
                //std::cout << "using id:  " << id << " " << str << std::endl;
                translation.emplace_back(std::pair<std::size_t, std::size_t>{str_to_id[str], num});
                continue;
            }

            std::string_view name(res.ptr+1, str.size() - 1 - std::distance(str.data(), res.ptr));
            //std::cout << "name: '" << name << "' num: " << num << std::endl;
            translation.emplace_back(std::pair<std::size_t, std::size_t>{str_to_id[name], num});
        }
        using ext::util::pretty::operator<<;
        //std::cout << translation << std::endl;
        translations[str_to_id[item[0]]] = std::move(translation);
    }
    timer.add_step("translations created");
    //std::cout << "translation: " << translations << std::endl;

    std::vector<std::set<std::size_t>> contained_in_map(translations.size());
    for(std::size_t found_in=1; found_in < translations.size(); ++found_in) {
        for(auto const& pair : translations[found_in]) {
            if( pair.first == 0 ) continue; // invalid does not contain anything;
            //std::cout << found_in << std::endl;
            contained_in_map[pair.first].insert(found_in);
        }
    }
    timer.add_step("created mapping from id to set which contains id ");
    //std::cout << "cointained in map: " << contained_in_map << std::endl;

    //for (std::size_t index = 0; index < contained_in_map.size(); ++index)  {
    //    std::cout << id_to_str[index] << " contained in : ";
    //    for(auto item : contained_in_map[index]) {
    //        std::cout << id_to_str[item] << ", ";
    //    }
    //    std::cout << "\n";
    //}

    std::unordered_set<std::size_t> reaches;
    std::unordered_set<std::size_t> expand;
    expand.insert(str_to_id["shiny gold"]);
    //std::cout << "start id: " << *expand.begin() << std::endl;

    std::size_t last_size = 0;
    while (true) {
        last_size = reaches.size();
        std::unordered_set<std::size_t> expand_next;

        for(auto item : expand) {
            //std::cout << " -item- " << item << std::endl;
            for (auto id : contained_in_map[item]) {
                //std::cout << " -id- " << id << std::endl;
                if(reaches.empty() || reaches.find(item) == reaches.end()) {
                    expand_next.insert(id);
                    //using ext::util::pretty::operator<<;
                    //std::cout << expand_next << std::endl;
                }
            }
            reaches.insert(item);
        }

        expand = std::move(expand_next);
        if (reaches.size() == last_size) {
            break;
        }
        //std::cout << " -- next --  " << reaches.size() << " != " << last_size << std::endl;
    }
    timer.add_step("graph expanded");


    std::size_t result = reaches.size() - 1; //the gold bag itself
    std::cout << "\nresult:" << result << "\n";
}
