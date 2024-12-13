#include "Day13.h"
#include <sstream>
#include <regex>

AoCSolution_2024_13::AoCSolution_2024_13():
AoCDaySolution({"2024", "13"})
{}

struct Equation
{
    long long int res; // C
    long long int a_mult; // a
    long long int b_mult; // b
};

std::pair<long long int, long long int> solve(const std::pair<Equation, Equation>& system)
{
    long long int A = 0;
    long long int B = 0;

    long long int divider = system.first.a_mult * system.second.b_mult - system.second.a_mult * system.first.b_mult;

    if(divider != 0)
    {
        A = system.second.b_mult * system.first.res - system.first.b_mult * system.second.res;
        A /= divider;

        B = system.first.a_mult * system.second.res - system.second.a_mult * system.first.res;
        B /= divider;
    }

    return std::make_pair(A, B);
}

std::string AoCSolution_2024_13::PartOne()
{
    size_t tokens = 0;

    for(size_t i = 0; i < m_input.size(); i += 4)
    {
        Equation first;
        Equation second;

        std::stringstream ssA{m_input.at(i)};
        std::stringstream ssB{m_input.at(i + 1)};
        std::stringstream ssRes{m_input.at(i + 2)};

        ssA.seekg(12);
        ssA >> first.a_mult;
        ssA.ignore(std::numeric_limits<std::streamsize>::max(), '+');
        ssA >> second.a_mult;

        ssB.seekg(12);
        ssB >> first.b_mult;
        ssB.ignore(std::numeric_limits<std::streamsize>::max(), '+');
        ssB >> second.b_mult;

        ssRes.seekg(9);
        ssRes >> first.res;
        ssRes.ignore(std::numeric_limits<std::streamsize>::max(), '=');
        ssRes >> second.res;

        auto solution = solve(std::make_pair(first, second));

        if(solution.first * first.a_mult + solution.second * first.b_mult == first.res &&
            solution.first * second.a_mult + solution.second * second.b_mult == second.res)
        {
            tokens += 3 * solution.first + solution.second;
        }
    }
    return std::to_string(tokens);
}

std::string AoCSolution_2024_13::PartTwo()
{
    size_t tokens = 0;

    for(size_t i = 0; i < m_input.size(); i += 4)
    {
        Equation first;
        Equation second;

        std::stringstream ssA{m_input.at(i)};
        std::stringstream ssB{m_input.at(i + 1)};
        std::stringstream ssRes{m_input.at(i + 2)};

        ssA.seekg(12);
        ssA >> first.a_mult;
        ssA.ignore(std::numeric_limits<std::streamsize>::max(), '+');
        ssA >> second.a_mult;

        ssB.seekg(12);
        ssB >> first.b_mult;
        ssB.ignore(std::numeric_limits<std::streamsize>::max(), '+');
        ssB >> second.b_mult;

        ssRes.seekg(9);
        ssRes >> first.res;
        ssRes.ignore(std::numeric_limits<std::streamsize>::max(), '=');
        ssRes >> second.res;

        first.res += 10000000000000;
        second.res += 10000000000000;
        auto solution = solve(std::make_pair(first, second));

        if(solution.first * first.a_mult + solution.second * first.b_mult == first.res &&
            solution.first * second.a_mult + solution.second * second.b_mult == second.res)
        {
            tokens += 3 * solution.first + solution.second;
        }
    }
    return std::to_string(tokens);
}