#ifndef ADVENTOFCODE2023_GRAPH_HPP
#define ADVENTOFCODE2023_GRAPH_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

struct Node
{
    std::string name;
    std::string left;
    std::string right;

    [[nodiscard]] static std::pair<std::string, Node> from_line(const std::string& line) noexcept;

    bool operator==(const Node& other) const
    {
        return name == other.name;
    }
};

class Graph
{
public:
    [[nodiscard]] std::vector<std::shared_ptr<Node>> begin_nodes() const noexcept;
    [[nodiscard]] std::vector<std::shared_ptr<Node>> end_nodes() const noexcept;

    [[nodiscard]] static bool is_end(const Node& node) noexcept;

    [[nodiscard]] std::shared_ptr<Node> left(const Node& node);
    [[nodiscard]] std::shared_ptr<Node> right(const Node& node);
    void add_node(const std::string& name, Node& node);

private:
    std::unordered_map<std::string, std::shared_ptr<Node>> nodes_;
};


#endif //ADVENTOFCODE2023_GRAPH_HPP
