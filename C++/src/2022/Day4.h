#pragma once
#include "../Utility.h"
#include <iostream>

class AoCSolution_2022_4 : public AoCDaySolution
{
public:
	AoCSolution_2022_4(AoCUtilityTool& tool);
	std::string PartOne();

	std::string PartTwo();
private:
};


AoCSolution_2022_4::AoCSolution_2022_4(AoCUtilityTool& tool) : AoCDaySolution(tool, {"2022", "4"})
{
}

std::string AoCSolution_2022_4::PartOne()
{
    size_t count = 0;
    for(auto line : m_input)
    {
        std::string firstSec = line.substr(0, line.find(','));
        std::string secondSec = line.substr(line.find(',') + 1);

        size_t firstStart = std::stoi(firstSec.substr(0, firstSec.find('-')));
        size_t firstEnd = std::stoi(firstSec.substr(firstSec.find('-') + 1));

        size_t secondStart = std::stoi(secondSec.substr(0, secondSec.find('-')));
        size_t secondEnd = std::stoi(secondSec.substr(secondSec.find('-') + 1));

        if((firstStart >= secondStart && firstEnd <= secondEnd) || (firstStart <= secondStart && firstEnd >= secondEnd))
        {
            count++;
        }
    }
    return std::to_string(count);
}

std::string AoCSolution_2022_4::PartTwo()
{
    size_t count = 0;
    for(auto line : m_input)
    {
        std::string firstSec = line.substr(0, line.find(','));
        std::string secondSec = line.substr(line.find(',') + 1);

        size_t firstStart = std::stoi(firstSec.substr(0, firstSec.find('-')));
        size_t firstEnd = std::stoi(firstSec.substr(firstSec.find('-') + 1));

        size_t secondStart = std::stoi(secondSec.substr(0, secondSec.find('-')));
        size_t secondEnd = std::stoi(secondSec.substr(secondSec.find('-') + 1));

        if((firstStart >= secondStart && firstStart <= secondEnd) || (firstStart <= secondStart && firstEnd >= secondStart)
        || (secondStart >= firstStart && secondStart <= firstEnd) || (secondStart <= firstStart && secondEnd >= firstStart))
        {
            count++;
        }
    }
    return std::to_string(count);
}