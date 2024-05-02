#include "Day3.h"
#include <sstream>
AoCSolution_2023_3::AoCSolution_2023_3()
: AoCDaySolution({"2023", "3"})
{

}

struct SchematicNumber
{
    std::string number{""};
    size_t horizontalPosition{0};
};

struct SchematicSymbol
{
    char symbol{' '};
    size_t horizontalPosition{0};
};

std::vector<SchematicNumber> findAllPossiblePartNumbers(std::string_view line)
{
    std::vector<SchematicNumber> foundNumbers;
    constexpr std::string_view matches{"0123456789"};

    std::string substr{line};
    auto startOfNum{substr.find_first_of(matches)};
    size_t horizontalCount{0};
    while(startOfNum != std::string::npos)
    {
        size_t endOfNum{substr.find_first_not_of(matches, startOfNum)};
        if(endOfNum == std::string::npos)
        {
            endOfNum = substr.size();
        }

        SchematicNumber possibleNum;
        possibleNum.number = substr.substr(startOfNum, endOfNum - startOfNum);
        possibleNum.horizontalPosition = startOfNum + horizontalCount;

        foundNumbers.emplace_back(possibleNum);
        substr = substr.substr(endOfNum, substr.size() - endOfNum);
        horizontalCount += endOfNum;

        startOfNum = substr.find_first_of(matches);
    }

    return foundNumbers;
}

std::vector<SchematicSymbol> findAllSchematicSymbols(std::string_view line)
{
    std::vector<SchematicSymbol> foundSymbols;
    constexpr std::string_view nonMatches{"0123456789."};
    std::string substr{line};
    auto startOfSym{substr.find_first_not_of(nonMatches)};
    size_t horizontalCount{0};

    while(startOfSym != std::string::npos)
    {
        SchematicSymbol sym;
        sym.symbol = substr[startOfSym];
        sym.horizontalPosition = horizontalCount + startOfSym;
        foundSymbols.emplace_back(sym);

        horizontalCount += startOfSym + 1;

        substr = substr.substr(startOfSym + 1, substr.size() - startOfSym);
        startOfSym = substr.find_first_not_of(nonMatches);
    }

    return foundSymbols;
}

std::vector<SchematicSymbol> findAllCogs(std::string_view line)
{
    std::vector<SchematicSymbol> foundSymbols;
    constexpr std::string_view matches{"*"};
    std::string substr{line};
    auto startOfSym{substr.find_first_of(matches)};
    size_t horizontalCount{0};

    while(startOfSym != std::string::npos)
    {
        SchematicSymbol sym;
        sym.symbol = substr[startOfSym];
        sym.horizontalPosition = horizontalCount + startOfSym;
        foundSymbols.emplace_back(sym);

        horizontalCount += startOfSym + 1;

        substr = substr.substr(startOfSym + 1, substr.size() - startOfSym);
        startOfSym = substr.find_first_of(matches);
    }

    return foundSymbols;
}

std::string AoCSolution_2023_3::PartOne()
{
    // Numbers that are adjacent to a symbol (other than '.') needs to be summed up.
    // If a symbol is directly diagonal to a number, that number is counted e.g.
    
    // --- Example ---
    // 467...
    // ...*..
    // --- End ---
    
    // 467 in the example above is adjacent to the symbol '*'.

    std::vector<std::vector<SchematicNumber>> nums;
    std::vector<std::vector<SchematicSymbol>> syms;
    for(auto line : m_input)
    {
        nums.emplace_back(findAllPossiblePartNumbers(line));
        syms.emplace_back(findAllSchematicSymbols(line));
    }

    std::vector<int> partNumbers;

    for(size_t i{0}; i < nums.size(); i++)
    {
        for(auto& [numStr, numPos] : nums[i])
        {
            bool isAllowed{false};
            size_t minPosAllowed = numPos - 1 == static_cast<size_t>(-1) ? 0 : numPos - 1;
            if(i != 0)
            {
                // Check symbols above...
                for(auto& [sym, symPos] : syms[i - 1])
                {
                    if(symPos >= minPosAllowed
                    && symPos <= numPos + numStr.length())
                    {
                        partNumbers.emplace_back(std::stoi(numStr));
                        isAllowed = true;
                        break;
                    }
                }
                if(isAllowed)
                {
                    continue;
                }
            }

            if(i != nums.size() - 1)
            {
                // Check symbols below...
                for(auto& [sym, symPos] : syms[i + 1])
                {
                    if(symPos >= minPosAllowed
                    && symPos <= numPos + numStr.length())
                    {
                        partNumbers.emplace_back(std::stoi(numStr));
                        isAllowed = true;
                        break;
                    }
                }
                if(isAllowed)
                {
                    continue;
                }
            }

            // Check symbols left and right...
            for(auto& [sym, symPos] : syms[i])
            {
                if(symPos == minPosAllowed
                || symPos == numPos + numStr.length())
                {
                    partNumbers.emplace_back(std::stoi(numStr));
                    isAllowed = true;
                    break;
                }
            }
            if(isAllowed)
            {
                continue;
            }
        }
    }

    size_t sum{0};
    for(auto num : partNumbers)
    {
        sum += num;
    }
    return std::to_string(sum);
}

std::string AoCSolution_2023_3::PartTwo()
{
    std::vector<std::vector<SchematicNumber>> nums;
    std::vector<std::vector<SchematicSymbol>> syms;
    for(auto line : m_input)
    {
        nums.emplace_back(findAllPossiblePartNumbers(line));
        syms.emplace_back(findAllCogs(line));
    }

    size_t sum{0};

    for(size_t i{0}; i < syms.size(); i++)
    {
        for(auto [sym, symPos] : syms[i])
        {
            std::vector<int> adjacentNums;

            if(i != 0)
            {
                // check above
                for(auto [numStr, numPos] : nums[i - 1])
                {
                    if(numPos <= symPos + 1
                      && numPos + numStr.length() >= symPos)
                    {
                        adjacentNums.emplace_back(std::stoi(numStr));
                    }
                }
            }

            if(i != syms.size() - 1)
            {
                // check below
                for(auto [numStr, numPos] : nums[i + 1])
                {
                    if(numPos <= symPos + 1
                      && numPos + numStr.length() >= symPos)
                    {
                        adjacentNums.emplace_back(std::stoi(numStr));
                    }
                }
            }

            // check left and right
            for(auto [numStr, numPos] : nums[i])
            {
                if(numPos == symPos + 1
                  || numPos + numStr.length() == symPos)
                  {
                    adjacentNums.emplace_back(std::stoi(numStr));
                  }
            }

            if(adjacentNums.size() == 2)
            {
                sum += adjacentNums[0] * adjacentNums[1];
            }
        }
    }
    return std::to_string(sum);
}