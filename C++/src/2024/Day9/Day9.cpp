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

std::vector<std::pair<uint8_t, uint8_t>> createDiskMap(std::string input)
{
    char fileSize = 0;
    char freeSize = 0;

    std::vector<std::pair<uint8_t, uint8_t>> diskMap;

    // Assumed the input is only one string
    std::stringstream ss{input};

    while(ss >> fileSize)
    {
        if(!(ss >> freeSize))
        {
            freeSize = '0';
        }

        diskMap.emplace_back(std::make_pair(fileSize - '0', freeSize - '0'));
    }

    return diskMap;
}

size_t calculateChecksum(std::vector<std::pair<size_t, uint8_t>> fileSystem)
{
    size_t checksum = 0;
    size_t multiplier = 0;
    for(size_t i = 0; i < fileSystem.size(); i++)
    {
        for(size_t j = 0; j < fileSystem.at(i).second; j++)
        {
            checksum += multiplier * fileSystem.at(i).first;
            multiplier++;
        }
    }
    return checksum;
}

std::string AoCSolution_2024_9::PartOne()
{
    auto diskMap = createDiskMap(m_input.at(0));

    size_t backIndex = diskMap.size() - 1;
    uint8_t internalIndex = 0;
    std::vector<std::pair<size_t, uint8_t>> compressedFileSystem;
    for(size_t i = 0; i < diskMap.size(); i++)
    {
        if(backIndex == i)
        {
            compressedFileSystem.emplace_back(std::make_pair(i, diskMap.at(i).first - internalIndex));
            break;
        }
        else if (backIndex < i)
        {
            break;
        }

        compressedFileSystem.emplace_back(std::make_pair(i, diskMap.at(i).first));

        // Fill in from back of diskMap
        uint8_t filled = 0;
        while(filled < diskMap.at(i).second)
        {
            uint8_t toFillFromCurrentBackIndex = std::min(diskMap.at(backIndex).first - internalIndex, diskMap.at(i).second - filled);
            compressedFileSystem.emplace_back(std::make_pair(backIndex, toFillFromCurrentBackIndex));
            internalIndex += toFillFromCurrentBackIndex;
            filled += toFillFromCurrentBackIndex;
            if(internalIndex == diskMap.at(backIndex).first)
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

    return std::to_string(calculateChecksum(compressedFileSystem));
}

std::string AoCSolution_2024_9::PartTwo()
{
    auto diskMap = createDiskMap(m_input.at(0));

    std::vector<size_t> placedIndices;
    std::vector<size_t> freeIndices;

    for(size_t i = 0; i < diskMap.size(); i++)
    {
        freeIndices.emplace_back(i);
    }

    size_t frontIndex = 0;
    std::vector<std::pair<size_t, uint8_t>> compressedFileSystem1;
    while(freeIndices.size() > 0)
    {
        if(std::find(placedIndices.begin(), placedIndices.end(), frontIndex) == placedIndices.end())
        {
            compressedFileSystem1.emplace_back(std::make_pair(frontIndex, diskMap.at(frontIndex).first));
            placedIndices.emplace_back(frontIndex);
            freeIndices.erase(std::find(freeIndices.begin(), freeIndices.end(), frontIndex));
        }
        else
        {
            compressedFileSystem1.emplace_back(std::make_pair(0, diskMap.at(frontIndex).first));
        }

        if(freeIndices.size() == 0)
        {
            break;
        }

        size_t freeIndicesIndex = freeIndices.size() - 1;
        uint8_t currentFilledSpace = 0;
        uint8_t spaceToFill = diskMap.at(frontIndex).second;

        while(freeIndicesIndex >= 0 && currentFilledSpace < spaceToFill)
        {
            size_t freeIndex = freeIndices.at(freeIndicesIndex);
            if(diskMap.at(freeIndex).first <= spaceToFill - currentFilledSpace)
            {
                compressedFileSystem1.emplace_back(freeIndex, diskMap.at(freeIndex).first);
                currentFilledSpace += diskMap.at(freeIndex).first;
                placedIndices.emplace_back(freeIndex);
                freeIndices.erase(freeIndices.begin() + freeIndicesIndex);
            }
            if(freeIndicesIndex == 0)
            {
                break;
            }
            freeIndicesIndex--;
        }

        if(currentFilledSpace < spaceToFill)
        {
            compressedFileSystem1.emplace_back(0, spaceToFill - currentFilledSpace);
        }

        frontIndex++;
    }

    return std::to_string(calculateChecksum(compressedFileSystem1));
}