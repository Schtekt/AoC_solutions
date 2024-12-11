#include "Day11.h"
#include <sstream>
#include <map>

AoCSolution_2024_11::AoCSolution_2024_11():
AoCDaySolution({"2024", "11"})
{}

std::vector<size_t> blink(const std::vector<size_t>& stones)
{
    std::vector<size_t> res;
    for(size_t stoneValue : stones)
    {
        std::string asString = std::to_string(stoneValue);
        if(stoneValue == 0)
        {
            res.emplace_back(1);
        }
        else if(asString.size() % 2 == 0)
        {
            res.emplace_back(std::stoi(asString.substr(0, asString.size() / 2)));
            res.emplace_back(std::stoi(asString.substr(asString.size() / 2)));
        }
        else
        {
            res.emplace_back(stoneValue * 2024);
        }
    }
    return res;
}

std::string AoCSolution_2024_11::PartOne()
{
    // Assume there is only one line of input
    std::stringstream ss{m_input.at(0)};

    std::vector<size_t> stones;

    size_t val;
    while(ss >> val)
    {
        stones.emplace_back(val);
    }

    for(int i = 0; i < 25; i++)
    {
        stones = blink(stones);
    }

    return std::to_string(stones.size());
}

size_t cachedBlink(std::map<std::pair<size_t, size_t>, size_t>& cache, size_t stoneValue, size_t nrOfTimesToBlink)
{
    if(nrOfTimesToBlink == 0)
    {
        return 1;
    }

    auto& ref = cache[{stoneValue, nrOfTimesToBlink}];

    if(ref != 0)
    {
        return ref;
    }

    std::string asString = std::to_string(stoneValue);

    if(stoneValue == 0)
    {
        ref = cachedBlink(cache, 1, nrOfTimesToBlink - 1);
    }
    else if(asString.size() % 2 == 0)
    {
        ref = cachedBlink(cache, std::stoi(asString.substr(0, asString.size() / 2)), nrOfTimesToBlink - 1);
        ref += cachedBlink(cache, std::stoi(asString.substr(asString.size() / 2)), nrOfTimesToBlink - 1);
    }
    else
    {
        ref = cachedBlink(cache, stoneValue * 2024, nrOfTimesToBlink - 1);
    }

    return ref;
}

std::string AoCSolution_2024_11::PartTwo()
{
    // Assume there is only one line of input
    std::stringstream ss{m_input.at(0)};

    std::vector<size_t> stones;

    size_t val;
    while(ss >> val)
    {
        stones.emplace_back(val);
    }

    std::map<std::pair<size_t, size_t>, size_t> cache;

    size_t sum = 0;
    for(size_t stoneValue : stones)
    {
        sum += cachedBlink(cache, stoneValue, 75);
    }

    return std::to_string(sum);
}