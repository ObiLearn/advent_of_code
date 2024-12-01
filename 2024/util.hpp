#pragma once

#include <charconv>
#include <concepts>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string_view>
#include <thread>

namespace util {

inline int int_from_view(std::string_view view) {
    int num;
    auto [ptr, ec] = std::from_chars(view.data(), view.data() + view.size(), num);
    if (ec == std::errc::invalid_argument)
        throw std::invalid_argument("invalid arg");
    if (ec == std::errc::result_out_of_range)
        throw std::invalid_argument("out of ragne");
    return num;
}

inline void input_by_line(std::invocable<std::string const&> auto const& cb) {
    std::filesystem::path path = std::filesystem::current_path() / "input.txt";

    std::ifstream ifs;
    ifs.open(path);
    if(!ifs.is_open()) throw std::runtime_error("could not open input.txt");

    std::string line;
    while (std::getline(ifs, line))
        cb(line);

    return;
}

// for debuging
inline void sleep_for_secs(int secs) {
    std::this_thread::sleep_for(std::chrono::seconds{secs});
}

} //namespace util
