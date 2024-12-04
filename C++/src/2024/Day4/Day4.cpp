#include "Day4.h"
#include <regex>

AoCSolution_2024_4::AoCSolution_2024_4():
AoCDaySolution({"2024", "4"})
{}

bool verifyXmasGeneral(const std::string& searchWord, const std::vector<std::string>& letter, int startX, int startY, int incX, int incY)
{
    size_t maxIncMul = searchWord.size() - 1;
    if(startY - incY * maxIncMul < 0 || startY + incY * maxIncMul >= letter.size() || startY >= letter.size() ||
        startX - incX * maxIncMul < 0 || startX + incX * maxIncMul >= letter.at(startY).size() || startX >= letter.at(startY).size())
    {
        return false;
    }

    for(int i = 0; i < searchWord.size(); i++)
    {
        if(letter.at(startY + incY * i).at(startX + incX*i) != searchWord.at(i))
        {
            return false;
        }
    }

    return true;
}

std::string AoCSolution_2024_4::PartOne()
{
    const std::string searchWord = "XMAS";
    long long int sum = 0;
    for(int y = 0; y < m_input.size(); y++)
    {
        auto& line = m_input.at(y);
        for(int x = 0; x < line.length(); x++)
        {
            sum += verifyXmasGeneral(searchWord, m_input, x, y,  0, -1); // up
            sum += verifyXmasGeneral(searchWord, m_input, x, y,  0,  1); // down
            sum += verifyXmasGeneral(searchWord, m_input, x, y,  1,  0); // right
            sum += verifyXmasGeneral(searchWord, m_input, x, y, -1,  0); // left
            sum += verifyXmasGeneral(searchWord, m_input, x, y, -1, -1); // left, up
            sum += verifyXmasGeneral(searchWord, m_input, x, y,  1,  1); // right, down
            sum += verifyXmasGeneral(searchWord, m_input, x, y,  1, -1); // right, up
            sum += verifyXmasGeneral(searchWord, m_input, x, y, -1,  1); // left, down
        }
    }
    return std::to_string(sum);
}

bool verifyX_Mas(const std::vector<std::string>& letter, int startX, int startY)
{
    const std::string searchWord = "MAS";
    int count = 0;
    count += verifyXmasGeneral(searchWord, letter, startX + 1, startY + 1, -1, -1);
    count += verifyXmasGeneral(searchWord, letter, startX - 1, startY + 1,  1, -1);
    count += verifyXmasGeneral(searchWord, letter, startX + 1, startY - 1, -1,  1);
    count += verifyXmasGeneral(searchWord, letter, startX - 1, startY - 1,  1,  1);
    return count == 2;
}

std::string AoCSolution_2024_4::PartTwo()
{
    long long int sum = 0;
    for(int y = 0; y < m_input.size(); y++)
    {
        auto& line = m_input.at(y);
        for(int x = 0; x < line.length(); x++)
        {
            if(line.at(x) == 'A')
            {
                sum += verifyX_Mas(m_input, x, y);
            }
        }
    }
    return std::to_string(sum);
}