#pragma once
#include <string>
#include <vector>
struct InputDate
{
    const char* year;
    const char* day;
};

class AoCDaySolution
{
public:
    AoCDaySolution(InputDate&& date);

    virtual std::string PartOne() = 0;

    virtual std::string PartTwo() = 0;

    void Solve();
protected:
    std::vector<std::string> m_input;
    InputDate m_date;
private:
    void printResult();
    void readData();
};