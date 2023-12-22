//
// Created by bailey on 12/2/23.
//

#ifndef ADVENTOFCODE2023_INC_H
#define ADVENTOFCODE2023_INC_H

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

/**
 * Determines if the given string can be converted to an integral
 * @param s: The string to check
 * @return True if the string is integral, false otherwise
 */
[[nodiscard]] constexpr inline bool is_integral(const std::string_view s) noexcept
{
    return std::find_if_not(begin(s), end(s), [](char c)
    {
        return c >= '0' && c <= '9';
    }) == s.end();
}

/**
 * Consumes the contents of a given file, providing it as a vector of lines
 * @param file_path: The path to the file to retrieve
 * @return
 */
[[nodiscard]] std::vector<std::string> get_file_contents(const std::string& file_path) noexcept;

/**
 * Splits the given string into
 * @param s: The string to split
 * @param delimeter: The delimiter to split upon
 * @return: The vector of sub-strings
 */
[[nodiscard]] std::vector<std::string> str_split(std::string s, char delimeter);

/**
 * Extracts digits from a space separated list of digits
 * @tparam T: Type of digit to extract
 * @param s: The string source to extract from
 * @param sort: Whether the integers should be sorted
 * @return The integers extracted
 */
template <class T>
[[nodiscard]] std::vector<T> extract_digits(const std::string& s, bool sort = true) noexcept
{
    std::vector<T> nums{};

    for (const auto& num : str_split(s, ' '))
    {
        if (std::all_of(num.cbegin(), num.cend(), [](const auto c) { return std::isdigit(c) || c == '-'; }))
        {
            nums.push_back(static_cast<T>(std::stoull(num)));
        }
    }

    if (sort)
    {
        std::sort(nums.begin(), nums.end());
    }

    return nums;
}
#endif