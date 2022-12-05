#pragma once
#include "../Utility.h"
#include <stack>
#include <sstream>
#include <iostream>

class CrateMap
{
public:
    void MoveCrates(unsigned int from, unsigned int to, unsigned int nrOf);
    void MoveCratesKeepOrder(unsigned int from, unsigned int to, unsigned int nrOf);
    void ReadInput(const std::vector<std::string> &input);
    std::string GetTop();

private:
    std::stack<char> m_stacks[9];
};

void CrateMap::MoveCrates(unsigned int from, unsigned int to, unsigned int nrOf)
{
    for (unsigned int i = 0; i < nrOf; i++)
    {
        m_stacks[to].push(m_stacks[from].top());
        m_stacks[from].pop();
    }
}

void CrateMap::MoveCratesKeepOrder(unsigned int from, unsigned int to, unsigned int nrOf)
{
    std::stack<char> tempStack;
    for (unsigned int i = 0; i < nrOf; i++)
    {
        tempStack.push(m_stacks[from].top());
        m_stacks[from].pop();
    }

    for (unsigned int i = 0; i < nrOf; i++)
    {
        m_stacks[to].push(tempStack.top());
        tempStack.pop();
    }
}

void CrateMap::ReadInput(const std::vector<std::string> &input)
{
    bool done = false;
    std::stack<char> tempStacks[9];
    for (auto line : input)
    {
        if (line[1] == '1')
        {
            break;
        }
        for (unsigned int i = 0; i < line.size(); i += 4)
        {
            if (line[i + 1] >= 'A' && line[i + 1] <= 'Z')
            {
                tempStacks[i / 4].push(line[i + 1]);
            }
        }
    }

    for (unsigned int i = 0; i < 9; i++)
    {
        unsigned int stackSize = tempStacks[i].size();
        for (unsigned int j = 0; j < stackSize; j++)
        {
            m_stacks[i].push(tempStacks[i].top());
            tempStacks[i].pop();
        }
    }
}

std::string CrateMap::GetTop()
{
    std::string toReturn = "";
    for (int i = 0; i < 9; i++)
    {
        toReturn += m_stacks[i].top();
    }
    return toReturn;
}

class AoCSolution_2022_5 : public AoCDaySolution
{
public:
    AoCSolution_2022_5(AoCUtilityTool &tool);
    std::string PartOne();

    std::string PartTwo();

private:
};

AoCSolution_2022_5::AoCSolution_2022_5(AoCUtilityTool &tool) : AoCDaySolution(tool, {"2022", "5"})
{
}

std::string AoCSolution_2022_5::PartOne()
{
    CrateMap map;
    map.ReadInput(m_input);
    unsigned int nrOf, from, to;
    std::string temp;
    bool start = false;
    for (auto line : m_input)
    {
        if (start)
        {
            std::stringstream stream(line);
            stream >> temp;
            stream >> nrOf;
            stream >> temp;
            stream >> from;
            stream >> temp;
            stream >> to;

            map.MoveCrates(from - 1, to - 1, nrOf);
        }
        else
        {
            if (line == "")
                start = true;
        }
    }
    return map.GetTop();
}

std::string AoCSolution_2022_5::PartTwo()
{
    CrateMap map;
    map.ReadInput(m_input);
    unsigned int nrOf, from, to;
    std::string temp;
    bool start = false;
    for (auto line : m_input)
    {
        if (start)
        {
            std::stringstream stream(line);
            stream >> temp;
            stream >> nrOf;
            stream >> temp;
            stream >> from;
            stream >> temp;
            stream >> to;

            map.MoveCratesKeepOrder(from - 1, to - 1, nrOf);
        }
        else
        {
            if (line == "")
                start = true;
        }
    }
    return map.GetTop();
}