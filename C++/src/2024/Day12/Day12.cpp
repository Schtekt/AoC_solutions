#include "Day12.h"
#include <sstream>
#include <map>

AoCSolution_2024_12::AoCSolution_2024_12():
AoCDaySolution({"2024", "12"})
{}

std::vector<std::pair<char, std::vector<std::pair<size_t, size_t>>>> getRegions(const std::vector<std::string>& input)
{
    std::vector<std::pair<char, std::vector<std::pair<size_t, size_t>>>> regions;
    for(size_t y = 0; y < input.size(); y++)
    {
        const auto& line = input.at(y);
        for(size_t x = 0; x < line.size(); x++)
        {
            long long int foundRegion = -1;
            std::vector<size_t> regionsToMerge;

            // Check if there are any existing regions, of same type, that borders this plot
            for(int i = 0; i < regions.size(); i++)
            {
                auto& region = regions.at(i);
                if(region.first == line.at(x))
                {
                    for(const auto plot : region.second)
                    {
                        if((plot.first == x || plot.second == y) && (x - plot.first == 1 || y - plot.second == 1))
                        {
                            if(foundRegion == -1)
                            {
                                region.second.emplace_back(std::make_pair(x, y));
                                foundRegion = i;
                            }
                            // Merge this region with already found region
                            else if(i != foundRegion)
                            {
                                regionsToMerge.emplace_back(i);
                            }
                        }
                    }
                }
            }

            if(foundRegion != -1 && regionsToMerge.size() != 0)
            {
                auto& regionToMergeInto = regions.at(foundRegion);
                for(size_t i = regionsToMerge.size() - 1; i >= 0; i--)
                {
                    size_t regionIndex =  regionsToMerge.at(i);
                    auto& region = regions.at(regionIndex);
                    regionToMergeInto.second.insert(regionToMergeInto.second.end(), region.second.begin(), region.second.end());

                    regions.erase(regions.begin() + regionIndex);

                    if(i == 0)
                    {
                        break;
                    }
                }
            }

            if(foundRegion == -1)
            {
                // Create new region
                std::vector<std::pair<size_t, size_t>> plots;
                plots.emplace_back(std::make_pair(x, y));
                regions.emplace_back(std::make_pair(line.at(x), plots));
            }
        }
    }

    return regions;
}


std::string AoCSolution_2024_12::PartOne()
{   
    auto regions = getRegions(m_input);
    
    std::vector<size_t> perimiters;
    // Calculate perimiters for each region
    for(const auto& region : regions)
    {
        size_t& regionPerimiter = perimiters.emplace_back(0);
        const char regionType = region.first;
        for(const auto& plot : region.second)
        {
            size_t x = plot.first;
            size_t y = plot.second;
            regionPerimiter += y == 0;
            regionPerimiter += y == m_input.size() - 1;
            regionPerimiter += y > 0 && m_input.at(y - 1).at(x) != regionType;
            regionPerimiter += y <  m_input.size() - 1 && m_input.at(y + 1).at(x) != regionType;

            const auto & line = m_input.at(y);
            regionPerimiter += x == 0;
            regionPerimiter += x == line.size() - 1;
            regionPerimiter += x != 0 && line.at(x - 1) != regionType;
            regionPerimiter += x < line.size() - 1 && line.at(x + 1) != regionType;
        }
    }

    size_t totalPrice = 0;
    for(int i = 0; i < perimiters.size(); i++)
    {
        totalPrice += perimiters.at(i) * regions.at(i).second.size();
    }

    return std::to_string(totalPrice);
}

std::string AoCSolution_2024_12::PartTwo()
{
    auto regions = getRegions(m_input);
    
    size_t mapHeight = m_input.size();
    size_t mapWidth = m_input.at(0).size();
    size_t totalPrice = 0;
    for(const auto& region : regions)
    {
        // Since every fence connects with itself,
        // the number of lines is the same as the amount of corners

        // e.g.
        /*
            *---*
            |   |
            |   |
            *---*

              *-*
              | |
            *-* |
            |   |
            *---*

            *-------*
            | *---* |
            | |   | |
            | |   | |
            | |   | |
            *-*   *-*
        */

        // Layouts
        /*
            Not a corner (Most of these share corners with another plot,
            but these will be caught in other checks)
            AAA AAA ABA AAA AAA AAA ABA
            AAA AAB AAA BAA AAA BAB AAA
            AAA AAA AAA AAA ABA AAA ABA

            SINGLE CORNER (If two foreign plots, that are not in the same y or x)
             B   A   A   B
            AAB AAB BAA BAA
             A   B   B   A

            DOUBLE CORNER (if three foreign plots)
             B   A   B   B
            AAB BAB BAA BAB
             B   B   B   A

            QUADRUPLE CORNER (if four foreign plots)
             B
            BAB
             B

            EDGE CASES (One corner per diag foreign, if no foreign in vert and hor lines.)
            BAB AAB
            AAA BAA
            BAB BBA
        */

        size_t corners = 0;
        for(const auto& plot : region.second)
        {
            size_t x = plot.first;
            size_t y = plot.second;

            uint8_t nrOfForeign = 0;

            bool foreign_up = y == 0;
            foreign_up = foreign_up || m_input.at(y - 1).at(x) != region.first;

            bool foreign_left = x == 0;
            foreign_left = foreign_left || m_input.at(y).at(x - 1) != region.first;

            bool foreign_down = y == mapHeight - 1;
            foreign_down = foreign_down || m_input.at(y + 1).at(x) != region.first;

            bool foreign_right = x == mapWidth - 1;
            foreign_right = foreign_right || m_input.at(y).at(x + 1) != region.first;

            nrOfForeign += foreign_up + foreign_left + foreign_down + foreign_right;

            if(nrOfForeign == 2)
            {
                corners += foreign_up != foreign_down;
            }
            else if(nrOfForeign == 3)
            {
                corners += 2;
            }
            else if(nrOfForeign == 4)
            {
                corners += 4;
            }

            // Edge cases
            bool foreign_up_left = (y == 0 || x == 0) 
                    || m_input.at(y - 1).at(x - 1) != region.first;
            corners += foreign_up_left && !foreign_up && !foreign_left;

            bool foreign_up_right = (y == 0 || x == mapWidth - 1) 
                    || m_input.at(y - 1).at(x + 1) != region.first;
            corners += foreign_up_right && !foreign_up && !foreign_right;

            bool foreign_down_left = (y == mapHeight - 1 || x == 0)
                    || m_input.at(y + 1).at(x - 1) != region.first;
            corners += foreign_down_left && !foreign_down && !foreign_left;

            bool foreign_down_rigth = (y == mapHeight - 1 || x == mapWidth - 1) 
                    || m_input.at(y + 1).at(x + 1) != region.first;
            corners += foreign_down_rigth && !foreign_down && !foreign_right;
        }
        totalPrice += corners * region.second.size();
    }
    return std::to_string(totalPrice);
}