#pragma once
#include "Utility.h"
#include <iostream>
#include <sstream>
#include <algorithm>
class AoCSolution_2022_15 : public AoCDaySolution
{
public:
    AoCSolution_2022_15(AoCUtilityTool &tool);
    std::string PartOne();

    std::string PartTwo();

private:
};

AoCSolution_2022_15::AoCSolution_2022_15(AoCUtilityTool &tool) : AoCDaySolution(tool, {"2022", "15"})
{
}

struct Pos
{
    long long x;
    long long y;
};

struct Sensor
{
    Pos s;
    Pos b;
    unsigned long long dist;
};

void ReadInput(std::vector<Sensor> &sensors, std::vector<std::string> &input)
{
    for (auto line : input)
    {
        Sensor sensor{{0, 0}, {0, 0}, 0};
        sscanf_s(line.c_str(), "Sensor at x=%lld, y=%lld: closest beacon is at x=%lld, y=%lld", &sensor.s.x, &sensor.s.y, &sensor.b.x, &sensor.b.y);
        sensor.dist = abs(sensor.s.x - sensor.b.x) + abs(sensor.s.y - sensor.b.y);
        sensors.push_back(sensor);
    }
}

std::string AoCSolution_2022_15::PartOne()
{
    std::vector<Sensor> sensors;

    ReadInput(sensors, m_input);

    const long long y = 2000000;

    std::vector<std::pair<long long, long long>> sensorIntervals;

    for(auto sensor : sensors)
    {
        const auto delta_col = sensor.dist - std::abs(sensor.s.y - y);

        sensorIntervals.push_back({sensor.s.x - delta_col, sensor.s.x + delta_col});
    }

    std::sort(sensorIntervals.begin(), sensorIntervals.end());
    auto startInterval = sensorIntervals[0];
    sensorIntervals.erase(sensorIntervals.begin());

    std::vector<std::pair<long long, long long>> combinedIntervals;
    for(auto interval : sensorIntervals)
    {
        if(startInterval.first <= interval.first && startInterval.second >= interval.second)
        {
            continue;
        }
        else if(startInterval.second >= interval.first && startInterval.second <= interval.second)
        {
            startInterval.second = interval.second;
        }
        else
        {
            combinedIntervals.push_back(startInterval);
            startInterval = interval;
        }
    }

    unsigned long long sum = 0;

    if(combinedIntervals.size() == 0)
    {
        sum += startInterval.second - startInterval.first;
    }
    else
    {
        for(auto interval : combinedIntervals)
        {
            sum += interval.second - interval.first;
        }
    }
    return std::to_string(sum);
}

struct Interval
{
    long long min;
    long long max;
};

std::string AoCSolution_2022_15::PartTwo()
{
    std::vector<Sensor> sensors;

    ReadInput(sensors, m_input);

    const long long size = 4000000;

    for(unsigned long long y = 0; y < size; y++)
    {
        std::vector<std::pair<long long, long long>> sensorIntervals;

        for(auto sensor : sensors)
        {
            const long long delta_col = sensor.dist - std::abs(sensor.s.y - static_cast<long long>(y));
            if(delta_col < 0)
                continue;

            std::pair<long long, long long> interval = std::make_pair(
                std::max(sensor.s.x - delta_col, 0ll),
                std::min(sensor.s.x + delta_col, size));
            sensorIntervals.push_back(interval);
        }

        std::sort(sensorIntervals.begin(), sensorIntervals.end());
        auto startInterval = sensorIntervals[0];
        sensorIntervals.erase(sensorIntervals.begin());

        for(auto interval : sensorIntervals)
        {
            if(startInterval.first <= interval.first && startInterval.second >= interval.second)
                continue;
            else if(startInterval.second >= interval.first && startInterval.second <= interval.second)
                startInterval.second = interval.second;
            else
                return std::to_string((startInterval.second + 1) * size + y);
        }

    }

    return "-1";
}