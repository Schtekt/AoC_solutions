#include "Utility.h"

#define CURL_STATICLIB
#include <curl\curl.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

size_t callbackFunc(char* ptr, size_t size, size_t nmemb, const char* path)
{
    std::ofstream ofs(path);
    ofs << ptr;
    ofs.close();
    return nmemb * size;
}

AoCUtilityTool::AoCUtilityTool(const char* configPath)
{
    std::ifstream ifs(configPath);
    std::stringstream buff;
    buff << ifs.rdbuf();
    m_cookieSession = buff.str();
}

bool AoCUtilityTool::getInput(InputDate date, const char* path)
{
    CURL* curl;
    CURLcode res;
    bool func_res = false;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl)
    {
        std::string inputUrl = "https://adventofcode.com/";
        inputUrl.append(date.year);
        inputUrl.append("/day/");
        inputUrl.append(date.day);
        inputUrl.append("/input");

        std::string cookieString = "session=";
        cookieString.append(m_cookieSession);

        //inputUrl = "https://adventofcode.com/2021/day/1/input";

        curl_easy_setopt(curl, CURLOPT_URL, inputUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_COOKIE, cookieString.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackFunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, path);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        }
        else
        {
            func_res = true;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return func_res;
}

void AoCUtilityTool::InitDay(InputDate date)

{
    std::string path = "Resources/";

    path.append(date.year);
    if (!std::filesystem::is_directory(path))
    {
        std::filesystem::create_directory(path);
    }
    path.append("/day_");
    path.append(date.day);
    if (!std::filesystem::is_directory(path))
    {
        std::filesystem::create_directory(path);
    }
    path.append("/input.txt");
    if (!std::filesystem::is_regular_file(path))
    {
        // create file
        std::ofstream ofs(path.c_str());
        ofs.close();

        if (!getInput(date, path.c_str()))
        {
            // Somehow, the request has failed, delete the file!
            std::filesystem::remove(path);
        }
    }
}

AoCDaySolution::AoCDaySolution(AoCUtilityTool& utility, InputDate&& date): m_utility(utility), m_date(date), m_resultPartOne(""), m_resultPartTwo("")
{
    m_utility.InitDay(m_date);
}

void AoCDaySolution::Solve()
{
    readData();
    PartOne();
    PartTwo();
    printResult();
}

void AoCDaySolution::printResult()
{
    std::cout << "===============================" << m_date.year << " " << m_date.day << "===============================\nPart1:\n" << m_resultPartOne << "\nPart2:\n" << m_resultPartTwo << "\n" << "====================================================================\n";
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
