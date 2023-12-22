#include <iostream>

#include "mapchain.hpp"
#include "solutions.hpp"
#include "util.hpp"


void MapChain::parse(const std::string &line) {
    if (line.empty())
    {
        return;
    }

    if (line.find("map") != std::string::npos || line.find("end") != std::string::npos)
    {
        // This is the beginning of a new map
        if (!curr_map.empty()) {
            chain_.push_back(curr_map);
            curr_map.erase(curr_map.begin(), curr_map.end());
        }
    }
    else
    {
        // This should be data for the map
        auto line_vals = extract_digits<std::uint64_t>(line, false);
        if (line_vals.size() != 3)
        {
            std::cerr << "Received input with " << line_vals.size() << "ranges!\n";
            return;
        }

        std::uint64_t dst_range_start = line_vals[0];
        std::uint64_t src_range_start = line_vals[1];
        std::uint64_t range_len = line_vals[2];

        Range<std::uint64_t> src_range{src_range_start, range_len};
        curr_map[src_range] = Range<std::uint64_t>{dst_range_start, range_len};
    }
}

std::uint64_t MapChain::resolve(const std::uint64_t input) {
    std::uint64_t curr_src = input;

    for (auto& map : chain_)
    {
        auto new_src = curr_src;
        for (const auto &[src_range, dst_range]: map) {
            if (curr_src >= src_range.begin && curr_src < src_range.end()) {
                new_src = dst_range.begin + (curr_src - src_range.begin);
                break;
            }
        }
//        std::cout << "Resolving " << curr_src << " to " << new_src << "\n";
        curr_src = new_src;
    }

    return curr_src;
}

std::uint64_t MapChain::find_minimum_input(Range<std::uint64_t> inp) {
    std::uint64_t min = UINT64_MAX;


    for (auto i = inp.begin; i < inp.end(); ++i)
    {
        min = std::min(min, resolve(i));
    }

    return min;
}

void day_five()
{
    std::size_t lowest = UINT64_MAX;
    std::vector<Range<std::uint64_t>> input_ranges{};

    MapChain mc{};

    auto lines = get_file_contents("five/input/example");
    lines.emplace_back("end");

    // Pop off the starting inputs
    auto chain_inputs = extract_digits<std::uint64_t>(lines.front(), false);
    lines.erase(lines.begin());

    // Prepare input ranges
    for (int i = 0; i < chain_inputs.size() - 1; i += 2)
    {
        input_ranges.push_back(Range<std::uint64_t>{chain_inputs[i], chain_inputs[i + 1]});
    }

    for (const auto& line : lines)
    {
        mc.parse(line);
    }

    // Find the lowest number
    std::cout << "There are " << input_ranges.size() << " ranges to process\n";
    for (const auto& inp_range : input_ranges)
    {
        std::cout << "Processing range!\n";
        lowest = std::min(static_cast<std::size_t>(mc.find_minimum_input(inp_range)), lowest);
    }
    std::cout << "Lowest: " << lowest << "\n";
}