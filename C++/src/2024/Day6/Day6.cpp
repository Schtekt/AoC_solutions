#include "Day6.h"
#include <cstdlib>

AoCSolution_2024_6::AoCSolution_2024_6():
AoCDaySolution({"2024", "6"})
{}

enum Direction
{
    up = 0,
    right,
    down,
    left
};

std::string AoCSolution_2024_6::PartOne()
{
    // x, y, left top is 0,0
    std::pair<size_t, size_t> guardPosition;
    Direction guardDirection{Direction::up};

    // Find initial Guard position
    size_t yCount = 0;
    for(const auto& line : m_input)
    {
        auto guardIt = std::find(line.begin(), line.end(), '^');
        if(guardIt != line.end())
        {
            guardPosition.first = guardIt - line.begin();
            guardPosition.second = yCount;
            break;
        }
        yCount++;
    }

    bool guardOnGrid = true;
    
    std::vector<std::pair<size_t, size_t>> visitedLocations;
    visitedLocations.emplace_back(guardPosition);

    std::pair guardMoveDirection = std::make_pair<long long int, long long int>(guardDirection % 2 == 1 ? (guardDirection == 3 ? -1 : 1) : 0, guardDirection % 2 == 0 ? (guardDirection == 0 ? -1 : 1) : 0);
    std::pair<size_t, size_t> movement = guardPosition;
    while(guardOnGrid)
    {
        movement.first += guardMoveDirection.first;
        movement.second += guardMoveDirection.second;

        if(movement.second < 0 || movement.first < 0 || movement.second >= m_input.size() || movement.first >= m_input.at(movement.second).size())
        {
            movement.first -= guardMoveDirection.first;
            movement.second -= guardMoveDirection.second;

            auto xDiff = ((long long int)guardPosition.first) - ((long long int)movement.first);
            auto yDiff = ((long long int)guardPosition.second) - ((long long int)movement.second);

            guardOnGrid = false;
            break;
        }

        // Guard meets a barrel, move him to it and rotate 90 degrees clockwise
        if(m_input.at(movement.second).at(movement.first) == '#')
        {
            movement.first -= guardMoveDirection.first;
            movement.second -= guardMoveDirection.second;

            auto xDiff = ((long long int)guardPosition.first) - ((long long int)movement.first);
            auto yDiff = ((long long int)guardPosition.second) - ((long long int)movement.second);

            guardPosition = movement;

            // Rotate
            guardDirection = static_cast<Direction>((guardDirection + 1) % 4);
            guardMoveDirection.first = guardDirection % 2 == 1 ? (guardDirection == 3 ? -1 : 1) : 0;
            guardMoveDirection.second = guardDirection % 2 == 0 ? (guardDirection == 0 ? -1 : 1) : 0;
        }

        if(std::find(visitedLocations.begin(), visitedLocations.end(), movement) == visitedLocations.end())
        {
            visitedLocations.emplace_back(movement);
        }
    }

    return std::to_string(visitedLocations.size());
}

bool guardIsStuck(const std::vector<std::string>& map, const std::pair<size_t, size_t>& guardStartPosition, const std::pair<size_t, size_t>& barrelLocation)
{
    Direction guardDirection{Direction::up};
    bool guardOnGrid = true;
    bool guardIsStuck = false;

    std::pair guardMoveDirection = std::make_pair<long long int, long long int>(guardDirection % 2 == 1 ? (guardDirection == 3 ? -1 : 1) : 0, guardDirection % 2 == 0 ? (guardDirection == 0 ? -1 : 1) : 0);
    std::pair<size_t, size_t> guardPosition = guardStartPosition;
    std::pair<size_t, size_t> movement = guardStartPosition;

    std::vector<std::pair<size_t, size_t>> visitedLocations;
    visitedLocations.emplace_back(guardStartPosition);
    std::vector<Direction> visitedLocationsDirections;
    visitedLocationsDirections.emplace_back(guardDirection);

    while(guardOnGrid && !guardIsStuck)
    {
        movement.first += guardMoveDirection.first;
        movement.second += guardMoveDirection.second;

        if(movement.second < 0 || movement.first < 0 || movement.second >= map.size() || movement.first >= map.at(movement.second).size())
        {
            movement.first -= guardMoveDirection.first;
            movement.second -= guardMoveDirection.second;

            auto xDiff = ((long long int)guardPosition.first) - ((long long int)movement.first);
            auto yDiff = ((long long int)guardPosition.second) - ((long long int)movement.second);

            guardOnGrid = false;
            break;
        }

        // Guard meets a barrel, move him to it and rotate 90 degrees clockwise
        if(map.at(movement.second).at(movement.first) == '#' || movement == barrelLocation)
        {
            movement.first -= guardMoveDirection.first;
            movement.second -= guardMoveDirection.second;

            auto xDiff = ((long long int)guardPosition.first) - ((long long int)movement.first);
            auto yDiff = ((long long int)guardPosition.second) - ((long long int)movement.second);

            guardPosition = movement;

            // Rotate
            guardDirection = static_cast<Direction>((guardDirection + 1) % 4);
            guardMoveDirection.first = guardDirection % 2 == 1 ? (guardDirection == 3 ? -1 : 1) : 0;
            guardMoveDirection.second = guardDirection % 2 == 0 ? (guardDirection == 0 ? -1 : 1) : 0;
        }

        auto visitedLocation = std::find(visitedLocations.begin(), visitedLocations.end(), movement);

        if(visitedLocation == visitedLocations.end())
        {
            visitedLocations.emplace_back(movement);
            visitedLocationsDirections.emplace_back(guardDirection);
        }
        else if(visitedLocationsDirections.at(visitedLocation - visitedLocations.begin()) == guardDirection)
        {
            guardIsStuck = true;
            break;
        }
    }

    return guardIsStuck;
}

// Brute force solution
std::string AoCSolution_2024_6::PartTwo()
{
    // x, y, left top is 0,0
    size_t guardStartX = 0;
    size_t guardStartY = 0;
    Direction guardDirection{Direction::up};

    // Find initial Guard position
    size_t yCount = 0;
    for(const auto& line : m_input)
    {
        auto guardIt = std::find(line.begin(), line.end(), '^');
        if(guardIt != line.end())
        {
            guardStartX = guardIt - line.begin();
            guardStartY = yCount;
            break;
        }
        yCount++;
    }

    const auto guardStartPosition = std::make_pair(guardStartX, guardStartY);

    bool guardOnGrid = true;
    
    std::vector<std::pair<size_t, size_t>> visitedLocations;
    visitedLocations.emplace_back(guardStartPosition);

    std::pair guardMoveDirection = std::make_pair<long long int, long long int>(guardDirection % 2 == 1 ? (guardDirection == 3 ? -1 : 1) : 0, guardDirection % 2 == 0 ? (guardDirection == 0 ? -1 : 1) : 0);
    std::pair<size_t, size_t> guardPosition = guardStartPosition;
    std::pair<size_t, size_t> movement = guardStartPosition;
    while(guardOnGrid)
    {
        movement.first += guardMoveDirection.first;
        movement.second += guardMoveDirection.second;

        if(movement.second < 0 || movement.first < 0 || movement.second >= m_input.size() || movement.first >= m_input.at(movement.second).size())
        {
            movement.first -= guardMoveDirection.first;
            movement.second -= guardMoveDirection.second;

            auto xDiff = ((long long int)guardPosition.first) - ((long long int)movement.first);
            auto yDiff = ((long long int)guardPosition.second) - ((long long int)movement.second);

            guardOnGrid = false;
            break;
        }

        // Guard meets a barrel, move him to it and rotate 90 degrees clockwise
        if(m_input.at(movement.second).at(movement.first) == '#')
        {
            movement.first -= guardMoveDirection.first;
            movement.second -= guardMoveDirection.second;

            auto xDiff = ((long long int)guardPosition.first) - ((long long int)movement.first);
            auto yDiff = ((long long int)guardPosition.second) - ((long long int)movement.second);

            guardPosition = movement;

            // Rotate
            guardDirection = static_cast<Direction>((guardDirection + 1) % 4);
            guardMoveDirection.first = guardDirection % 2 == 1 ? (guardDirection == 3 ? -1 : 1) : 0;
            guardMoveDirection.second = guardDirection % 2 == 0 ? (guardDirection == 0 ? -1 : 1) : 0;
        }

        if(std::find(visitedLocations.begin(), visitedLocations.end(), movement) == visitedLocations.end())
        {
            visitedLocations.emplace_back(movement);
        }
    }

    // Try putting an obstacle on all of the positions in the guards patrol path. If she ends up in a previouslyy visited position,
    // with the same direction, she is stuck in a loop
    size_t sum = 0;
    for(auto location : visitedLocations)
    {
        if(location == guardStartPosition)
        {
            continue;
        }
        sum += guardIsStuck(m_input, guardStartPosition, location);
    }
    return std::to_string(sum);
}