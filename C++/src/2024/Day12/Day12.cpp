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
        for(const auto plot : region.second)
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
    return "";
}