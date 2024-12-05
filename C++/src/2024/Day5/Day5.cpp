#include "Day5.h"
#include <regex>
#include <iostream>
#include <sstream>
#include <map>

AoCSolution_2024_5::AoCSolution_2024_5():
AoCDaySolution({"2024", "5"})
{}

std::string AoCSolution_2024_5::PartOne()
{    
    // Parse rules
    std::regex ruleFormat(R"(\d+\|\d+)");
    std::regex updateFormat(R"(\d+(,\d+)+)");

    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> updates;

    for(const auto& line : m_input)
    {
        std::istringstream ss{line};
        if(std::regex_match(line, ruleFormat))
        {
            int first;
            int second;
            ss >> first;
            ss.ignore(1, '|');
            ss >> second;

            rules.emplace_back(std::make_pair(first, second));
        }
        else if(std::regex_match(line, updateFormat))
        {
            auto& updateEntry = updates.emplace_back();
            int num;
            while(ss >> num)
            {
                updateEntry.emplace_back(num);
                ss.ignore(1, ',');
            }
        }
    }

    // Verify updates, and place valid ones in a separate vector
    std::vector<size_t> validUpdates;
    size_t count = 0;
    for(auto update : updates)
    {
        bool valid = true;
        for(auto rule : rules)
        {
            const auto& updateBegin = update.begin();
            const auto& updateEnd = update.end();
            auto firstPos = std::find(updateBegin, updateEnd, rule.first);
            auto secondPos = std::find(updateBegin, updateEnd, rule.second);

            if(firstPos > secondPos && firstPos != updateEnd && secondPos != updateEnd)
            {
                valid = false;
                break;
            }
        }

        if(valid)
        {
            validUpdates.emplace_back(count);
        }
        count++;
    }

    // Summarize all the middle numbers of each valid update
    size_t sum = 0;
    for(auto validUpdate : validUpdates)
    {
        const auto& update = updates.at(validUpdate);
        sum += update.at(update.size() / 2);
    }

   return std::to_string(sum);
}

std::string AoCSolution_2024_5::PartTwo()
{
    // Parse rules
    std::regex ruleFormat(R"(\d+\|\d+)");
    std::regex updateFormat(R"(\d+(,\d+)+)");

    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> updates;

    for(const auto& line : m_input)
    {
        std::istringstream ss{line};
        if(std::regex_match(line, ruleFormat))
        {
            int first;
            int second;
            ss >> first;
            ss.ignore(1, '|');
            ss >> second;

            rules.emplace_back(std::make_pair(first, second));
        }
        else if(std::regex_match(line, updateFormat))
        {
            auto& updateEntry = updates.emplace_back();
            int num;
            while(ss >> num)
            {
                updateEntry.emplace_back(num);
                ss.ignore(1, ',');
            }
        }
    }

    // Verify updates, and place invalid ones in a separate vector
    std::vector<size_t> invalidUpdateIndices;
    size_t count = 0;
    for(auto update : updates)
    {
        bool valid = true;
        for(auto rule : rules)
        {
            const auto& updateBegin = update.begin();
            const auto& updateEnd = update.end();
            auto firstPos = std::find(updateBegin, updateEnd, rule.first);
            auto secondPos = std::find(updateBegin, updateEnd, rule.second);

            if(firstPos > secondPos && firstPos != updateEnd && secondPos != updateEnd)
            {
                valid = false;
                break;
            }
        }

        if(!valid)
        {
            invalidUpdateIndices.emplace_back(count);
        }
        count++;
    }

    std::vector<std::vector<int>> correctedUpdates;

    // Brute force solution, swap untill it all makes sense
    for(const auto& invalidUpdateIndex : invalidUpdateIndices)
    {
        auto& correctionUpdate = correctedUpdates.emplace_back();

        for(auto num : updates.at(invalidUpdateIndex))
        {
            bool inserted = false;
            // Sort by insertion
            for(auto correctionIt = correctionUpdate.begin(); correctionIt != correctionUpdate.end(); correctionIt++)
            {
                auto ruleIt = std::find(rules.begin(), rules.end(), std::make_pair(num, *correctionIt));
                if(ruleIt != rules.end())
                {
                    correctionUpdate.insert(correctionIt, num);
                    inserted = true;
                    break;
                }
            }

            if(!inserted)
            {
                correctionUpdate.emplace_back(num);
            }
        }
    }

    // Summarize the middle number of each corrected updates
    size_t sum = 0;
    for(const auto& correctedUpdate : correctedUpdates)
    {
        sum += correctedUpdate.at(correctedUpdate.size() / 2);
    }

    return std::to_string(sum);
}