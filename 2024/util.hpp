#pragma once

#include <charconv>
#include <concepts>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string_view>
#include <thread>
#include <format>

namespace util {

inline int int_from_chars(char const* begin, char const* end) {
    int num;
    auto [ptr, ec] = std::from_chars(begin, end, num);
    if (ec == std::errc()) return num;

    std::string_view arg(begin, std::distance(begin,end));
    auto err = std::make_error_code(ec);
    throw std::invalid_argument(std::format("ERROR: `{}` - given argument: `{}`", err.message(), arg));
}

inline int int_from_view(std::string_view view) {
    return int_from_chars(view.data(), view.data() + view.size());
}

inline int int_from_iterators(std::string::const_iterator begin, std::string::const_iterator end) {
    // NOTE - unfortunately `std::from_chars` is not able to take string iterator.
    // imo it should, I might sit on a broken implementation.
    //int var;
    //auto [ptr, ec] = std::from_chars(line.begin(), it, var); // <<-- no matching function to call
    /*
     * /usr/include/c++/14/charconv:552:5: note:   template argument deduction/substitution failed:
       app.cpp:26:56: note:   cannot convert ‘(& line)->std::__cxx11::basic_string<char>::begin()’ (type ‘std::__cxx11::basic_string<char>::const_iterator’) to type ‘const char*’
          26 |             auto [ptr, ec] = std::from_chars(line.begin(), it, var); // <<-- no matching function to call
     */
    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2007r0.html

    //auto offset = std::distance(line.begin(), it);
    //char const* begin = line.data();
    //std::string_view view_a(begin, offset);
    return int_from_chars(&*begin, &*end); // hack hack
}

inline void input_by_line(std::invocable<std::string const&> auto const& cb) {
    std::filesystem::path path = std::filesystem::current_path() / "input.txt";
    std::ifstream ifs(path, std::ios::in );
    if(!ifs.is_open()) throw std::runtime_error("could not open input.txt");
    ifs.exceptions(std::ifstream::badbit);

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
