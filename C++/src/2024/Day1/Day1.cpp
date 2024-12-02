#include "Day1.h"

#include <sstream>
#include <algorithm>

AoCSolution_2024_1::AoCSolution_2024_1()
: AoCDaySolution({"2024", "1"})
{

}

std::string AoCSolution_2024_1::PartOne()
{
    std::vector<int> left;
    std::vector<int> right;

    for(const auto& line : m_input)
    {
        std::istringstream stream{line};

        auto& leftNum = left.emplace_back();
        auto& rightNum = right.emplace_back();

        stream >> leftNum;
        stream >> rightNum;
    }
    
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    if(left.size() != right.size())
    {
        return "Error, left and right are different sizes!";
    }

    int sum = 0;
    for(int i = 0; i < left.size(); i++)
    {
        sum += abs(left[i] - right[i]);
    }

    return std::to_string(sum);
}

std::string AoCSolution_2024_1::PartTwo()
{
    std::vector<int> left;
    std::vector<int> right;

    for(const auto& line : m_input)
    {
        std::istringstream stream{line};

        auto& leftNum = left.emplace_back();
        auto& rightNum = right.emplace_back();

        stream >> leftNum;
        stream >> rightNum;
    }
    
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    if(left.size() != right.size())
    {
        return "Error, left and right are different sizes!";
    }

    auto newEnd = std::unique(left.begin(), left.end());
    left.erase(newEnd, left.end());

    long long int sum = 0;
    for(auto num : left)
    {
        sum += num * std::count(right.begin(), right.end(), num);
    }

    return std::to_string(sum);
}