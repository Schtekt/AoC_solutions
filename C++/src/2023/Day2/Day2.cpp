#include "Day2.h"
#include <sstream>

AoCSolution_2023_2::AoCSolution_2023_2(AoCUtilityTool& tool)
: AoCDaySolution(tool, {"2023", "2"})
{

}

struct SetInfo
{
    size_t nrOfRed{0};
    size_t nrOfGreen{0};
    size_t nrOfBlue{0};
};

struct GameInfo
{
    size_t id{0};
    std::vector<SetInfo> sets;
};

SetInfo extractSetInfo(const std::string& setInfo)
{
    // Example set info
    // 1 red, 2 blue, 3 green OR 3 green 2 blue OR 1 blue
    // Assumption: No set is empty

    std::stringstream ss{setInfo};

    SetInfo inf;

    size_t nr{0};
    std::string color;

    while(!ss.eof())
    {
        ss >> nr;
        ss >> color;

        if(color.find("red") != std::string::npos)
        {
            inf.nrOfRed = nr;
        }
        else if(color.find("green") != std::string::npos)
        {
            inf.nrOfGreen = nr;
        }
        else if(color.find("blue") != std::string::npos)
        {
            inf.nrOfBlue = nr;
        }
    }
    return inf;
}

GameInfo extractGameInfo(const std::string& gameLine)
{
    std::stringstream ss{gameLine};

    std::string word;
    char character;
    
    size_t id;

    ss >> word; // Read "Game"
    ss >> id; // Read ID
    ss >> character; // Read ":"

    GameInfo info;
    info.id = id;

    // split the rest of the string into three sets, divided by the two semicolons
    // set1; set2; set3\n

    std::string setString{""};
    bool mayReadMore{true};
    do
    {
        std::getline(ss, setString, ';');
        mayReadMore = !ss.eof();
        setString.erase(setString.begin()); // Erase the initial space " 3 blue, 4 red" -> "3 blue, 4 red"
        info.sets.push_back(extractSetInfo(setString)); // Extract and save set info
    }
    while(mayReadMore);
    return info;
}

std::string AoCSolution_2023_2::PartOne()
{
    // Input:
    // Game #: set1; set2; set3; ...\n
    // where # is the game ID
    // where setx is replaced by a set of cubes, e.g. 3 blue, 4 red OR 1 red 2 green, 6 blue OR 2 green

    constexpr size_t maxRed{12};
    constexpr size_t maxGreen{13};
    constexpr size_t maxBlue{14};

    size_t idSums{0};
    // for each game, extract three sets of games, as well as the game ID.
    for(auto line : m_input)
    {
        GameInfo game{extractGameInfo(line)};

        // Determine if the game is legal. which it only is if each set has a max of 12 red, 13 green and 14 blue.

        bool gameIsLegal{true};
        for(auto currSet : game.sets)
        {
            gameIsLegal &= currSet.nrOfRed <= maxRed && currSet.nrOfGreen <= maxGreen && currSet.nrOfBlue <= maxBlue;

            if(!gameIsLegal)
            {
                break;
            }
        }

        if(gameIsLegal)
        {
            idSums += game.id;
        }
    }
    return std::to_string(idSums);
}

std::string AoCSolution_2023_2::PartTwo()
{
    // Determine the fewest number of cubes (for each color) in each game
    // Multiply the minimum number if cubes (e.g. 1 red, 2 blue, 3 green = 1*2*3 = 6) and sum up the power of each game

    size_t sum = 0;
    for(auto line : m_input)
    {
        GameInfo game{extractGameInfo(line)};

        size_t minRed = 0;
        size_t minGreen = 0;
        size_t minBlue = 0;

        for(auto& set : game.sets)
        {
            if(minRed < set.nrOfRed)
            {
                minRed = set.nrOfRed;
            }

            if(minGreen < set.nrOfGreen)
            {
                minGreen = set.nrOfGreen;
            }
            if(minBlue < set.nrOfBlue)
            {
                minBlue = set.nrOfBlue;
            }
        }

        sum += minRed * minGreen * minBlue;
    }
    return std::to_string(sum);
}