#include <iostream>
#include <unordered_map>

#include "solutions.hpp"
#include "util.hpp"
#include "trie.hpp"

static const std::unordered_map<std::string, char> digit_to_value
{
    {"one", '1'},
    {"two", '2'},
    {"three", '3'},
    {"four", '4'},
    {"five", '5'},
    {"six", '6'},
    {"seven", '7'},
    {"eight", '8'},
    {"nine", '9'}
};

static const std::vector<std::string> digits {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

[[nodiscard]] char first_integral(std::string s, const Trie<char>& t, bool reverse) noexcept
{
    if (s.empty()) { return '0'; }
    if (!reverse) {
        std::reverse(s.begin(), s.end());
    }

    std::string curr_digit{};
    for (char c = s.back(); !s.empty(); c = s.back())
    {
        s.pop_back();
        if (std::isdigit(c))
        {
            // Ignore everything preceding, this is our next definitive integral
            return c;
        }

        switch (t.search(curr_digit + c))
        {
            case SearchResult::NOT_PRESENT:
                curr_digit = std::string{curr_digit[curr_digit.length() - 1]} + c;
                break;
            case SearchResult::NON_TERMINAL:
                curr_digit += c;
                break;
            case SearchResult::TERMINAL:
                curr_digit += c;
                if (reverse)
                {
                    std::reverse(curr_digit.begin(), curr_digit.end());
                }

                return digit_to_value.find(curr_digit)->second;
            default:
                return '0';
        }
    }
    return '0';
}

/**
 * Extracts a two-digit integral from a string, using the first and last integral
 * @param s: The string to extract from
 * @param ft: Forward trie
 * @param rt: Backward trie
 * @return: The extracted integral
 */
[[nodiscard]] int extract_integral(std::string& s, const Trie<char>& ft, const Trie<char>& rt) noexcept
{
    auto integral = std::string{first_integral(s, ft, false)} + first_integral(s, rt, true);
    return std::stoi(integral);
}

void day_one()
{
    std::size_t sum{};
    auto lines = get_file_contents("inputs/1/input.txt");

    std::vector<std::string> rev_digits{};
    std::transform(digits.begin(), digits.end(), std::back_inserter(rev_digits), [](const std::string& s)
    {
        std::string rs{};
        std::reverse_copy(s.begin(), s.end(), std::back_inserter(rs));
        return rs;
    });
    Trie<char> forward_t{digits};
    Trie<char> backward_t{rev_digits};

    for (auto& line : lines)
    {
        sum += extract_integral(line, forward_t, backward_t);;
    }

    std::cout << "Sum of all calibration values: " << sum << "\n";
}