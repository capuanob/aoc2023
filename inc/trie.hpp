#ifndef ADVENTOFCODE2023_TRIE_H
#define ADVENTOFCODE2023_TRIE_H

#include <cstddef>
#include <concepts>
#include <ranges>
#include <unordered_map>

enum class SearchResult
{
    NOT_PRESENT = 0,
    NON_TERMINAL = 1,
    TERMINAL = 2
};

template<typename ElemT, typename CollT>
concept RangeOf = requires(CollT coll)
{
    std::ranges::begin(coll);
    std::ranges::end(coll);
    std::same_as<decltype(std::ranges::begin(coll)), ElemT*>;
    std::same_as<decltype(std::ranges::end(coll)), ElemT*>;
};

template <typename T>
struct TrieNode
{
    TrieNode() = default;
    TrieNode(T value, bool is_terminal)
    {
        this->value = value;
        this->is_terminal = is_terminal;
    }

    T value;
    bool is_terminal{};
    std::unordered_map<T, std::unique_ptr<TrieNode<T>>> children{};
};

template <typename T>
class Trie
{
public:
    template <typename CollT> requires RangeOf<T, CollT>
    Trie(std::vector<CollT> colls)
    {
        head = std::make_unique<TrieNode<T>>(T{}, false);
        for (const auto coll : colls)
        {
            insert(coll);
        }
    }

    template <typename CollT> requires RangeOf<T, CollT>
    void insert(const CollT& inp)
    {
        auto curr_node = head.get();

        for (const T& e : inp)
        {
            if (curr_node->children.contains(e))
            {
                curr_node = curr_node->children[e].get();
            }
            else
            {
                // Add the child
                curr_node->children[e] = std::make_unique<TrieNode<T>>(e, false);
                curr_node = curr_node->children[e].get();
            }
        }

        curr_node->is_terminal = true;
    }

    template <typename CollT> requires RangeOf<T, CollT>
    [[nodiscard]] SearchResult search(const CollT& coll) const noexcept
    {
        auto curr_node = head.get();

        for (const T& e : coll)
        {
            if (!curr_node->children.contains(e))
            {
                return SearchResult::NOT_PRESENT;
            }
            curr_node = curr_node->children[e].get();
        }
        return (curr_node->is_terminal) ? SearchResult::TERMINAL : SearchResult::NON_TERMINAL;
    }

private:
    std::unique_ptr<TrieNode<T>> head{};
};
#endif //ADVENTOFCODE2023_TRIE_H
