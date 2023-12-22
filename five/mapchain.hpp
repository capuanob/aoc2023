#ifndef ADVENTOFCODE2023_MAPCHAIN_HPP
#define ADVENTOFCODE2023_MAPCHAIN_HPP
#include <unordered_map>
#include <vector>

template <class T>
struct Range
{
    T begin;
    T length;

    [[nodiscard]] T end() const noexcept { return begin + length; }
    [[nodiscard]] T middle() const noexcept { return (begin + end()) / 2; }

    bool operator==(const Range &other) const
    {
        return begin == other.begin && length == other.length;
    }

    [[nodiscard]] Range<T> intersection(const Range<T> &other) const noexcept {
        Range<T> r{0UL, 0UL};

        if (begin <= other.begin && other.end() <= end())
        {
            r.begin = other.begin;
            r.length = std::min(end(), other.end()) - r.begin;
        }
        return r;
    }

    [[nodiscard]] Range<T> first_half() const noexcept
    {
        return { begin, length / 2};
    }

    [[nodiscard]] Range<T> second_half() const noexcept
    {
        return {middle() + 1, std::max<T>(0, end() - middle()) };
    }

    [[nodiscard]] bool empty() const noexcept { return length == 0UL; }
};


namespace std {
    template<typename T>
    struct hash<Range < T>> {
        std::size_t operator()(const Range <T>& r) const {
            size_t hash_value{};

            hash_value ^= hash<T>()(r.begin) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
            hash_value ^= hash<T>()(r.length) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
            return hash_value;
        }
    };
}
using Map = std::unordered_map<Range<std::uint64_t>, Range<std::uint64_t>>;

class MapChain
{
public:
    void parse(const std::string& line);

    [[nodiscard]] std::uint64_t find_minimum_input(Range<std::uint64_t> inp);
private:
    [[nodiscard]] std::uint64_t resolve(std::uint64_t input);
    Map curr_map{};
    std::vector<Map> chain_{};
};


#endif //ADVENTOFCODE2023_MAPCHAIN_HPP
