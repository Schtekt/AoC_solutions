#include "Day7.h"
#include <cinttypes>
#include <sstream>

AoCSolution_2024_7::AoCSolution_2024_7():
AoCDaySolution({"2024", "7"})
{}

long long int evaluate(const std::vector<long long int>& numbers, uint32_t operators)
{
    long long int result = numbers[0];
    for(size_t i = 1; i < numbers.size(); i++)
    {
        if((0b01LL << (i - 1)) & operators)
        {
            result *= numbers[i];
        }
        else
        {
            result += numbers[i];
        }
    }
    return result;
}

std::string AoCSolution_2024_7::PartOne()
{
    long long int sum = 0;
    for(const auto& line : m_input)
    {
        std::istringstream ss{line};
        long long int testValue;
        std::vector<long long int> numbers;

        ss >> testValue;
        ss.ignore(1, ':');
        long long int number;
        while(ss >> number)
        {
            numbers.emplace_back(number);
        }

        if(numbers.size() == 0)
            bool hej = true;

        for(int i = 0; i < pow(2, numbers.size() - 1); i++)
        {
            if(evaluate(numbers, i) == testValue)
            {
                sum += testValue;
                break;
            }
        }
    }
    return std::to_string(sum);
}

std::vector<size_t> toBase3(uint64_t num, size_t length) {
    std::vector<size_t> base3(length, 0);
    for (int i = static_cast<int>(length - 1); i >= 0; --i) {
        base3[i] = num % 3;
        num /= 3;
    }
    return base3;
}

long long int evaluateWithConcat(const std::vector<long long int>& numbers, uint64_t operators)
{
    long long int result = numbers[0];

    auto base3Operators = toBase3(operators, numbers.size() - 1);
    for(size_t i = 1; i < numbers.size(); i++)
    {
        auto op = base3Operators[i-1];
        if(op == 0)
        {
            result += numbers[i];
        }
        else if(op == 1)
        {
            result *= numbers[i];
        }
        else
        {
            result = std::strtoll((std::to_string(result) + std::to_string(numbers[i])).c_str(), nullptr, 10);
        }
    }
    return result;
}

std::string AoCSolution_2024_7::PartTwo()
{
    long long int sum = 0;
    for(const auto& line : m_input)
    {
        std::istringstream ss{line};
        long long int testValue;
        std::vector<long long int> numbers;

        ss >> testValue;
        ss.ignore(1, ':');
        long long int number;
        while(ss >> number)
        {
            numbers.emplace_back(number);
        }

        if(numbers.size() == 0)
            bool hej = true;


        for(int i = 0; i < pow(3, numbers.size() - 1); i++)
        {
            if(evaluateWithConcat(numbers, i) == testValue)
            {
                sum += testValue;
                break;
            }
        }
    }
    return std::to_string(sum);
}