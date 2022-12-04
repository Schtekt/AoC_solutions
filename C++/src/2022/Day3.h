#pragma once
#include "../Utility.h"
#include <iostream>

class AoCSolution_2022_3 : public AoCDaySolution
{
public:
	AoCSolution_2022_3(AoCUtilityTool& tool);
	std::string PartOne();

	std::string PartTwo();
private:
};


AoCSolution_2022_3::AoCSolution_2022_3(AoCUtilityTool& tool) : AoCDaySolution(tool, {"2022", "3"})
{
}

int calcCharacterScore(char character)
{
	if(character >= 'a' && character <= 'z')
		return int(character - 'a') + 1;
	else
		return int(character - 'A') + 27;
}

std::string AoCSolution_2022_3::PartOne()
{
	size_t sum = 0;
	for(auto line : m_input)
	{
		std::string firstHalf = line.substr(0, line.size() / 2);
		std::string secondHalf = line.substr(line.size() / 2);
		bool found = false;

		for(char characterFirst : firstHalf)
		{
			for(char characterSec : secondHalf)
			{
				if(characterFirst == characterSec)
				{
					sum += calcCharacterScore(characterFirst);
					found = true;
					break;
				}	
			}

			if(found)
			{
				found = false;
				break;
			}
		}
	}
    return std::to_string(sum);
}

std::string AoCSolution_2022_3::PartTwo()
{
	bool found = false;
	size_t sum = 0;

	for(size_t i = 0; i < m_input.size(); i+=3)
	{
		for(auto first : m_input[i])
		{
			for(auto sec : m_input[i + 1])
			{
				for(auto third : m_input[i+2])
				{
					if(first == sec && sec == third)
					{
						found = true;
						sum += calcCharacterScore(first);
						break;
					}
				}
				if(found)
				{
					break;
				}
			}
			if(found)
			{
				found = false;
				break;
			}
		}
	}
    return std::to_string(sum);
}