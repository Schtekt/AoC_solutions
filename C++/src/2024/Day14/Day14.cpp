#include "Day14.h"
#include <iostream>
#include <regex>
#include <array>
#include <thread>

AoCSolution_2024_14::AoCSolution_2024_14():
AoCDaySolution({"2024", "14"})
{}

std::string AoCSolution_2024_14::PartOne()
{
    long long int givenWidth{101};
    long long int givenHeight{103};
    long long int timeToElapse{100};

    std::regex reg("p=(-?[0-9]+),(-?[0-9]*) v=(-?[0-9]+),(-?[0-9]+)");

    // position, velocity
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> robots;
    for(const auto& line : m_input)
    {
        std::pair<int, int> pos;
        std::pair<int, int> vel;
        std::smatch match;
        std::regex_search(line, match, reg);

        if(match.size() == 5)
        {
            pos.first = std::stoi(match[1]);
            pos.second = std::stoi(match[2]);

            vel.first = std::stoi(match[3]);
            vel.second = std::stoi(match[4]);
        }
        auto& robot = robots.emplace_back();
        robot.first = pos;
        robot.second = vel;
    }

    std::vector<std::pair<int, int>> finalPositions;
    for(const auto& robot : robots)
    {
        long long int x = robot.first.first + robot.second.first * timeToElapse;
        long long int y = robot.first.second + robot.second.second * timeToElapse;

        if(x >= 0)
        {
            x = x % givenWidth;
        }
        else
        {
            x = (givenWidth - (abs(x) % givenWidth)) % givenWidth;
        }

        if(y >= 0)
        {
            y = y % givenHeight;
        }
        else
        {
            y = (givenHeight - (abs(y) % givenHeight)) % givenHeight;
        }

        auto& finalPosition = finalPositions.emplace_back();
        finalPosition.first = static_cast<int>(x);
        finalPosition.second = static_cast<int>(y);
    }
    
    std::array<int, 4> quadrants{0};

    int halfWidth = static_cast<int>(givenWidth / 2);
    int halfHeight = static_cast<int>(givenHeight / 2);
    for(const auto& finalPosition : finalPositions)
    {
        if(finalPosition.first < halfWidth && finalPosition.second < halfHeight)
        {
            quadrants[0] += 1;
        }
        else if(finalPosition.first > halfWidth && finalPosition.second < halfHeight)
        {
            quadrants[1] += 1;
        }
        else if(finalPosition.first < halfWidth && finalPosition.second > halfHeight)
        {
            quadrants[2] += 1;
        }
        else if(finalPosition.first > halfWidth && finalPosition.second > halfHeight)
        {
            quadrants[3] += 1;
        }
    }

    size_t sum = 1;

    for(int quad : quadrants)
    {
        sum *= quad;
    }

    return std::to_string(sum);
}

std::vector<std::pair<int, int>> moveRobots(const std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& robots, long long int width, long long int height, long long int seconds)
{
    std::vector<std::pair<int, int>> finalPositions;
    for(const auto& robot : robots)
    {
        long long int x = robot.first.first + robot.second.first * seconds;
        long long int y = robot.first.second + robot.second.second * seconds;

        if(x >= 0)
        {
            x = x % width;
        }
        else
        {
            x = (width - (abs(x) % width)) % width;
        }

        if(y >= 0)
        {
            y = y % height;
        }
        else
        {
            y = (height - (abs(y) % height)) % height;
        }

        auto& finalPosition = finalPositions.emplace_back();
        finalPosition.first = static_cast<int>(x);
        finalPosition.second = static_cast<int>(y);
    }
    return finalPositions;
}

void display(const std::vector<std::pair<int, int>>& positions, long long int width, long long int height, long long int seconds)
{
    std::vector<std::string> visualize;
    for(int y = 0; y < height; y++)
    {
        auto& line = visualize.emplace_back();
        line.append(width, '.');
    }

    for(const auto& position : positions)
    {
        visualize.at(position.second).at(position.first) = 'x';
    }

    for(const auto& line : visualize)
    {
        std::cout << line << "\n";
    }

    std::cout << "Seconds: " << seconds;
}

std::string AoCSolution_2024_14::PartTwo()
{
    long long int givenWidth{101};
    long long int givenHeight{103};

    std::regex reg("p=(-?[0-9]+),(-?[0-9]*) v=(-?[0-9]+),(-?[0-9]+)");

    // position, velocity
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> robots;
    for(const auto& line : m_input)
    {
        std::pair<int, int> pos;
        std::pair<int, int> vel;
        std::smatch match;
        std::regex_search(line, match, reg);

        if(match.size() == 5)
        {
            pos.first = std::stoi(match[1]);
            pos.second = std::stoi(match[2]);

            vel.first = std::stoi(match[3]);
            vel.second = std::stoi(match[4]);
        }
        auto& robot = robots.emplace_back();
        robot.first = pos;
        robot.second = vel;
    }
    
    std::array<int, 4> quadrants{0};
    size_t safetyFactor = std::numeric_limits<size_t>::max();
    size_t highestNeighbourCount = 0;
    size_t highestNeighbourCountSecondsUsed = 0;
    for(int i = 0; i < 10000; i++)
    {
        auto finalPositions = moveRobots(robots, givenWidth, givenHeight, i);

        int halfWidth = static_cast<int>(givenWidth / 2);
        int halfHeight = static_cast<int>(givenHeight / 2);
        for(const auto& finalPosition : finalPositions)
        {
            if(finalPosition.first < halfWidth && finalPosition.second < halfHeight)
            {
                quadrants[0] += 1;
            }
            else if(finalPosition.first > halfWidth && finalPosition.second < halfHeight)
            {
                quadrants[1] += 1;
            }
            else if(finalPosition.first < halfWidth && finalPosition.second > halfHeight)
            {
                quadrants[2] += 1;
            }
            else if(finalPosition.first > halfWidth && finalPosition.second > halfHeight)
            {
                quadrants[3] += 1;
            }
        }

        size_t neighbourCount = 0;
        for(const auto& robot : finalPositions)
        {
            auto up = robot;
            up.second -= 1;

            auto down = robot;
            down.second += 1;

            auto left = robot;
            left.first -= 1;

            auto right = robot;
            right.first += 1;

            if(std::find(finalPositions.begin(), finalPositions.end(), up) != finalPositions.end())
            {
                neighbourCount += 1;
            }

            if(std::find(finalPositions.begin(), finalPositions.end(), down) != finalPositions.end())
            {
                neighbourCount += 1;
            }

            if(std::find(finalPositions.begin(), finalPositions.end(), left) != finalPositions.end())
            {
                neighbourCount += 1;
            }

            if(std::find(finalPositions.begin(), finalPositions.end(), right) != finalPositions.end())
            {
                neighbourCount += 1;
            }
        }
        
        if(highestNeighbourCount < neighbourCount)
        {
            highestNeighbourCount = neighbourCount;
            highestNeighbourCountSecondsUsed = i;
            // Helper visualizer
            //display(finalPositions, givenWidth, givenHeight, i);
        }
    }

    return std::to_string(highestNeighbourCountSecondsUsed);
}