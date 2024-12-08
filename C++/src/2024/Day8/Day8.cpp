#include "Day8.h"
#include <map>
#include <iostream>

AoCSolution_2024_8::AoCSolution_2024_8():
AoCDaySolution({"2024", "8"})
{}

std::string AoCSolution_2024_8::PartOne()
{
    std::map<char, std::vector<std::pair<uint8_t, uint8_t>>> antennas;

    // Parse antenna locations
    for(uint8_t y = 0; y < m_input.size(); y++)
    {
        const auto& line = m_input.at(y);
        for(uint8_t x = 0; x < line.size(); x++)
        {
            char character = line.at(x);
            if(character != '.')
            {
                antennas[character].emplace_back(std::make_pair(x, y));
            }
        }
    }

    std::vector<std::pair<uint8_t, uint8_t>> antinodePositions;

    for(const auto& antennaType : antennas)
    {
        for(const auto& antenna : antennaType.second)
        {
            for(const auto& secondAntenna : antennaType.second)
            {
                if(secondAntenna == antenna)
                {
                    continue;
                }

                // Calculate distance
                
                auto distance = std::make_pair<int8_t, int8_t>(antenna.first - secondAntenna.first, antenna.second - secondAntenna.second);
                auto antinodePosition = std::make_pair<int8_t, int8_t>(antenna.first + distance.first, antenna.second + distance.second);
                
                if(antinodePosition.second >= 0 && antinodePosition.second < m_input.size() && antinodePosition.first >= 0 && antinodePosition.first < m_input.at(antinodePosition.second).size() &&
                    std::find(antinodePositions.begin(), antinodePositions.end(), antinodePosition) == antinodePositions.end())
                {
                    antinodePositions.emplace_back(antinodePosition);
                }
            }
        }
    }

    return std::to_string(antinodePositions.size());
}

std::string AoCSolution_2024_8::PartTwo()
{
    std::map<char, std::vector<std::pair<uint8_t, uint8_t>>> antennas;

    // Parse antenna locations
    for(uint8_t y = 0; y < m_input.size(); y++)
    {
        const auto& line = m_input.at(y);
        for(uint8_t x = 0; x < line.size(); x++)
        {
            char character = line.at(x);
            if(character != '.')
            {
                antennas[character].emplace_back(std::make_pair(x, y));
            }
        }
    }

    std::vector<std::pair<uint8_t, uint8_t>> antinodePositions;

    for(const auto& antennaType : antennas)
    {
        for(const auto& antenna : antennaType.second)
        {
            for(const auto& secondAntenna : antennaType.second)
            {
                if(secondAntenna == antenna)
                {
                    if(antennaType.second.size() > 1 && std::find(antinodePositions.begin(), antinodePositions.end(), antenna) == antinodePositions.end())
                    {
                        antinodePositions.emplace_back(antenna);
                    }
                    continue;
                }

                // Calculate distance
                
                auto distance = std::make_pair<int8_t, int8_t>(antenna.first - secondAntenna.first, antenna.second - secondAntenna.second);
                auto antinodePosition = std::make_pair<int8_t, int8_t>(antenna.first + distance.first, antenna.second + distance.second);

                bool insideGrid = true;
                while(insideGrid)
                {
                    insideGrid = antinodePosition.second >= 0 && antinodePosition.second < m_input.size() && antinodePosition.first >= 0 && antinodePosition.first < m_input.at(antinodePosition.second).size();
                    
                    if(!insideGrid)
                    {
                        continue;
                    }
                    
                    if(std::find(antinodePositions.begin(), antinodePositions.end(), antinodePosition) == antinodePositions.end())
                    {
                        antinodePositions.emplace_back(antinodePosition);
                    }

                    antinodePosition.first += distance.first;
                    antinodePosition.second += distance.second;
                }
            }
        }
    }

    return std::to_string(antinodePositions.size());
}