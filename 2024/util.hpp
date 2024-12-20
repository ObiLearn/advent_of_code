#pragma once

#include <charconv>
#include <concepts>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <thread>
#include <vector>

namespace util {

inline int int_from_chars(char const* begin, char const* end, bool check_ptr = true) {
    int num;
    std::string_view ar(begin, std::distance(begin, end));
    auto [ptr, ec] = std::from_chars(begin, end, num);
    if (ec == std::errc())
        return num;
    else {
        std::string_view arg(begin, std::distance(begin, end));
        auto err = std::make_error_code(ec);
        throw std::invalid_argument(std::format("ERROR: `{}` - given argument: `{}`", err.message(), arg));
    }

    if (check_ptr && ptr != end)
        throw std::runtime_error("input not fully matched");
}

inline int int_from_view(std::string_view view) {
    return int_from_chars(view.data(), view.data() + view.size());
}

inline int int_from_iterators(std::string::const_iterator begin, std::string::const_iterator end) {
    // NOTE - unfortunately `std::from_chars` is not able to take string iterators.
    // imo it should, I might sit on a broken implementation.
    // int var;
    // auto [ptr, ec] = std::from_chars(line.begin(), it, var); // <<-- no matching function to call
    /*
     * /usr/include/c++/14/charconv:552:5: note:   template argument deduction/substitution failed:
       app.cpp:26:56: note:   cannot convert ‘(& line)->std::__cxx11::basic_string<char>::begin()’ (type
     ‘std::__cxx11::basic_string<char>::const_iterator’) to type ‘const char*’ 26 |             auto [ptr, ec] =
     std::from_chars(line.begin(), it, var); // <<-- no matching function to call
     */
    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2007r0.html

    // auto offset = std::distance(line.begin(), it);
    // char const* begin = line.data();
    // std::string_view view_a(begin, offset);
    return int_from_chars(&*begin, &*end); // hack hack
}

inline void input_by_line(std::invocable<std::string&> auto const& cb, std::filesystem::path path = std::filesystem::current_path() / "input.txt" ) {
    // use memory mapped files for real speed
    std::ifstream ifs(path, std::ios::in);
    if (!ifs.is_open())
        throw std::runtime_error("could not open input.txt");
    ifs.exceptions(std::ifstream::badbit);

    std::string line;
    while (std::getline(ifs, line)) cb(line);

    return;
}

inline std::string read_file(std::filesystem::path path = std::filesystem::current_path() / "input.txt") {
    std::ifstream ifs(path);
    std::string str;

    ifs.seekg(0, std::ios::end);
    str.reserve(ifs.tellg());
    ifs.seekg(0, std::ios::beg);
    str.assign((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    return str;
}

inline std::vector<std::string> read_lines(std::filesystem::path path = std::filesystem::current_path() / "input.txt") {
    std::vector<std::string> lines;
    input_by_line([&lines](std::string& line) {
        lines.push_back(std::move(line));
    }, std::move(path));
    return lines;
}

// for debuging
inline void sleep_for_secs(int secs) {
    std::this_thread::sleep_for(std::chrono::seconds{secs});
}

template <typename T, typename A>
inline void print_vec(std::string what, std::vector<T, A> vec) {
    // std::println("{}: {}", what, vec); // it could be so easy...
    std::cout << what << ": ";
    for (auto const& item : vec) std::cout << item << " ";
    std::cout << "\n";
}

} // namespace util
