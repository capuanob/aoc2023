#include <functional>

#include "util.hpp"
[[nodiscard]] std::vector<std::string> get_file_contents(const std::string& file_path) noexcept
{
    std::ifstream f{file_path};
    std::vector<std::string> lines{};

    if (f.bad())
    {
        return lines;
    }

    std::string line{};
    while (std::getline(f, line))
    {
        lines.push_back(line);
    }

    return lines;
}

/**
 * Removes whitespace on either side of the given string
 * @param s: String to clean
 * @return
 */
[[nodiscard]] std::string str_strip(std::string s)
{
    auto lpos = s.find_first_not_of("\t\n ");
    auto rpos = s.find_last_not_of("\t\n ");
    return s.substr(lpos, rpos + 1);
}

[[nodiscard]] std::vector<std::string> str_split(std::string s, char delimeter)
{
    std::vector<std::string> sub_strs{};
    while (!s.empty())
    {
        auto pos = s.find(delimeter);
        if (pos != s.npos)
        {
            if (pos != 0) {
                sub_strs.push_back(str_strip(s.substr(0, pos)));
            }
            s = s.substr(pos + 1);
        }
        else
        {
            sub_strs.push_back(str_strip(s));
            s = "";
        }
    }
    return sub_strs;
}

