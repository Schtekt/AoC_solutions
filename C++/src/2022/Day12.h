#pragma once
#include "../Utility.h"
#include <iostream>

class AoCSolution_2022_12 : public AoCDaySolution
{
public:
	AoCSolution_2022_12(AoCUtilityTool& tool);
	std::string PartOne();

	std::string PartTwo();
private:
};

AoCSolution_2022_12::AoCSolution_2022_12(AoCUtilityTool& tool) : AoCDaySolution(tool, {"2022", "12"})
{
}

struct Pos
{
    unsigned int x;
    unsigned int y;

    bool operator==(const Pos& other)
    {
        return x == other.x && y == other.y;
    }
};

Pos findLetter(const std::vector<std::string>& map, char toFind)
{
    for(unsigned int y = 0; y < map.size(); y++)
    {
        for(unsigned int x = 0; x < map[y].size(); x++)
        {
            if(map[y][x] == toFind)
            {
                return Pos{x,y};
            }
        }
    }
    return Pos{(unsigned int)-1,(unsigned int)-1};
}

std::vector<Pos> findAllOfLetter(const std::vector<std::string>& map, char toFind)
{
    std::vector<Pos> found;
    for(unsigned int y = 0; y < map.size(); y++)
    {
        for(unsigned int x = 0; x < map[y].size(); x++)
        {
            if(map[y][x] == toFind)
            {
                found.push_back(Pos{x,y});
            }
        }
    }
    return found;
}

// Rationale: because of part 2, it is better to calculate the distance "end -> start" rather than "start -> end".
// When this is done, we do not need to recaulculate paths for every starting position...
void checkAndAddNewCoordinate(Pos next, Pos old, std::vector<std::vector<unsigned int>>& scoreMap, const std::vector<std::string>& heightMap, std::vector<Pos>& visited)
{
    if(heightMap[next.y][next.x] >= heightMap[old.y][old.x] - 1)
    {
        if(std::find(visited.begin(), visited.end(), next) == visited.end())
        {
            scoreMap[next.y][next.x] = scoreMap[old.y][old.x] + 1;
            visited.push_back(next);
        }
    }
}

std::vector<std::vector<unsigned int>> calcCosts(Pos end, const std::vector<std::string>& map)
{
    std::vector<std::vector<unsigned int>> toReturn;

    for(unsigned int y = 0; y < map.size(); y++)
    {
        toReturn.emplace_back();
        for(unsigned int x = 0; x < map[y].size(); x++)
        {
            toReturn[y].push_back(-1);
        }
    }

    std::vector<Pos> positions;
    positions.push_back(end);

    toReturn[end.y][end.x] = 0;
    auto currPos = positions.begin();
    size_t counter = 0;

    while(currPos != positions.end())
    {
        Pos current = *currPos;
        if(current.x > 0)
        {
            Pos temp{current.x - 1, current.y};
            checkAndAddNewCoordinate(temp, current, toReturn, map, positions);
        }

        if(current.y > 0)
        {
            Pos temp{current.x, current.y - 1};
            checkAndAddNewCoordinate(temp, current, toReturn, map, positions);
        }

        if(current.x < map[current.y].size() - 1)
        {
            Pos temp{current.x + 1, current.y};
            checkAndAddNewCoordinate(temp, current, toReturn, map, positions);
        }

        if(current.y < map.size() - 1)
        {
            Pos temp{current.x, current.y + 1};
            checkAndAddNewCoordinate(temp, current, toReturn, map, positions);
        }
        currPos = positions.begin() + ++counter;
    }

    return toReturn;
}

std::string AoCSolution_2022_12::PartOne()
{
    std::vector<std::string> map = m_input;

    Pos start = findLetter(map, 'S');
    Pos end = findLetter(map, 'E');
    map[end.y][end.x] = 'z';
    map[start.y][start.x] = 'a';

    auto scores = calcCosts(end, map);
    return std::to_string(scores[start.y][start.x]);
}

std::string AoCSolution_2022_12::PartTwo()
{
    std::vector<std::string> map = m_input;
    std::vector<unsigned int> costs;
    Pos tmp = findLetter(map, 'S');
    map[tmp.y][tmp.x] = 'a';
    auto startPositions = findAllOfLetter(map, 'a');
    Pos end = findLetter(map, 'E');

    auto scores = calcCosts(end, map);
    unsigned int lowest = -1;
    for(auto start : startPositions)
    {
        if(lowest > scores[start.y][start.x])
            lowest = scores[start.y][start.x];
    }
    return std::to_string(lowest);
}