#include <cmath>
#include <numeric>
#include <regex>
#include <iostream>

#include "solutions.hpp"
#include "util.hpp"

const std::regex card_re{"Card.*?[0-9]+:(.*?) \\| (.*?)$"};

struct Card
{
    std::string contents{};
    std::size_t copies{};
};


[[nodiscard]] std::size_t calculate_card_score(const std::string& card_contents) noexcept
{
    std::smatch sm{};
    if (!std::regex_search(card_contents, sm, card_re))
    {
        return 0UL;
    }

    const auto winning_numbers = extract_digits<int>(sm[1].str());
    const auto chosen_numbers = extract_digits<int>(sm[2].str());
    std::vector<int> intersection{};

    std::set_intersection(winning_numbers.cbegin(), winning_numbers.cend(),
                          chosen_numbers.cbegin(), chosen_numbers.cend(),
                          std::back_inserter(intersection));
    return intersection.size();
}

void day_four()
{
    std::size_t sum{};
    std::vector<Card> cards{};

    auto lines = get_file_contents("four/input/input");

    // Create all initial cards
    cards.reserve(lines.size());
    for (auto & line : lines)
    {
        cards.push_back(Card{line, 1UL});
    }

    for (std::size_t i = 0; i < cards.size(); ++i)
    {
        auto& card = cards[i];
        std::size_t cards_to_copy = calculate_card_score(card.contents);

        for (std::size_t off = 1; off <= cards_to_copy; ++off)
        {
            std::cout << "Card[" << i + 1 << "] creates " << card.copies << " copies of Card[" << i + 1 + off << "]\n";
            cards[i + off].copies += card.copies;
        }

        sum += card.copies;
    }
    std::cout << "Sum: " << sum << "\n";
}