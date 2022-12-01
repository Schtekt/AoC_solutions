#pragma once
#include "../Utility.h"
class AoCSolution_2021_2 : public AoCDaySolution
{
public:
	AoCSolution_2021_2(AoCUtilityTool& tool) : AoCDaySolution(tool, { "2021","2" }) {};
	void PartOne();

	void PartTwo();
private:
};

void AoCSolution_2021_2::PartOne()
{
	int depth = 0;
	int horizontal = 0;
	for(std::string input : m_input)
	{
		int pos = input.find(" ");
		auto cmd = input.substr(0, pos);
		auto units = stoi(input.substr(pos));

		if(cmd == "forward")
		{
			horizontal += units;
		}
		else if(cmd == "down")
		{
			depth += units;
		}
		else if(cmd == "up")
		{
			depth -= units;
		}
	}

	m_resultPartOne = std::to_string(horizontal * depth);
}

void AoCSolution_2021_2::PartTwo()
{
	size_t depth = 0;
	size_t horizontal = 0;
	size_t aim = 0;
	for (std::string input : m_input)
	{
		int pos = input.find(" ");
		auto cmd = input.substr(0, pos);
		auto units = stoi(input.substr(pos));

		if (cmd == "forward")
		{
			horizontal += units;
			depth += units * aim;
		}
		else if (cmd == "down")
		{
			aim += units;
		}
		else if (cmd == "up")
		{
			aim -= units;
		}
	}

	m_resultPartTwo = std::to_string(horizontal * depth);
}