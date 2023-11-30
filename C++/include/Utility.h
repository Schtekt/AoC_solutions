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

    virtual std::string PartOne() = 0;

    virtual std::string PartTwo() = 0;

    void Solve();
protected:
    std::vector<std::string> m_input;
    InputDate m_date;
private:
    void printResult();
    void readData();

    AoCUtilityTool& m_utility;
};