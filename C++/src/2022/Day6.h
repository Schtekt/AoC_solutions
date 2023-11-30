#pragma once
#include "Utility.h"
#include <string>

class AoCSolution_2022_6 : public AoCDaySolution
{
public:
    AoCSolution_2022_6(AoCUtilityTool &tool);
    std::string PartOne();

    std::string PartTwo();

private:
};

AoCSolution_2022_6::AoCSolution_2022_6(AoCUtilityTool &tool) : AoCDaySolution(tool, {"2022", "6"})
{

}

bool CheckAllUnique(char* arr, unsigned int nrToCompare)
{
    bool toReturn = true;
    for(unsigned int i = 0; i < nrToCompare; i++)
    {
        for(unsigned int j = i + 1; j < nrToCompare; j++)
        {
            if(arr[i] == arr[j])
            {
                toReturn = false;
            }
        }
    }
    return toReturn;
}

std::string AoCSolution_2022_6::PartOne()
{
    char characters[4];
    for(unsigned int i = 0; i < 4; i++)
    {
        characters[i] = m_input[0][i];
    }
    
    for(unsigned int i = 4; i < m_input[0].size(); i++)
    {
        if(CheckAllUnique(characters, 4))
            {
                return std::to_string(i);
            }

        for(unsigned int j = 0; j < 3; j++)
        {
            characters[j] = characters[j+1];
        }
        characters[3] = m_input[0][i];
    }
    return "-1";
}

std::string AoCSolution_2022_6::PartTwo()
{
    char characters[14];
    for(unsigned int i = 0; i < 14; i++)
    {
        characters[i] = m_input[0][i];
    }
    
    for(unsigned int i = 14; i < m_input[0].size(); i++)
    {
        if(CheckAllUnique(characters, 14))
        {
            return std::to_string(i);
        }
        for(unsigned int j = 0; j < 13; j++)
        {
            characters[j] = characters[j+1];
        }
        characters[13] = m_input[0][i];
    }
    return "-1";
}