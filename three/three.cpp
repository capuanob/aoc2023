#include <iostream>
#include <numeric>

#include "schematic.hpp"
#include "solutions.hpp"
#include "util.hpp"

void day_three()
{
    std::size_t ratio_sum{};
    auto lines = get_file_contents("three/input/input");
    Schematic s{lines};
    s.parse();

    std::unordered_map<Neighbor*, std::vector<PartNumber*>> gears{};
    for (const auto& part_value : s.valid_parts())
    {
        for (const auto& neighbor : part_value->neighbors())
        {
            if (neighbor->type() == NeighborType::Gear) {
                gears[neighbor.get()].push_back(part_value);
            }
        }
    }

    for (const auto&[gear, parts]: gears)
    {
        if (parts.size() == 2)
        {
            // This is a true gear
            ratio_sum += parts[0]->value() * parts[1]->value();
        }
    }
    std::cout << "Sum: " << ratio_sum << "\n";

}