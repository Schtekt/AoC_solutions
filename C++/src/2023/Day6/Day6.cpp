#include "Day6.h"

#include <sstream>

AoCSolution_2023_6::AoCSolution_2023_6()
: AoCDaySolution{{"2023", "6"}}
{

}

struct Race
{
    size_t time;
    size_t recordDistance;
};

size_t calcDistance(size_t timeHeldMs, size_t raceTimeMs)
{
    return timeHeldMs * (raceTimeMs - timeHeldMs);
}

std::string AoCSolution_2023_6::PartOne()
{
    std::stringstream ssTimes{m_input[0].substr(m_input[0].find(':') + 1)};
    std::stringstream ssDistances{m_input[1].substr(m_input[1].find(':') + 1)};

    std::vector<Race> races;
    Race race;
    while(ssTimes >> race.time)
    {
        ssDistances >> race.recordDistance;
        races.emplace_back(race);
    }

    size_t sum{1};
    for(auto [raceTime, recordDistance] : races)
    {
        size_t numWaysToBeat{0};
        for(size_t i{0}; i < raceTime; i++)
        {
            if(calcDistance(i, raceTime) > recordDistance)
            {
                numWaysToBeat++;
            }
        }
        sum *= numWaysToBeat;
    }
    
    return std::to_string(sum);
}

std::string removeSpaces(const std::string & str)
{
    std::stringstream ss{str};
    char character;
    std::string res;
    while(ss >> character)
    {
        res += character;
    }
    return res;
}

std::string AoCSolution_2023_6::PartTwo()
{
    Race race;
    std::stringstream ssTime{removeSpaces(m_input[0].substr(m_input[0].find(':') + 1))};
    std::stringstream ssDistance{removeSpaces(m_input[1].substr(m_input[1].find(':') + 1))};

    ssTime >> race.time;
    ssDistance >> race.recordDistance;

    // timeHeldMs * (raceTimeMs - timeHeldMs)
    // distance = timeHeldMs * raceTimeMs - timeHeldMs ^ 2
    // 0 = timeHeldMs * raceTimeMs - timeHeldMs ^ 2 - distance
    // timeHeldMs ^ 2 - raceTimeMs * timeHeldMs + distance = 0

    // timeHeldMs_1 = raceTimeMs / 2 + sqrt((raceTimeMs / 2)^2 - distance)
    // timeHeldMs_2 = raceTimeMs / 2 - sqrt((raceTimeMs / 2)^2 - distance)

    auto halfRaceTime = race.time / 2.0;
    auto timeHeldMs_1 = halfRaceTime + std::sqrt(std::pow(halfRaceTime, 2) - race.recordDistance);
    auto timeHeldMs_2 = halfRaceTime - std::sqrt(std::pow(halfRaceTime, 2) - race.recordDistance);
    return std::to_string(static_cast<size_t>(std::floor(timeHeldMs_1 - timeHeldMs_2)));
}