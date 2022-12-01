#include "../Utility.h"

class AoCSolution_2022_1 : public AoCDaySolution
{
public:
	AoCSolution_2022_1(AoCUtilityTool& tool);
	void PartOne();

	void PartTwo();
private:
};

AoCSolution_2022_1::AoCSolution_2022_1(AoCUtilityTool& tool) : AoCDaySolution(tool, {"2022", "1"})
{
}

void AoCSolution_2022_1::PartOne()
{
	unsigned int calCountHighest = 0;
	unsigned int calCountCurr = 0;
	for(std::string input : m_input)
	{
		if(input == "")
		{
			if(calCountHighest < calCountCurr)
			{
				calCountHighest = calCountCurr;
			}
			
			calCountCurr = 0;
		}
		else
		{
			calCountCurr += std::stoi(input);
		}
	}

	// account for last elf
	if(calCountHighest < calCountCurr)
	{
		calCountHighest = calCountCurr;
	}

	m_resultPartOne = std::to_string(calCountHighest);
}

void AoCSolution_2022_1::PartTwo()
{
	unsigned int calCountHighest = 0;
	unsigned int calCountSecondHighest = 0;
	unsigned int calCountThirdHighest = 0;
	unsigned int calCountCurr = 0;
	for(std::string input : m_input)
	{
		if(input == "")
		{
			if(calCountHighest < calCountCurr)
			{
				calCountThirdHighest = calCountSecondHighest;
				calCountSecondHighest = calCountHighest;
				calCountHighest = calCountCurr;
			}
			else if(calCountSecondHighest < calCountCurr)
			{
				calCountThirdHighest = calCountSecondHighest;
				calCountSecondHighest = calCountCurr;
			}
			else if(calCountThirdHighest < calCountCurr)
			{
				calCountThirdHighest = calCountCurr;
			}
			
			calCountCurr = 0;
		}
		else
		{
			calCountCurr += std::stoi(input);
		}
	}

	// account for last elf
	if(calCountHighest < calCountCurr)
	{
		calCountThirdHighest = calCountSecondHighest;
		calCountSecondHighest = calCountHighest;
		calCountHighest = calCountCurr;
	}
	else if(calCountSecondHighest < calCountCurr)
	{
		calCountThirdHighest = calCountSecondHighest;
		calCountSecondHighest = calCountCurr;
	}
	else if(calCountThirdHighest < calCountCurr)
	{
		calCountThirdHighest = calCountCurr;
	}

	m_resultPartTwo = std::to_string(calCountHighest + calCountSecondHighest + calCountThirdHighest);
}