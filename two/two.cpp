#include <iostream>
#include <numeric>
#include <regex>

#include "solutions.hpp"
#include "util.hpp"

/**
 * Contains the information of how many of each color of cube were pulled for a round of a game
 */
struct Round
{
    int red;
    int green;
    int blue;
};

struct Game
{
    int id;
    std::vector<Round> rounds;
};

std::regex game_re{"Game ([0-9]+): (.*)"};
std::regex round_re{"([0-9]+) (red|green|blue)"};

/**
 * Parses a semicolon separated list of games into its constituent Round objects
 * @param game: The string representing a game
 * @return The game object that is parsed out
 */
[[nodiscard]] Game parse_game(const std::string& game)
{
    Game g{};
    std::smatch sm;

    // Extract game ID and rounds
    if (!std::regex_search(game, sm, game_re))
    {
        std::cerr << "Unable to parse Game ID for " << game << "!\n";
        return g;
    }
    g.id = std::stoi(sm[1]);

    // Parse rounds
    auto round_strs = str_split(sm[2], ';');
    for (const auto& round_str : round_strs)
    {
        Round r{};
        std::string::const_iterator search_start{round_str.begin()};
        while(std::regex_search(search_start, round_str.cend(), sm, round_re))
        {
            auto count = std::stoi(sm[1]);
            auto color = sm[2];

            if (color == "red")
            {
                r.red = count;
            }
            else if (color == "blue")
            {
                r.blue = count;
            }
            else
            {
                r.green = count;
            }
            search_start = sm.suffix().first;
        }
        g.rounds.push_back(r);
    }

    return g;
}

[[nodiscard]] std::size_t get_min_color(const Game& g, auto round_selector)
{
    std::vector<int> color_count{};
    std::transform(g.rounds.cbegin(), g.rounds.cend(), std::back_inserter(color_count), round_selector);
    return *std::max_element(color_count.begin(), color_count.end(), [](int a, int b){ return a < b; });
}

[[nodiscard]] std::size_t calculate_game_power(const std::string& game)
{
    auto g = parse_game(game);

    std::vector<int> color_counts{};
    auto min_red = get_min_color(g, [](const Round& r) { return r.red; });
    auto min_green = get_min_color(g, [](const Round& r) { return r.green; });
    auto min_blue = get_min_color(g, [](const Round& r) { return r.blue; });

    return min_red * min_green * min_blue;
};

void day_two()
{
    auto games = get_file_contents("inputs/2/input.txt");
    std::size_t sum{};
    for (const auto& game: games)
    {
        sum += calculate_game_power(game);
    }
    std::cout << "Sum: " << sum << "\n";
}