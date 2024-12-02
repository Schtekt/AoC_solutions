#include "Day2.h"

#include <sstream>

AoCSolution_2024_2::AoCSolution_2024_2()
: AoCDaySolution{{"2024", "2"}}
{

}

enum class ReportState {
    Increasing,
    Decreasing,
    None,
    Unset
};

std::string AoCSolution_2024_2::PartOne()
{
    int numSafeReports = 0;
    for(const auto& line : m_input)
    {
        int first;
        int second;

        std::istringstream stream{line};
        stream >> first;
        stream >> second;

        ReportState originalState = first > second ? ReportState::Decreasing : (first < second ? ReportState::Increasing : ReportState::None);

        unsigned int diff = abs(first - second);

        if(originalState == ReportState::None || diff > 3)
        {
            continue;
        }

        bool reportIsSafe = true;
        first = second;
        while(stream >> second)
        {
            ReportState newState = first > second ? ReportState::Decreasing : (first < second ? ReportState::Increasing : ReportState::None);
            unsigned int diff = abs(first - second);

            if(newState != originalState || diff > 3)
            {
                reportIsSafe = false;
                break;
            }

            first = second;
        }
        numSafeReports += reportIsSafe;
    }

    return std::to_string(numSafeReports);
}

std::string AoCSolution_2024_2::PartTwo()
{
    int numSafeReports = 0;
    for(const auto& line : m_input)
    {
        int val;

        std::istringstream stream{line};
        std::vector<int> values;

        while(stream >> val)
        {
            values.emplace_back(val);
        }

        bool reportIsSafe = false;

        for(int i = 0; i < values.size(); i++)
        {
            ReportState lastState = ReportState::Unset;
            bool reportVariantSafe = true;

            auto subsetValues = values;
            subsetValues.erase(subsetValues.begin() + i);

            for(int j = 0; j < subsetValues.size() - 1; j++)
            {
                ReportState newState = subsetValues[j] > subsetValues[j + 1] ? ReportState::Decreasing : (subsetValues[j] < subsetValues[j + 1] ? ReportState::Increasing : ReportState::None);

                if(lastState == ReportState::Unset)
                {
                    lastState = newState;
                }

                unsigned int diff = abs(subsetValues[j] - subsetValues[j + 1]);
                if(lastState != newState || diff > 3 || newState == ReportState::None)
                {
                    reportVariantSafe = false;
                    break;
                }
            }

            if(reportVariantSafe)
            {
                reportIsSafe = true;
                break;
            }
        }

        numSafeReports += reportIsSafe;
    }

    return std::to_string(numSafeReports);
}