#pragma once
#include "../Utility.h"
#include <iostream>
#include <sstream>

class AoCSolution_2022_14 : public AoCDaySolution
{
public:
    AoCSolution_2022_14(AoCUtilityTool &tool);
    std::string PartOne();

    std::string PartTwo();

private:
};

AoCSolution_2022_14::AoCSolution_2022_14(AoCUtilityTool &tool) : AoCDaySolution(tool, {"2022", "14"})
{
}

struct Line
{
    size_t start_x;
    size_t end_x;

    size_t start_y;
    size_t end_y;
};

std::vector<Line> GetRockLines(const std::string &input)
{
    std::vector<Line> rcklines;
    std::stringstream ss(input);

    size_t start_x;
    size_t start_y;
    size_t end_x = -1;
    size_t end_y = -1;
    char trash;

    ss >> start_x;
    ss >> trash;
    ss >> start_y;
    ss >> trash;
    ss >> trash;

    while (ss >> end_x)
    {
        ss >> trash;
        ss >> end_y;
        ss >> trash;
        ss >> trash;
        Line tmp{start_x, end_x, start_y, end_y};

        if (tmp.start_x > tmp.end_x)
        {
            size_t tmpStart = start_x;
            tmp.start_x = tmp.end_x;
            tmp.end_x = tmpStart;
        }

        if (tmp.start_y > tmp.end_y)
        {
            size_t tmpStart = start_y;
            tmp.start_y = tmp.end_y;
            tmp.end_y = tmpStart;
        }
        rcklines.push_back(tmp);

        start_x = end_x;
        start_y = end_y;
    }

    return rcklines;
}

void DrawLines(std::vector<std::string> &map, const std::vector<Line> &lines, size_t min_x)
{
    for (auto rockLine : lines)
    {
        for (unsigned int y = rockLine.start_y; y <= rockLine.end_y; y++)
        {
            map[y][rockLine.start_x - min_x] = '#';
        }

        for (unsigned int x = rockLine.start_x - min_x; x <= rockLine.end_x - min_x; x++)
        {
            map[rockLine.start_y][x] = '#';
        }
    }
}


std::vector<std::string> caveMap(const std::vector<std::string> &input, size_t min_x, size_t max_x, size_t max_y)
{
    std::vector<std::string> map;
    for (unsigned int y = 0; y <= max_y; y++)
    {
        map.emplace_back();
        for (unsigned int x = 0; x <= max_x - min_x; x++)
        {
            map[y] += ".";
        }
    }

    for (auto line : input)
    {
        DrawLines(map, GetRockLines(line), min_x);
    }
    return map;
}

bool DropSand(std::vector<std::string> &map, size_t from_x, size_t from_y)
{
    bool moved = false;
    bool movedToAbyss = false;

    size_t sandPos_x = from_x;
    size_t sandPos_y = from_y;

    do
    {
        moved = false;
        if (sandPos_y + 1 < map.size())
        {
            if (map[sandPos_y + 1][sandPos_x] == '.')
            {
                sandPos_y += 1;
                moved = true;
            }
            else
            {

                if (sandPos_x > 0)
                {
                    if (map[sandPos_y + 1][sandPos_x - 1] == '.')
                    {
                        sandPos_y += 1;
                        sandPos_x -= 1;
                        moved = true;
                    }
                }
                else
                {
                    movedToAbyss = true;
                }

                if (sandPos_x < map[sandPos_y].size() && !moved)
                {
                    if (map[sandPos_y + 1][sandPos_x + 1] == '.')
                    {
                        sandPos_y += 1;
                        sandPos_x += 1;
                        moved = true;
                    }
                }
                else if (!moved)
                {
                    movedToAbyss = true;
                }
            }
        }
        else
        {
            movedToAbyss = true;
        }
    } while (moved);

    if (!movedToAbyss)
    {
        map[sandPos_y][sandPos_x] = 'o';
        return true;
    }
    else
    {
        return false;
    }
}

bool DropSandUntilBlocked(std::vector<std::string> &map, size_t& from_x, size_t from_y)
{
    bool moved = false;
    bool blocked = false;

    size_t sandPos_x = from_x;
    size_t sandPos_y = from_y;

    if (map[sandPos_y][sandPos_x] == 'o')
    {
        return false;
    }

    do
    {
        moved = false;
        if (sandPos_y + 1 < map.size())
        {
            if (map[sandPos_y + 1][sandPos_x] == '.')
            {
                sandPos_y += 1;
                moved = true;
            }
            else
            {
                if (sandPos_x == 0)
                {
                    for (unsigned int y = 0; y < map.size() - 1; y++)
                    {
                        map[y] = '.' + map[y];
                    }
                    map[map.size() - 1] = '#' + map[map.size() - 1];
                    sandPos_x += 1;
                    from_x += 1;
                }
                else if (sandPos_x == map[sandPos_y].size() - 1)
                {
                    for (unsigned int y = 0; y < map.size() - 1; y++)
                    {
                        map[y] += '.';
                    }
                    map[map.size() - 1] += '#';
                }

                if (map[sandPos_y + 1][sandPos_x - 1] == '.')
                {
                    sandPos_y += 1;
                    sandPos_x -= 1;
                    moved = true;
                }
                else if (map[sandPos_y + 1][sandPos_x + 1] == '.')
                {
                    sandPos_y += 1;
                    sandPos_x += 1;
                    moved = true;
                }
            }
        }
    } while (moved);
    map[sandPos_y][sandPos_x] = 'o';
    return true;
}

std::string AoCSolution_2022_14::PartOne()
{
    // find out min/max x and min/max y.

    size_t min_x = -1;
    size_t min_y = -1;

    size_t max_x = 0;
    size_t max_y = 0;

    for (auto line : m_input)
    {
        std::stringstream ss(line);

        size_t tempX;
        size_t tempY;
        char trash;
        while (ss >> tempX)
        {
            ss >> trash;
            ss >> tempY;
            ss >> trash;
            ss >> trash;

            if (tempX < min_x)
            {
                min_x = tempX;
            }
            if (tempY < min_y)
            {
                min_y = tempY;
            }

            if (tempX > max_x)
            {
                max_x = tempX;
            }

            if (tempY > max_y)
            {
                max_y = tempY;
            }
        }
    }

    std::vector<std::string> map = caveMap(m_input, min_x, max_x, max_y);
    size_t count = 0;
    size_t start_x = 500 - min_x;
    while (DropSand(map, start_x, 0))
    {
        count++;
    }

    return std::to_string(count);
}

std::string AoCSolution_2022_14::PartTwo()
{
    // find out min/max x and max y.

    size_t min_x = -1;
    // min y always 0.

    size_t max_x = 0;
    size_t max_y = 0;

    for (auto line : m_input)
    {
        std::stringstream ss(line);

        size_t tempX;
        size_t tempY;
        char trash;
        while (ss >> tempX)
        {
            ss >> trash;
            ss >> tempY;
            ss >> trash;
            ss >> trash;

            if (tempX < min_x)
            {
                min_x = tempX;
            }

            if (tempX > max_x)
            {
                max_x = tempX;
            }

            if (tempY > max_y)
            {
                max_y = tempY;
            }
        }
    }

    std::vector<std::string> map = caveMap(m_input, min_x, max_x, max_y);
    std::string boost;
    std::string floor;

    for (unsigned int i = 0; i < map[0].size(); i++)
    {
        boost += '.';
        floor += '#';
    }

    map.push_back(boost);
    map.push_back(floor);

    size_t count = 0;
    size_t start_x = 500 - min_x;
    while (DropSandUntilBlocked(map, start_x, 0))
    {
        count++;
    }

    return std::to_string(count);
}