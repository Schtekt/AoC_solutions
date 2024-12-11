#include "Day10.h"
#include <sstream>

AoCSolution_2024_10::AoCSolution_2024_10():
AoCDaySolution({"2024", "10"})
{}

std::vector<std::vector<std::pair<size_t, size_t>>> examinePaths(std::pair<size_t, size_t> startPos, const std::vector<std::string>& map)
{
    std::vector<std::vector<std::pair<size_t, size_t>>> result;

    if(startPos.second == -1 || startPos.first == -1 || startPos.second >= map.size() || startPos.first >= map.at(startPos.second).size())
    {
        return result;
    }

    if(map.at(startPos.second).at(startPos.first) == '9')
    {
        auto& path = result.emplace_back();
        path.emplace_back(startPos);
        return result;
    }

    auto left = startPos;
    left.first -= 1;
    if(startPos.first > 0 && map.at(startPos.second).at(startPos.first) + 1 == map.at(left.second).at(left.first))
    {
        auto subResult = examinePaths(left, map);

        for(auto& path : subResult)
        {
            path.insert(path.begin(), startPos);
            result.emplace_back(path);
        }
    }

    // right
    auto right = startPos;
    right.first += 1;
    if(startPos.first < map.at(startPos.second).size() - 1 && map.at(startPos.second).at(startPos.first) + 1 == map.at(right.second).at(right.first))
    {
        auto subResult = examinePaths(right, map);
        
        for(auto& path : subResult)
        {
            path.insert(path.begin(), startPos);
            result.emplace_back(path);
        }
    }

    // up
    auto up = startPos;
    up.second -= 1;
    if(startPos.second > 0 && map.at(startPos.second).at(startPos.first) + 1 == map.at(up.second).at(up.first))
    {
        auto subResult = examinePaths(up, map);
        
        for(auto& path : subResult)
        {
            path.insert(path.begin(), startPos);
            result.emplace_back(path);
        }
    }

    // down
    auto down = startPos;
    down.second += 1;
    if(startPos.second < map.size() - 1 && map.at(startPos.second).at(startPos.first) + 1 == map.at(down.second).at(down.first))
    {
        auto subResult = examinePaths(down, map);
        
        for(auto& path : subResult)
        {
            path.insert(path.begin(), startPos);
            result.emplace_back(path);
        }
    }

    return result;
}

std::string AoCSolution_2024_10::PartOne()
{
    // Find out all start positions
    std::vector<std::pair<size_t, size_t>> startPositions;

    for(int y = 0; y < m_input.size(); y++)
    {
        const auto& line = m_input.at(y);
        for(int x = 0; x < line.size(); x++)
        {
            if(line.at(x) == '0')
            {
                startPositions.emplace_back(std::make_pair(x,y));
            }
        }
    }

    // Follow each trail start, split paths as needed (recursively) and see which ones end up on a nine
    size_t scoreSum = 0;
    for(const auto& pos : startPositions)
    {
        auto res = examinePaths(pos, m_input);

        std::vector<std::pair<size_t, size_t>> uniqueEnds;
        for(const auto& path : res)
        {
            if(std::find(uniqueEnds.begin(), uniqueEnds.end(), path.back()) == uniqueEnds.end())
            {
                uniqueEnds.emplace_back(path.back());
            }
        }
        scoreSum += uniqueEnds.size();
    }

    return std::to_string(scoreSum);
}

std::string AoCSolution_2024_10::PartTwo()
{
    // Find out all start positions
    std::vector<std::pair<size_t, size_t>> startPositions;

    for(int y = 0; y < m_input.size(); y++)
    {
        const auto& line = m_input.at(y);
        for(int x = 0; x < line.size(); x++)
        {
            if(line.at(x) == '0')
            {
                startPositions.emplace_back(std::make_pair(x,y));
            }
        }
    }

    // Follow each trail start, split paths as needed (recursively) and see which ones end up on a nine
    size_t scoreSum = 0;
    for(const auto& pos : startPositions)
    {
        auto res = examinePaths(pos, m_input);
        scoreSum += res.size();
    }

    return std::to_string(scoreSum);
}