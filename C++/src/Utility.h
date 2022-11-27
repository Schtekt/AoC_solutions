#pragma once
#include <string>
#include <vector>
struct InputDate
{
    const char* year;
    const char* day;
};

class AoCUtilityTool
{
public:
    AoCUtilityTool(const char* configPath);
    AoCUtilityTool() = delete;
    ~AoCUtilityTool() = default;

    void InitDay(InputDate date);

private:
    bool getInput(InputDate date, const char* path);
    std::string m_cookieSession;
};

class AoCDaySolution
{
public:
    AoCDaySolution(AoCUtilityTool& utility, InputDate&& date);

    virtual void PartOne() = 0;

    virtual void PartTwo() = 0;

    void Solve();
protected:
    std::vector<std::string> m_input;
    std::string m_resultPartOne;
    std::string m_resultPartTwo;
    InputDate m_date;
private:
    void printResult();
    void readData();

    AoCUtilityTool& m_utility;
};