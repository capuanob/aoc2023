#include <iostream>
#include <regex>
#include <unordered_map>

#include "schematic.hpp"


const std::regex part_number_re{"([0-9]+)"};

bool PartNumber::is_valid() const noexcept {
    return std::any_of(neighbors_.begin(), neighbors_.end(), [](const auto& neighbor) {
        return neighbor->type() == NeighborType::Symbol || neighbor->type() == NeighborType::Gear;
    });
}

void PartNumber::add_neighbor(const std::shared_ptr<Neighbor>& neighbor) {
    neighbors_.emplace_back(neighbor);
}

void Schematic::parse() noexcept {

    for (int i = 0; i < lines_.size(); ++i)
    {
        const auto& line = lines_[i];
        std::string part_number;

        std::smatch sm;
        std::string::const_iterator search_start{line.begin()};
        int offset = 0;

        while (std::regex_search(search_start, line.cend(), sm, part_number_re))
        {
            auto pn = std::make_shared<PartNumber>(std::stoull(sm[1]));

            int curr_start = offset + sm.position();
            int left = std::max(0, curr_start - 1);
            int right = std::min<int>(curr_start + sm.length(), line.length() - 1);

            // Get left neighbor
            if (left != curr_start)
            {
                pn->add_neighbor(get_or_create_neighbor(left, i, line[left]));
            }

            // Get right neighbor
            if (right != curr_start)
            {
                pn->add_neighbor(get_or_create_neighbor(right, i, line[right]));
            }

            // Get above neighbors
            if (i - 1 >= 0)
            {
                const auto& above = lines_[i - 1].substr(left, right - left + 1);
                for (int j = left; j <= right; ++j)
                {
                    pn->add_neighbor(get_or_create_neighbor(j, i - 1, lines_[i - 1][j]));
                }
            }
            // Get below neighbors
            if (i + 1 < lines_.size())
            {
                const auto& below = lines_[i + 1].substr(left, right - left + 1);
                for (int j = left; j <= right; ++j)
                {
                    pn->add_neighbor(get_or_create_neighbor(j, i + 1, lines_[i + 1][j]));
                }
            }

            part_numbers_.push_back(pn);

            offset = curr_start + sm.length();
            search_start = sm.suffix().first;
        }
    }
}

std::vector<PartNumber*> Schematic::valid_parts() const noexcept {
    std::vector<PartNumber*> part_number_ptrs{};
    std::vector<PartNumber*> valid{};
    valid.reserve(part_numbers_.size());
    valid.reserve(valid.size());

    std::transform(part_numbers_.cbegin(), part_numbers_.cend(), std::back_inserter(part_number_ptrs), [](
            auto& pn_ptr) {
        return pn_ptr.get();
    });

    std::copy_if(part_number_ptrs.cbegin(), part_number_ptrs.cend(), std::back_inserter(valid), [](const auto* pn) {
       return pn->is_valid();
    });

    return valid;
}

std::shared_ptr<Neighbor> Schematic::get_or_create_neighbor(int x, int y, char c) {
    std::pair<int, int> key{x, y};

    if (auto iter = neighbor_store.find({x, y}); iter == neighbor_store.end())
    {

        auto type = Neighbor::get_type(c);
        auto neighbor = std::make_shared<Neighbor>(x, y, type);
        neighbor_store[key] = std::make_shared<Neighbor>(x, y, type);
    }

    return neighbor_store[key];
}

NeighborType Neighbor::get_type(char c) {
    NeighborType ty{};
    if (std::isdigit(c))
    {
        ty = NeighborType::Number;
    }
    else if (c == '.')
    {
        ty = NeighborType::Empty;
    }
    else if (c == '*')
    {
        ty = NeighborType::Gear;
    }
    else
    {
        ty = NeighborType::Symbol;
    }
    return ty;
}
