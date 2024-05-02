#include "Day4.h"
#include <sstream>

AoCSolution_2023_4::AoCSolution_2023_4()
: AoCDaySolution({"2023", "4"})
{

}

struct ScratchTicket
{
    std::vector<int> winningNumbers;
    std::vector<int> myNumbers;
};

std::vector<int> parseAllNumbersFromString(const std::string& str)
{
    std::stringstream ss{str};
    std::vector<int> numbers;
    int parsedNum{0};
    while(ss >> parsedNum)
    {
        numbers.emplace_back(parsedNum);
    }
    return numbers;
}

ScratchTicket parseTicket(const std::string& line)
{
    ScratchTicket ticket;

    //        "Winning numbers"     "My numbers"
    // Card x: # # # # # # # # ... | # # # # # # # ...

    auto startOfWinningNumbers = line.find(':');
    auto startOfMyNumbers = line.find('|');
        
    auto winningNumbersStr = line.substr(startOfWinningNumbers + 1, startOfMyNumbers - startOfWinningNumbers - 1);
    auto myNumbersStr = line.substr(startOfMyNumbers + 1);

    ticket.winningNumbers = parseAllNumbersFromString(winningNumbersStr);
    ticket.myNumbers = parseAllNumbersFromString(myNumbersStr);

    return ticket;
}

std::string AoCSolution_2023_4::PartOne()
{
    size_t sum{0};
    for(auto line : m_input)
    {
        auto ticket = parseTicket(line);

        size_t nrOfMatches{0};
        for(auto winningNum : ticket.winningNumbers)
        {
            for(auto myNumber : ticket.myNumbers)
            {
                if(winningNum == myNumber)
                {
                    nrOfMatches += 1;
                    break;
                }
            }
        }
        // 1 match -> 1 = 2 ^ 0
        // 2 match -> 2 = 2 ^ 1
        // 3 match -> 4 = 2 ^ 2
        if(nrOfMatches > 0)
        {
            sum += static_cast<size_t>(pow(2, nrOfMatches - 1));
        }
    }
    return std::to_string(sum);
}

std::string AoCSolution_2023_4::PartTwo()
{
    std::vector<size_t> scratchCards;
    size_t currentIndex{0};

    for(auto line : m_input)
    {
        // In case we reach a scratchcard which we have no copies of, add its original.
        if(scratchCards.size() <= currentIndex)
        {
            scratchCards.emplace_back(1);
        }

        auto ticket = parseTicket(line);

        size_t nrOfMatches{0};

        for(auto winningNum : ticket.winningNumbers)
        {
            for(auto myNumber : ticket.myNumbers)
            {
                if(winningNum == myNumber)
                {
                    nrOfMatches += 1;
                    break;
                }
            }
        }

        for(int i{1}; i < nrOfMatches + 1; i++)
        {
            // In case we reach a scratchcard which we have no copies of, add its original.
            if(scratchCards.size() <= currentIndex + i)
            {
                scratchCards.emplace_back(1);
            }

            // For each copy held of this scratchcard (scratchCards[currentIndex]), we will gain one copy of the following card (scratchCards[currentIndex + i]).
            scratchCards[currentIndex + i] += scratchCards[currentIndex];
        }
        currentIndex++;
    }

    size_t sum{0};
    for(auto nrOfCards : scratchCards)
    {
        sum += nrOfCards;
    }

    return std::to_string(sum);
}