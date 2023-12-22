#include <iostream>

#include "solutions.hpp"
#include "util.hpp"

std::vector<std::int64_t> resolve_next_value(std::vector<std::int64_t> &values)
{

    // Build out the next line
    std::vector<std::int64_t> next_line{};
    next_line.resize(values.size() - 1);

    for (std::size_t i = 0; i < next_line.size(); ++i)
    {
        next_line[i] = values[i + 1] - values[i];
    }

    if (std::all_of(next_line.begin(), next_line.end(), [](const auto& v) {
        return v == 0;
    }))
    {
        values.insert(values.begin(), next_line.front() + values.front());
        return values;
    }
    else
    {
        auto next = resolve_next_value(next_line);
        values.insert(values.begin(), values.front() - next.front());
        return values;
    }

}

std::int64_t predict_next_value(std::vector<std::int64_t> &values)
{
    return resolve_next_value(values).front();
}

void day_nine()
{
    std::int64_t sum{};
    auto lines = get_file_contents("nine/input/input");

    for (const auto& line : lines)
    {
        auto digits = extract_digits<std::int64_t>(line, false);
        sum += predict_next_value(digits);
    }
    std::cout << "Sum: " << sum << "\n";
}