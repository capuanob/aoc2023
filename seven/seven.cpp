#include <iostream>
#include <array>
#include <unordered_map>

#include "solutions.hpp"
#include "util.hpp"

enum class CardFace
{
    Joker = 0,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Queen,
    King,
    Ace
};

enum class HandType
{
    HighCard = 0,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    Fullhouse,
    FourOfAKind,
    FiveOfAKind
};
const std::unordered_map<char, CardFace> char_to_face
{
    {'2', CardFace::Two},
    {'3', CardFace::Three},
    {'4', CardFace::Four},
    {'5', CardFace::Five},
    {'6', CardFace::Six},
    {'7', CardFace::Seven},
    {'8', CardFace::Eight},
    {'9', CardFace::Nine},
    {'T', CardFace::Ten},
    {'J', CardFace::Joker},
    {'Q', CardFace::Queen},
    {'K', CardFace::King},
    {'A', CardFace::Ace}
};

struct Hand
{
public:
    std::array<CardFace, 5> cards{};
    HandType type;
    std::uint64_t bid;
};

Hand parse_line(const std::string& line)
{
    auto components = str_split(line, ' ');
    if (components.size() != 2)
    {
        exit(1);
    }
    auto& card_chars = components[0];
    auto bid = static_cast<std::uint64_t>(std::stoull(components[1]));

    std::array<CardFace, 5> cards{};

    std::unordered_map<char, std::uint64_t> face_count{};

    for (std::size_t i = 0; i < card_chars.size(); ++i)
    {
        char c = card_chars[i];
        if (auto iter = char_to_face.find(c); iter != char_to_face.end())
        {
            if (!face_count.contains(c))
            {
                face_count[c] = 0;
            }
            cards[i] = iter->second;
            face_count[c] += 1;
        }
        else
        {
            exit(1);
        }
    }

    // Determine the type of the hand
    std::vector<std::uint64_t> counts{};
    counts.reserve(face_count.size());
    std::uint64_t joker_count{};
    for (const auto&[key, value] : face_count)
    {
        if (key == 'J')
        {
            joker_count = value;
        }
        else if (value > 0) {
            counts.push_back(value);
        }
    }
    std::sort(counts.begin(), counts.end(), [](const auto& a, const auto& b) { return a > b; });
    counts[0] += joker_count;
    HandType ty;
    if (counts.size() == 5)
    {
        ty = HandType::HighCard;
    }
    else if (counts.size() == 4)
    {
        ty = HandType::OnePair;
    }
    else if (counts.size() == 3)
    {
        if (counts[0] == 2 && counts[1] == 2 && counts[2] == 1)
        {
            ty = HandType::TwoPair;
        }
        else if (counts[0] == 3 && counts[1] == 1 && counts[2] == 1)
        {
            ty = HandType::ThreeOfAKind;
        }
        else
        {
            exit(1);
        }
    }
    else if (counts.size() == 2)
    {
        if (counts[0] == 3 && counts[1] == 2) {
            ty = HandType::Fullhouse;
        }
        else if (counts[0] == 4 && counts[1] == 1)
        {
            ty = HandType::FourOfAKind;
        }
        else
        {
            exit(1);
        }
    }
    else
    {
        ty = HandType::FiveOfAKind;
    }
    return {cards, ty, bid};
}

void day_seven()
{
    std::uint64_t winnings{};
    auto lines = get_file_contents("seven/input/input");

    std::vector<Hand> hands;
    hands.reserve(lines.size());
    for (const auto& line : lines)
    {
        hands.push_back(parse_line(line));
    }

    std::sort(hands.begin(), hands.end(), [](const auto& a, const auto& b) {
        if (a.type != b.type)
        {
            return a.type <= b.type;
        }
        else
        {
            for (std::size_t i = 0; i < a.cards.size(); ++i)
            {
                if (a.cards[i] != b.cards[i])
                {
                    return a.cards[i] <= b.cards[i];
                }
            }
            return false;
        }
    });
    for (std::size_t i = 0; i < hands.size(); ++i)
    {
        winnings += (hands[i].bid * (i + 1));
    }
    std::cout << "Winnings: " << winnings << "\n";
}