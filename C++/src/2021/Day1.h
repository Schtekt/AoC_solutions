#include "../Utility.h"

class AoCSolution_2021_1 : public AoCDaySolution
{
public:
	AoCSolution_2021_1(AoCUtilityTool& tool);
	void PartOne();

	void PartTwo();
private:
};

AoCSolution_2021_1::AoCSolution_2021_1(AoCUtilityTool& tool) : AoCDaySolution(tool, {"2021", "1"})
{
}

void AoCSolution_2021_1::PartOne()
{
	size_t count = 0;
	for (size_t i = 1; i < m_input.size(); i++)
	{
		if (stoi(m_input[i]) > stoi(m_input[i - 1]))
		{
			count++;
		}
	}
	m_resultPartOne = std::to_string(count);
}

void AoCSolution_2021_1::PartTwo()
{
	size_t count = 0;
	for (size_t i = 1; i < m_input.size() - 2; i++)
	{
		if (stoi(m_input[i + 2]) + stoi(m_input[i + 1]) + stoi(m_input[i]) > stoi(m_input[i - 1]) + stoi(m_input[i]) + stoi(m_input[i + 1]))
		{
			count++;
		}
	}
	m_resultPartTwo = std::to_string(count);
}