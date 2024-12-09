#include "Day9.h"
#include <sstream>

struct FileBlock {
    FileBlock(int s, int f)
    : size(s), freespace(f) {}
    int size;
    int freespace;
};

AoCSolution_2024_9::AoCSolution_2024_9():
AoCDaySolution({"2024", "9"})
{}

std::string AoCSolution_2024_9::PartOne()
{
    char fileSize = 0;
    char freeSize = 0;

    std::vector<std::pair<uint8_t, uint8_t>> diskMap;

    // Assumed the input is only one string
    std::stringstream ss{m_input[0]};

    while(ss >> fileSize)
    {
        if(!(ss >> freeSize))
        {
            freeSize = '0';
        }

        diskMap.emplace_back(std::make_pair(fileSize - '0', freeSize - '0'));
    }

    size_t backIndex = diskMap.size() - 1;
    uint8_t internalIndex = 0;
    std::vector<std::pair<size_t, uint8_t>> compressedFileSystem;
    for(size_t i = 0; i < diskMap.size(); i++)
    {
        if(backIndex == i)
        {
            compressedFileSystem.emplace_back(std::make_pair(i, diskMap[i].first - internalIndex));
            break;
        }
        else if (backIndex < i)
        {
            break;
        }

        compressedFileSystem.emplace_back(std::make_pair(i, diskMap[i].first));

        // Fill in from back of diskMap
        uint8_t filled = 0;
        while(filled < diskMap[i].second)
        {
            uint8_t toFillFromCurrentBackIndex = std::min(diskMap[backIndex].first - internalIndex, diskMap[i].second - filled);
            compressedFileSystem.emplace_back(std::make_pair(backIndex, toFillFromCurrentBackIndex));
            internalIndex += toFillFromCurrentBackIndex;
            filled += toFillFromCurrentBackIndex;
            if(internalIndex == diskMap[backIndex].first)
            {
                internalIndex = 0;
                backIndex--;
            }

            if(backIndex <= i)
            {
                break;
            }
        }
    }

    // Calc checksum
    size_t checksum = 0;
    size_t multiplier = 0;
    for(size_t i = 0; i < compressedFileSystem.size(); i++)
    {
        for(size_t j = 0; j < compressedFileSystem.at(i).second; j++)
        {
            size_t lastChecksum = checksum;
            checksum += multiplier * compressedFileSystem.at(i).first;
            multiplier++;
        }
    }
    return std::to_string(checksum);
}

std::string AoCSolution_2024_9::PartTwo()
{
    char fileSize = 0;
    char freeSize = 0;

    std::vector<std::pair<uint8_t, uint8_t>> diskMap;

    // Assumed the input is only one string
    std::stringstream ss{m_input[0]};

    while(ss >> fileSize)
    {
        if(!(ss >> freeSize))
        {
            freeSize = '0';
        }

        diskMap.emplace_back(std::make_pair(fileSize - '0', freeSize - '0'));
    }

    size_t frontIndex = 0;
    std::vector<std::pair<size_t, uint8_t>> compressedFileSystem;
    std::vector<size_t> indicesPlaced;
    for(size_t frontIndex = 0; frontIndex < diskMap.size(); frontIndex++)
    {
        if(std::find(indicesPlaced.begin(), indicesPlaced.end(), frontIndex) == indicesPlaced.end())
        {
            compressedFileSystem.emplace_back(std::make_pair(frontIndex, diskMap[frontIndex].first));
            indicesPlaced.emplace_back(frontIndex);
        }
        else
        {
            compressedFileSystem.emplace_back(std::make_pair(0, diskMap[frontIndex].first));
        }

        size_t backIndex = diskMap.size() - 1;
        uint8_t currentFilledSpace = 0;
        // Find something that fits in this space
        while(backIndex > frontIndex && currentFilledSpace < diskMap[frontIndex].second)
        {
            if(diskMap[backIndex].first <= diskMap[frontIndex].second - currentFilledSpace
            && std::find(indicesPlaced.begin(), indicesPlaced.end(), backIndex) == indicesPlaced.end())
            {
                compressedFileSystem.emplace_back(backIndex, diskMap[backIndex].first);
                indicesPlaced.emplace_back(backIndex);
                currentFilledSpace += diskMap[backIndex].first;
            }
            backIndex--;
        }

        if(currentFilledSpace < diskMap[frontIndex].second)
        {
            compressedFileSystem.emplace_back(0, diskMap[frontIndex].second - currentFilledSpace);
        }
    }

    // Calc checksum
    size_t checksum = 0;
    size_t multiplier = 0;
    for(size_t i = 0; i < compressedFileSystem.size(); i++)
    {
        for(size_t j = 0; j < compressedFileSystem.at(i).second; j++)
        {
            size_t lastChecksum = checksum;
            checksum += multiplier * compressedFileSystem.at(i).first;
            multiplier++;
        }
    }
    return std::to_string(checksum);
}