#pragma once
#include "../Utility.h"
#include <vector>
#include <sstream>

class AoCSolution_2022_9 : public AoCDaySolution
{
public:
    AoCSolution_2022_9(AoCUtilityTool &tool);
    std::string PartOne();

    std::string PartTwo();

private:
};

AoCSolution_2022_9::AoCSolution_2022_9(AoCUtilityTool &tool) : AoCDaySolution(tool, {"2022", "9"})
{

}

struct pos
{
    int x;
    int y;
};

enum Direction
{
    Up,
    Down,
    Left,
    Right
};

void MoveHead(pos& head, char dir, unsigned int nrOfSteps, pos& tail, std::vector<pos>& visitedPos)
{
    for (unsigned int i = 0; i < nrOfSteps; i++)
    {
        switch (dir)
        {
        case 'U':
            head.y += 1;
            break;
        case 'D':
            head.y -= 1;
            break;
        case 'L':
            head.x -= 1;
            break;
        case 'R':
            head.x += 1;
            break;
        default:
            break;
        }

        if (sqrt(pow(head.x - tail.x, 2) + pow(head.y - tail.y, 2)) >= 2)
        {
            int x = head.x - tail.x;
            int y = head.y - tail.y;

            if(x != 0)
                tail.x += abs(x) / x;
            if(y != 0)
                tail.y += abs(y) / y;
        }

        bool found = false;
        for (auto position : visitedPos)
        {
            if (position.x == tail.x && position.y == tail.y)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            visitedPos.push_back(tail);
        }
    }
}

void MoveHeads(pos& head, char dir, unsigned int nrOfSteps, std::vector<pos>& tails, std::vector<pos>& visitedPos)
{
    for (unsigned int i = 0; i < nrOfSteps; i++)
    {
        switch (dir)
        {
        case 'U':
            head.y += 1;
            break;
        case 'D':
            head.y -= 1;
            break;
        case 'L':
            head.x -= 1;
            break;
        case 'R':
            head.x += 1;
            break;
        default:
            break;
        }

        pos* currHead = &head;

        for (auto& currTail : tails)
        {
            if (sqrt(pow(currHead->x - currTail.x, 2) + pow(currHead->y - currTail.y, 2)) >= 2)
            {
                int x = currHead->x - currTail.x;
                int y = currHead->y - currTail.y;

                if (x != 0)
                    currTail.x += abs(x) / x;
                if (y != 0)
                    currTail.y += abs(y) / y;

            }
            currHead = &currTail;
        }

        pos lastTail = tails[tails.size() - 1];
        bool found = false;
        for (auto position : visitedPos)
        {
            if (position.x == lastTail.x && position.y == lastTail.y)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            visitedPos.push_back(lastTail);
        }
    }
}

std::string AoCSolution_2022_9::PartOne()
{
    std::vector<pos> visitedPositions;
    pos head{ 0,0 };
    pos tail{ 0,0 };
    
    for (auto line : m_input)
    {
        std::stringstream ss(line);
        char dir;
        unsigned int steps;
        ss >> dir;
        ss >> steps;
        MoveHead(head, dir, steps, tail, visitedPositions);
    }
    return std::to_string(visitedPositions.size());
}

std::string AoCSolution_2022_9::PartTwo()
{
    std::vector<pos> visitedPositions;
    pos head{ 0,0 };

    std::vector<pos> tails;
    for (int i = 0; i < 9; i++)
    {
        pos tail{ 0,0 };
        tails.push_back(tail);
    }

    for (auto line : m_input)
    {
        std::stringstream ss(line);
        char dir;
        unsigned int steps;
        ss >> dir;
        ss >> steps;
        MoveHeads(head, dir, steps, tails, visitedPositions);
    }
    return std::to_string(visitedPositions.size());
}