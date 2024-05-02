#include "Utility.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

AoCDaySolution::AoCDaySolution(InputDate&& date)
:
m_date(date)
{
}

void AoCDaySolution::Solve()
{
    readData();
    printResult();
}

void AoCDaySolution::printResult()
{
    std::cout << "===============================" << m_date.year << " " << m_date.day << "===============================\nPart1:\n" << PartOne() << "\nPart2:\n" << PartTwo() << "\n" << "====================================================================\n";
}

void AoCDaySolution::readData()
{
    std::string path = "Resources/";
    path.append(m_date.year);
    path.append("/day_");
    path.append(m_date.day);
    path.append("/input.txt");

    std::ifstream ifs(path);
    std::stringstream sstream;
    sstream << ifs.rdbuf();

    std::string line;

    while (std::getline(sstream, line, '\n'))
    {
        m_input.emplace_back(line);
    }
}
