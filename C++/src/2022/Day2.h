#pragma once
#include "Utility.h"
#include <iostream>

class AoCSolution_2022_2 : public AoCDaySolution
{
public:
	AoCSolution_2022_2(AoCUtilityTool& tool);
	std::string PartOne();

	std::string PartTwo();
private:
};


const int baseScoreRock = 1;
const int baseScorePaper = 2;
const int baseScoreScissors = 3;

const int baseScoreLoss = 0;
const int baseScoreDraw = 3;
const int baseScoreVictory = 6;

const char elfRock = 'A';
const char elfPaper = 'B';
const char elfScissors = 'C';


AoCSolution_2022_2::AoCSolution_2022_2(AoCUtilityTool& tool) : AoCDaySolution(tool, {"2022", "2"})
{
}

std::string AoCSolution_2022_2::PartOne()
{
    size_t score = 0;
    for(auto line : m_input)
    {
        if(line[2] == 'X')
        {
            score += baseScoreRock;

            if(line[0] == elfRock)
            {
                score += baseScoreDraw;
            }
            else if(line[0] == elfPaper)
            {
                score += baseScoreLoss;
            }
            else if(line[0] == elfScissors)
            {
                score += baseScoreVictory;
            }
        }
        else if(line[2] == 'Y')
        {
            score += baseScorePaper;

            if(line[0] == elfRock)
            {
                score += baseScoreVictory;
            }
            else if(line[0] == elfPaper)
            {
                score += baseScoreDraw;
            }
            else if(line[0] == elfScissors)
            {
                score += baseScoreLoss;
            }
        }
        else if(line[2] == 'Z')
        {
            score += baseScoreScissors;

            if(line[0] == elfRock)
            {
                score += baseScoreLoss;
            }
            else if(line[0] == elfPaper)
            {
                score += baseScoreVictory;
            }
            else if(line[0] == elfScissors)
            {
                score += baseScoreDraw;
            }
        }
    }
    return std::to_string(score);
}

std::string AoCSolution_2022_2::PartTwo()
{
size_t score = 0;
    for(auto line : m_input)
    {
        if(line[2] == 'X')
        {
            score += baseScoreLoss;

            if(line[0] == elfRock)
            {
                score += baseScoreScissors;
            }
            else if(line[0] == elfPaper)
            {
                score += baseScoreRock;
            }
            else if(line[0] == elfScissors)
            {
                score += baseScorePaper;
            }
        }
        else if(line[2] == 'Y')
        {
            score += baseScoreDraw;

            if(line[0] == elfRock)
            {
                score += baseScoreRock;
            }
            else if(line[0] == elfPaper)
            {
                score += baseScorePaper;
            }
            else if(line[0] == elfScissors)
            {
                score += baseScoreScissors;
            }
        }
        else if(line[2] == 'Z')
        {
            score += baseScoreVictory;

            if(line[0] == elfRock)
            {
                score += baseScorePaper;
            }
            else if(line[0] == elfPaper)
            {
                score += baseScoreScissors;
            }
            else if(line[0] == elfScissors)
            {
                score += baseScoreRock;
            }
        }
    }
    return std::to_string(score);
}