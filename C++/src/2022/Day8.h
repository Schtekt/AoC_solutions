#pragma once
#include "Utility.h"

class AoCSolution_2022_8 : public AoCDaySolution
{
public:
    AoCSolution_2022_8();
    std::string PartOne();

    std::string PartTwo();

private:
};

AoCSolution_2022_8::AoCSolution_2022_8() : AoCDaySolution({"2022", "8"})
{

}

bool IsTreeVisible(std::vector<std::string>& treeMap, unsigned int treePosX, unsigned int treePosY)
{
    bool visible = true;
    for (int i = 0; i < treePosX; i++)
    {
        if (static_cast<unsigned int>(treeMap[treePosY][i] - '0') >= static_cast<unsigned int>(treeMap[treePosY][treePosX] - '0'))
        {
            visible = false;
            break;
        }
    }
    if (visible)
    {
        return true;
    }

    visible = true;
    for (int i = treePosX + 1; i < treeMap[treePosY].size(); i++)
    {
        if (static_cast<unsigned int>(treeMap[treePosY][i] - '0') >= static_cast<unsigned int>(treeMap[treePosY][treePosX] - '0'))
        {
            visible = false;
            break;
        }
    }
    if (visible)
    {
        return true;
    }

    visible = true;
    for (int i = 0; i < treePosY; i++)
    {
        if (static_cast<unsigned int>(treeMap[i][treePosX] - '0') >= static_cast<unsigned int>(treeMap[treePosY][treePosX] - '0'))
        {
            visible = false;
            break;
        }
    }
    if (visible)
    {
        return true;
    }

    visible = true;
    for (int i = treePosY + 1; i < treeMap.size(); i++)
    {
        if (static_cast<unsigned int>(treeMap[i][treePosX] - '0') >= static_cast<unsigned int>(treeMap[treePosY][treePosX] - '0'))
        {
            visible = false;
            break;
        }
    }
    if (visible)
    {
        return true;
    }

    return false;
}

size_t CalcScenicViewScore(std::vector<std::string>& treeMap, unsigned int treePosX, unsigned int treePosY)
{
    size_t scenicViewScore = 1;
    bool visible = true;
    for (int i = treePosX - 1; i >= 0; i--)
    {
        if (static_cast<unsigned int>(treeMap[treePosY][i] - '0') >= static_cast<unsigned int>(treeMap[treePosY][treePosX] - '0'))
        {
            scenicViewScore *= (treePosX - i);
            visible = false;
            break;
        }
    }
    if (visible)
    {
        scenicViewScore *= treePosX;
    }

    visible = true;
    for (int i = treePosX + 1; i < treeMap[treePosY].size(); i++)
    {
        if (static_cast<unsigned int>(treeMap[treePosY][i] - '0') >= static_cast<unsigned int>(treeMap[treePosY][treePosX] - '0'))
        {
            scenicViewScore *= (i - treePosX);
            visible = false;
            break;
        }
    }
    if (visible)
    {
        scenicViewScore *= treeMap[treePosY].size() - 1 - treePosX;
    }

    visible = true;
    for (int i = treePosY - 1; i >= 0; i--)
    {
        if (static_cast<unsigned int>(treeMap[i][treePosX] - '0') >= static_cast<unsigned int>(treeMap[treePosY][treePosX] - '0'))
        {
            scenicViewScore *= (treePosY - i);
            visible = false;
            break;
        }
    }
    if (visible)
    {
        scenicViewScore *= treePosY;
    }


    visible = true;
    for (int i = treePosY + 1; i < treeMap.size(); i++)
    {
        if (static_cast<unsigned int>(treeMap[i][treePosX] - '0') >= static_cast<unsigned int>(treeMap[treePosY][treePosX] - '0'))
        {
            scenicViewScore *= (i - treePosY);
            visible = false;
            break;
        }
    }
    if (visible)
    {
        scenicViewScore *= treeMap[treePosY].size() - 1 - treePosY;
    }

    return scenicViewScore;
}

std::string AoCSolution_2022_8::PartOne()
{
    size_t count = 0;
    for (int i = 1; i < m_input.size() - 1; i++)
    {
        for (int j = 1; j < m_input[i].size() - 1; j++)
        {
            if (!IsTreeVisible(m_input, j, i))
            {
                count++;
            }
        }
    }
    return std::to_string(m_input.size() * m_input[0].size() - count);
}

std::string AoCSolution_2022_8::PartTwo()
{
    size_t highest = 0;
    for (int i = 1; i < m_input.size() - 1; i++)
    {
        for (int j = 1; j < m_input[i].size() - 1; j++)
        {
            size_t curr = CalcScenicViewScore(m_input, j, i);
            if (curr > highest)
            {
                highest = curr;
            }
        }
    }
    return std::to_string(highest);
}