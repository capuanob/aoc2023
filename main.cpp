#include <iostream>

#include "solutions.hpp"
#include "util.hpp"

int main(const int argc, const char *argv[]) {
    if (2 != argc || !is_integral(std::string_view(argv[1])))
    {
        std::cerr << "Must specify which day's solution you would like!\n";
        exit(1);
    }

    int day = std::stoi(std::string{argv[1]});

    switch (day)
    {
        case 1:
            day_one();
            break;
        case 2:
            day_two();
            break;
        case 3:
            day_three();
            break;
        case 4:
            day_four();
            break;
        case 5:
            day_five();
            break;
        case 7:
            day_seven();
            break;
        case 8:
            day_eight();
            break;
        case 9:
            day_nine();
            break;
        case 10:
            day_ten();
            break;
        default:
            std::cerr << "No solution defined for day " << day << "!\n";
    }
    return 0;
}
