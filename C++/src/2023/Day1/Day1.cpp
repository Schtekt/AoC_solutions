#include "Day1.h"

AoCSolution_2023_1::AoCSolution_2023_1(AoCUtilityTool& tool)
: AoCDaySolution(tool, {"2023", "1"})
{

}

std::string AoCSolution_2023_1::PartOne()
{
    size_t sum = 0;
    for(auto line : m_input)
    {
        uint16_t first = 0;
        uint16_t last = 0;
        for(auto character : line)
        {
            if(std::isdigit(character))
            {
                if(first == 0)
                {
                    first = character - '0';
                    last = first;
                }
                else
                {
                    last = character - '0';
                }
            }
        }

        sum += first * 10 + last;
    }

    return std::to_string(sum);
}

std::string AoCSolution_2023_1::PartTwo()
{
    std::vector<std::tuple<std::string, uint16_t>> possibleMatches = 
    {
        std::make_tuple<std::string, uint16_t>("one", 1),
        std::make_tuple<std::string, uint16_t>("two", 2),
        std::make_tuple<std::string, uint16_t>("three", 3),
        std::make_tuple<std::string, uint16_t>("four", 4),
        std::make_tuple<std::string, uint16_t>("five", 5),
        std::make_tuple<std::string, uint16_t>("six", 6),
        std::make_tuple<std::string, uint16_t>("seven", 7),
        std::make_tuple<std::string, uint16_t>("eight", 8),
        std::make_tuple<std::string, uint16_t>("nine", 9),
        std::make_tuple<std::string, uint16_t>("1", 1),
        std::make_tuple<std::string, uint16_t>("2", 2),
        std::make_tuple<std::string, uint16_t>("3", 3),
        std::make_tuple<std::string, uint16_t>("4", 4),
        std::make_tuple<std::string, uint16_t>("5", 5),
        std::make_tuple<std::string, uint16_t>("6", 6),
        std::make_tuple<std::string, uint16_t>("7", 7),
        std::make_tuple<std::string, uint16_t>("8", 8),
        std::make_tuple<std::string, uint16_t>("9", 9)
    };

    size_t sum = 0;

    for(auto line : m_input)
    {
        size_t firstPos = -1;
        size_t lastPos = -1;
        uint16_t firstNumber = 0;
        uint16_t lastNumber = 0;
        for(auto matcher : possibleMatches)
        {
            auto pos_first = line.find(std::get<0>(matcher));
            auto pos_last = line.rfind(std::get<0>(matcher));

            if(pos_first == static_cast<size_t>(-1))
            {
                continue;
            }
            
            if(firstPos == static_cast<size_t>(-1) || pos_first < firstPos)
            {
                firstNumber = std::get<1>(matcher);
                firstPos = pos_first;
            }

            if(lastPos == static_cast<size_t>(-1) || pos_last > lastPos)
            {
                lastNumber = std::get<1>(matcher);
                lastPos = pos_last;
            }
        }
        
        sum += firstNumber * 10 + lastNumber;
    }

    return std::to_string(sum);
}