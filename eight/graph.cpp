#include <regex>

#include "graph.hpp"

const std::regex node_re{"(.{3}) = \\((.{3}), (.{3})\\)"};

std::shared_ptr<Node> Graph::left(const Node &node)
{
    return nodes_[node.left];
}

std::shared_ptr<Node> Graph::right(const Node &node)
{
   return nodes_[node.right];
}

void Graph::add_node(const std::string &name, Node &node) {
    nodes_[name] = std::make_shared<Node>(node);
}

bool Graph::is_end(const Node &node) noexcept {
    return node.name.ends_with('Z');
}

std::vector<std::shared_ptr<Node>> Graph::begin_nodes() const noexcept {
    std::vector<std::shared_ptr<Node>> begin_nodes{};
    for (const auto&[name, node] : nodes_)
    {
        if (name.ends_with('A'))
        {
            begin_nodes.push_back(node);
        }
    }
    return begin_nodes;
}

std::vector<std::shared_ptr<Node>> Graph::end_nodes() const noexcept {
    std::vector<std::shared_ptr<Node>> end_nodes{};
    for (const auto&[name, node] : nodes_)
    {
        if (name.ends_with('Z'))
        {
            end_nodes.push_back(node);
        }
    }
    return end_nodes;
}

std::pair<std::string, Node> Node::from_line(const std::string &line) noexcept {
    std::smatch sm{};
    if (!std::regex_search(line, sm, node_re))
    {
        exit(1);
    }
    return {sm[1].str(), {sm[1].str(), sm[2].str(), sm[3].str()}};
}
