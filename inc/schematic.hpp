#ifndef ADVENTOFCODE2023_SCHEMATIC_HPP
#define ADVENTOFCODE2023_SCHEMATIC_HPP
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};


enum class NeighborType
{
    Empty,
    Number,
    Symbol,
    Gear
};

class Neighbor
{
public:
    Neighbor(int x, int y, NeighborType type) : x_{x}, y_{y}, type_{type} {}
    static NeighborType get_type(char c);

    [[nodiscard]] NeighborType type() const noexcept { return type_; }
private:
    int x_{};
    int y_{};
    NeighborType type_{};
};

class PartNumber
{
public:
    explicit PartNumber(std::uint64_t value): value_{value} {}

    [[nodiscard]] bool is_valid() const noexcept;

    void add_neighbor(const std::shared_ptr<Neighbor>& neighbor);
    const std::vector<std::shared_ptr<Neighbor>>& neighbors() const noexcept { return neighbors_; }

    [[nodiscard]] std::uint64_t value() const noexcept { return value_; }
private:
    std::uint64_t value_{};
    std::vector<std::shared_ptr<Neighbor>> neighbors_{};
};

class Gear: public Neighbor
{
    Gear(int x, int y) : Neighbor(x, y, NeighborType::Gear), parts{} {}
private:
    std::vector<std::shared_ptr<PartNumber>> parts{};
};

class Schematic
{
public:
    explicit Schematic(std::vector<std::string> lines) : lines_{std::move(lines)} {};

    void parse() noexcept;
    [[nodiscard]] std::vector<PartNumber *> valid_parts() const noexcept;
    [[nodiscard]] std::shared_ptr<Neighbor> get_or_create_neighbor(int x, int y, char c);

private:
    std::vector<std::string> lines_{};
    std::vector<std::shared_ptr<PartNumber>> part_numbers_{};
    std::unordered_map<std::pair<int, int>, std::shared_ptr<Neighbor>, hash_pair> neighbor_store{};
};
#endif //ADVENTOFCODE2023_SCHEMATIC_HPP
