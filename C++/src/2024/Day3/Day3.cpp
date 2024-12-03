#include "Day3.h"
#include <regex>

AoCSolution_2024_3::AoCSolution_2024_3():
AoCDaySolution({"2024", "3"})
{

}

std::string AoCSolution_2024_3::PartOne()
{
    std::regex mulRegex{"mul\\(([0-9]*),([0-9]*)\\)"};

    long long int sum = 0;
    for(const auto line : m_input)
    {
        auto matchBegin = std::sregex_iterator(line.begin(), line.end(), mulRegex);
        auto matchEnd = std::sregex_iterator();

        for(auto it = matchBegin; it != matchEnd; it++)
        {
            auto match = *it;
            auto first = match.str(1);
            auto second = match.str(2);

            sum += std::atoi(first.c_str()) * std::atoi(second.c_str());
        }
    }

    return std::to_string(sum);
}

std::string AoCSolution_2024_3::PartTwo()
{
    std::regex mulRegex{"mul\\(([0-9]*),([0-9]*)\\)"};
    std::regex doRegex{"do\\(\\)"};
    std::regex dontRegex{"don't\\(\\)"};

    std::string combined = "";
    for(const auto line : m_input)
    {
        combined += line;
    }

    auto mulMatchBegin = std::sregex_iterator(combined.begin(), combined.end(), mulRegex);
    auto doMatchBegin = std::sregex_iterator{combined.begin(), combined.end(), doRegex};
    auto dontMatchBegin = std::sregex_iterator{combined.begin(), combined.end(), dontRegex};
    auto end = std::sregex_iterator();

    auto doIter = doMatchBegin;
    auto doIterNext = doMatchBegin;
    doIterNext++;

    auto dontIter = dontMatchBegin;
    auto dontIterNext = dontMatchBegin;
    dontIterNext++;

    long long int sum = 0;
    for(auto it = mulMatchBegin; it != end; it++)
    {
        auto mulMatch = *it;

        while(doIterNext != end && doIterNext->position(0) < mulMatch.position(0))
        {
            doIter++;
            doIterNext++;
        }

        while(dontIterNext != end && dontIterNext->position(0) < mulMatch.position(0))
        {
            dontIter++;
            dontIterNext++;
        }

        bool validMull = true;
        
        // Multiplication is invalid if a "dont" statement appears before it,
        // and there is no "do" statement between the "dont" and "mul" statements.
        if(dontIter->position() < mulMatch.position() &&
            doIter->position() < dontIter->position())
        {
            validMull = false;
        }

        if(validMull)
        {
            auto first = mulMatch.str(1);
            auto second = mulMatch.str(2);

            sum += std::atoi(first.c_str()) * std::atoi(second.c_str());
        }
    }

    return std::to_string(sum);
}