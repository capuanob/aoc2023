#include <iostream>

#include "graph.hpp"
#include "solutions.hpp"
#include "util.hpp"

std::uint64_t gcd(std::uint64_t a, std::uint64_t b)
{
    return b == 0 ? a : gcd(b, a % b);
}

std::uint64_t lcm(std::uint64_t a, std::uint64_t b)
{
    return a * b / gcd(a, b);
}

void day_eight()
{
    std::uint64_t steps{};
    Graph g{};

    auto lines = get_file_contents("eight/input/input");
    auto directions = lines.front();
    lines.erase(lines.begin());
    lines.erase(lines.begin());

    for (const auto& line : lines)
    {
        auto[name, node] = Node::from_line(line);
        g.add_node(name, node);
    }

    auto curr_nodes = g.begin_nodes();
    std::vector<unsigned int> cycle_count{};
    cycle_count.reserve(curr_nodes.size());

    while (!curr_nodes.empty())
    {
        auto& curr_node = curr_nodes.back();
        curr_nodes.pop_back();
        steps = 0;
        bool in_cycle = false;

        while (!in_cycle && !Graph::is_end(*curr_node)) {
            if (Graph::is_end(*curr_node))
            {
                in_cycle = true;
            }

            if (directions[steps % directions.length()] == 'L') {
                curr_node = g.left(*curr_node);
            } else {
                curr_node = g.right(*curr_node);
            }
            steps += 1;
        }
        cycle_count.push_back(steps);
    }

    steps = 1;
    for (const auto& cc : cycle_count)
    {
        steps = lcm(steps, cc);
    }
    std::cout << "Steps: " << steps << "\n";
}