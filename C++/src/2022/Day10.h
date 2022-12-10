#pragma once
#include "../Utility.h"
#include <vector>
#include <sstream>

class AoCSolution_2022_10 : public AoCDaySolution
{
public:
    AoCSolution_2022_10(AoCUtilityTool& tool);
    std::string PartOne();

    std::string PartTwo();

private:
};

AoCSolution_2022_10::AoCSolution_2022_10(AoCUtilityTool& tool) : AoCDaySolution(tool, { "2022", "10" })
{

}

std::string AoCSolution_2022_10::PartOne()
{
    long x = 1;
    long toAddX = 0;
    unsigned int countdown = 0;
    size_t cycleCount = 0;
    size_t inputLine = 0;
    size_t score = 0;

    while(m_input.size() > inputLine)
    {
        if ((cycleCount + 20) % 40 == 0)
        {
            score += cycleCount * x;
        }

        if (countdown == 0)
        {
            std::stringstream ss(m_input[inputLine++]);
            std::string cmd;

            ss >> cmd;

            x += toAddX;
            toAddX = 0;

            if (cmd == "addx")
            {
                countdown = 1;
                ss >> toAddX;
            }
        }
        else
        {
            countdown--;
        }
        cycleCount++;
    }

    return std::to_string(score);
}

std::string AoCSolution_2022_10::PartTwo()
{
    long x = 1;
    long toAddX = 0;
    unsigned int countdown = 0;
    size_t inputLine = 0;
    size_t cycleCount = 0;

    // prepare pixels with default values.
    std::string outputLines[6];
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 40; j++)
            outputLines[i] += ".";
    }

    while (m_input.size() > inputLine)
    {
        if (countdown == 0)
        {
            std::stringstream ss(m_input[inputLine++]);
            std::string cmd;

            ss >> cmd;

            x += toAddX;
            toAddX = 0;

            if (cmd == "addx")
            {
                countdown = 1;
                ss >> toAddX;
            }
        }
        else if (countdown > 0)
        {
            countdown--;
        }

        if (abs(static_cast<long>((cycleCount % 40) - x)) < 2)
        {
            outputLines[cycleCount / 40][cycleCount % 40] = '#';
        }
        cycleCount++;
    }

    // Sum up all pixels to a "screen"
    std::string ans;
    for (int i = 0; i < 6; i++)
    {
        ans += outputLines[i];
        ans += "\n";
    }
    return ans;
}