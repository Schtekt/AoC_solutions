#pragma once
#include "Utility.h"
#include <map>
class AoCSolution_2021_3 : public AoCDaySolution
{
public:
	AoCSolution_2021_3(AoCUtilityTool& tool) : AoCDaySolution(tool, { "2021","3" }) {};
	std::string PartOne();

	std::string PartTwo();
private:
};

std::string AoCSolution_2021_3::PartOne()
{
    std::map<int, long> bitMap;

    for(auto line : m_input)
    {
        for(size_t i = 0; i < line.size(); i++)
        {
            bitMap[i] += line[i] == '1' ? 1 : -1;
        }
    }

    size_t gamma = 0;
    size_t epsilon = 0;
    size_t num = 0;
    for(size_t i = 0; i < bitMap.size(); i++)
    {
        num = bitMap[bitMap.size() - 1 - i] > 0 ? 1 : 0;
        gamma += static_cast<size_t>(static_cast<double>(num) * pow(2.0, static_cast<double>(i)));
        epsilon += static_cast<size_t>(static_cast<double>(1 - num) * pow(2.0, static_cast<double>(i)));
    }


    return std::to_string(gamma*epsilon);
}

std::vector<std::string> SplitResults(char character, size_t position, std::vector<std::string>& in)
{
    std::vector<std::string> out;

    for(size_t i = 0; i < in.size(); i++)
    {
        if(in[i][position] == character)
        {
            out.push_back(in[i]);
        }
    }
    return out;
}

std::map<int, long> CalcDiff(std::vector<std::string>& in)
{
    std::map<int, long> bitMap;

    for(auto line : in)
    {
        for(size_t i = 0; i < line.size(); i++)
        {
            bitMap[i] += line[i] == '1' ? 1 : -1;
        }
    }

    return bitMap;
}

std::string AoCSolution_2021_3::PartTwo()
{
    std::vector<std::string> oxyCandidates = m_input;
    std::vector<std::string> co2Candidates = m_input;

    std::map<int, long> bitMap = CalcDiff(m_input);

    size_t nrOfBits = bitMap.size();
    size_t oxyVal = 0;
    size_t co2Val = 0;
    for(size_t i = 0; i < nrOfBits; i++)
    {
        char character = bitMap[i] >= 0 ? '1' : '0';
        oxyCandidates = SplitResults(character, i, oxyCandidates);

        if(oxyCandidates.size() == 1)
            break;

        bitMap = CalcDiff(oxyCandidates);
    }

    // Reuse bitMap, but reinitialize it
    bitMap = CalcDiff(m_input);

    for(size_t i = 0; i < nrOfBits; i++)
    {
        char character = bitMap[i] < 0 ? '1' : '0';
        co2Candidates = SplitResults(character, i, co2Candidates);

        if(co2Candidates.size() == 1)
            break;

        bitMap = CalcDiff(co2Candidates);
    }

    for(size_t i = 0; i < nrOfBits; i++)
    {
        oxyVal += (oxyCandidates[0][i] == '1' ? 1 : 0) * static_cast<size_t>(pow(2, nrOfBits - 1 - i));
        co2Val += (co2Candidates[0][i] == '1' ? 1 : 0) * static_cast<size_t>(pow(2, nrOfBits - 1 - i));
    }

    return std::to_string(oxyVal * co2Val);
}