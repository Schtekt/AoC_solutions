#pragma once
#include "Utility.h"
#include <string>
#include <sstream>
#include <iostream>

struct Monkey
{
    std::vector<long long> items;
    long long opValue = 0;
    bool useOldOpValue = false;
    bool mult = false;
    long long inspectionCount = 0;

    long long testDivisible = 1;
    long long firstThrow;
    long long secondThrow;

    void monkeyRound(std::vector<Monkey>& monkeys)
    {
        for(auto& item : items)
        {
            inspectionCount++;
            if(useOldOpValue)
            {
                opValue = item;
            }

            if(mult)
            {
                item *= opValue;
            }
            else
            {
                item += opValue;
            }

            item /= 3;

            if(item % testDivisible == 0)
            {
                monkeys[firstThrow].items.push_back(item);
            }
            else
            {
                monkeys[secondThrow].items.push_back(item);
            }
        }

        items.clear();
    }

    void monkeyRoundPanic(std::vector<Monkey>& monkeys, long long reducer)
    {
        for(auto& item : items)
        {
            inspectionCount++;
            long long old = item;
            if(useOldOpValue)
            {
                opValue = item;
            }

            if(mult)
            {
                item *= opValue;
            }
            else
            {
                item += opValue;
            }

            item %= reducer;

            if(item % testDivisible == 0)
            {
                monkeys[firstThrow].items.push_back(item);
            }
            else
            {
                monkeys[secondThrow].items.push_back(item);
            }
        }

        items.clear();
    }
};

class AoCSolution_2022_11 : public AoCDaySolution
{
public:
    AoCSolution_2022_11(AoCUtilityTool &tool);
    std::string PartOne();

    std::string PartTwo();

private:
};

AoCSolution_2022_11::AoCSolution_2022_11(AoCUtilityTool &tool) : AoCDaySolution(tool, {"2022", "11"})
{

}

void ReadInput(const std::vector<std::string>& input, std::vector<Monkey>& monkeys)
{
    std::string trash;
    long long vals;
    char op;
    std::string opVal;
    long long divBy;
    long long firstChoice;
    long long secondChoice;

    for(long long i = 0; i < input.size(); i += 7)
    {
        Monkey monkey;
        std::stringstream itemsStream(input[i + 1]);

        itemsStream >> trash;
        itemsStream >> trash;

        while(itemsStream >> vals)
        {
            monkey.items.push_back(vals);
            itemsStream >> trash;
        }

        std::stringstream opStream(input[i + 2]);

        opStream >> trash;
        opStream >> trash;
        opStream >> trash;
        opStream >> trash;

        opStream >> op;
        opStream >> opVal;

        if(op == '*')
        {
            monkey.mult = true;
        }

        if(opVal == "old")
        {
            monkey.useOldOpValue = true;
        }
        else
        {
            monkey.opValue = std::atoi(opVal.c_str());
        }

        std::stringstream divStream(input[i + 3]);

        divStream >> trash;
        divStream >> trash;
        divStream >> trash;
        divStream >> divBy;

        monkey.testDivisible = divBy;

        std::stringstream firstChoiceStream(input[i+4]);
        firstChoiceStream >> trash;
        firstChoiceStream >> trash;
        firstChoiceStream >> trash;
        firstChoiceStream >> trash;
        firstChoiceStream >> trash;

        firstChoiceStream >> firstChoice;

        std::stringstream secondChoiceStream(input[i+5]);
        secondChoiceStream >> trash;
        secondChoiceStream >> trash;
        secondChoiceStream >> trash;
        secondChoiceStream >> trash;
        secondChoiceStream >> trash;

        secondChoiceStream >> secondChoice;

        monkey.firstThrow = firstChoice;
        monkey.secondThrow = secondChoice;

        monkeys.push_back(monkey);
    }
}

std::string AoCSolution_2022_11::PartOne()
{
    std::vector<Monkey> monkeys;
    ReadInput(m_input, monkeys);
    long long reducer = 1;
    for(auto& monkey : monkeys)
    {
        reducer *= monkey.testDivisible;
    }
    for(int i = 0; i < 20; i++)
    {
        for(auto& monkey : monkeys)
        {
            monkey.monkeyRound(monkeys);
        }
    }

    long long highest = 0;
    long long secondHighest = 0;

    for(auto& monkey : monkeys)
    {
        if(monkey.inspectionCount > highest)
        {
            secondHighest = highest;
            highest = monkey.inspectionCount;
        }
        else if(monkey.inspectionCount > secondHighest)
        {
            secondHighest = monkey.inspectionCount;
        }
    }
    return std::to_string(highest * secondHighest);
}

std::string AoCSolution_2022_11::PartTwo()
{
    std::vector<Monkey> monkeys;
    ReadInput(m_input, monkeys);
    long long reducer = 1;
    for(auto& monkey : monkeys)
    {
        reducer *= monkey.testDivisible;
    }
    for(int i = 0; i < 10000; i++)
    {
        for(auto& monkey : monkeys)
        {
            monkey.monkeyRoundPanic(monkeys, reducer);
        }
    }

    long long highest = 0;
    long long secondHighest = 0;

    for(auto& monkey : monkeys)
    {
        if(monkey.inspectionCount > highest)
        {
            secondHighest = highest;
            highest = monkey.inspectionCount;
        }
        else if(monkey.inspectionCount > secondHighest)
        {
            secondHighest = monkey.inspectionCount;
        }
    }
    return std::to_string(highest * secondHighest);
}