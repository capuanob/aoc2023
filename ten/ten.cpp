#include <iostream>
#include <unordered_map>
#include <stack>
#include "solutions.hpp"
#include "util.hpp"

enum class Tile
{
    Ground = 0,
    Start,
    Vertical,
    Horizontal,
    NtoE,
    NtoW,
    StoW,
    StoE,
};

const std::unordered_map<char, Tile> char_to_tile{
        {'.', Tile::Ground},
        {'S', Tile::Start},
        {'|', Tile::Vertical},
        {'-', Tile::Horizontal},
        {'L', Tile::NtoE},
        {'J', Tile::NtoW},
        {'7', Tile::StoW},
        {'F', Tile::StoE},
};

std::pair<std::size_t, std::vector<Tile>> get_tiles(const std::string &line)
{
    std::vector<Tile> tiles{};
    tiles.reserve(line.size());
    std::size_t start_pos = tiles.size();

    for (std::size_t i = 0; i < line.size(); ++i)
    {
        auto tile = char_to_tile.at(line[i]);
        if (tile == Tile::Start)
        {
            start_pos = i;
        }
        tiles.push_back(tile);
    }

    return {start_pos, tiles};
}

void dfs_iterative(std::vector<std::vector<Tile>> g, std::pair<std::size_t, std::size_t> start)
{
    std::stack<std::pair<std::size_t, std::size_t>> stack{};
    stack.push(start);

    while (!stack.empty())
    {
        auto& peek = stack.top();

        if (peek.)
    }
}

void day_ten()
{
    std::int64_t sum{};
    auto lines = get_file_contents("ten/input/example");

    std::vector<std::vector<Tile>> grid{};
    std::pair<std::size_t, std::size_t> start_pos;

    for (std::size_t i = 0; i < lines.size(); ++i)
    {
        auto[start_idx, tiles] = get_tiles(lines[i]);
        if (start_idx != tiles.size())
        {
            // This line contains the starting position, save it off
            start_pos.first = i;
            start_pos.second = start_idx;
        }

        grid.push_back(tiles);
    }

    dfs_iterative(grid, start_pos);

    std::cout << "Sum: " << sum << "\n";
}