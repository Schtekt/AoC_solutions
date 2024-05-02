#pragma once
#include "Utility.h"
#include <string>
#include <sstream>
#include <iostream>

class AoCSolution_2022_7 : public AoCDaySolution
{
public:
    AoCSolution_2022_7();
    std::string PartOne();

    std::string PartTwo();

private:
};

struct File
{
    size_t m_size;
    std::string m_name;
};

struct Dir
{
    std::string m_name;
    std::vector<Dir> m_dirs;
    std::vector<File> m_files;
    Dir* m_parent;
    size_t m_size;

    size_t findDir(std::string &name)
    {
        for (size_t i = 0; i < m_dirs.size(); i++)
        {
            if (m_dirs[i].m_name == name)
            {
                return i;
            }
        }
        return -1;
    }

    size_t findFile(std::string &name)
    {
        for (size_t i = 0; i < m_files.size(); i++)
        {
            if (m_files[i].m_name == name)
            {
                return i;
            }
        }
        return -1;
    }

    size_t sumUp()
    {
        size_t totSum = 0;
        for (auto dir : m_dirs)
        {
            size_t dirSum = dir.sumUp();

            totSum += dirSum;
        }
        for (auto file : m_files)
        {
            totSum += file.m_size;
        }
        m_size = totSum;
        return totSum;
    }

    void GetAllDirs(std::vector<Dir> &list)
    {
        for (auto dir : m_dirs)
        {
            list.push_back(dir);
            dir.GetAllDirs(list);
        }
    }
};

std::unique_ptr<Dir> ParseInput(std::vector<std::string> &commands)
{
    Dir* current = nullptr;
    std::unique_ptr<Dir> first;

    for (auto line : commands)
    {
        std::string cmd;
        std::stringstream ss(line);

        ss >> cmd;

        if (cmd == "$")
        {
            ss >> cmd;

            if (cmd == "cd")
            {
                ss >> cmd;

                if (cmd != "..")
                {
                    if (current)
                    {
                        size_t dirPos = current->findDir(cmd);
                        if (dirPos != size_t(-1))
                        {
                            current = &current->m_dirs[dirPos];
                        }
                        else
                        {
                            // create new dir, should not happen...
                            Dir dir;
                            ss >> dir.m_name;
                            dir.m_parent = current;
                            current->m_dirs.push_back(dir);
                        }
                    }
                    else
                    {
                        // create first dir
                        first = std::make_unique<Dir>();
                        first->m_name = "/";
                        current = first.get();
                    }
                }
                else
                {
                    current = current->m_parent;
                }
            }
            else if (cmd == "ls")
            {
                // ignore
            }
        }
        else if (cmd == "dir")
        {
            size_t dirPos = current->findDir(cmd);
            if (dirPos != size_t(-1))
            {
                current = &current->m_dirs[dirPos];
            }
            else
            {
                // create new dir
                Dir dir;
                ss >> dir.m_name;
                dir.m_parent = current;
                current->m_dirs.push_back(dir);
            }
        }
        else
        {
            std::string name;
            ss >> name;

            if (current->findFile(name) == size_t(-1))
            {
                File f;
                f.m_size = std::stoi(cmd);
                f.m_name = name;
                current->m_files.push_back(f);
            }
            else
            {
                // Found file already exists in the directory, this should not occur!
                return nullptr;
            }
        }
    }

    return first;
}

AoCSolution_2022_7::AoCSolution_2022_7() : AoCDaySolution({"2022", "7"})
{
}

std::string AoCSolution_2022_7::PartOne()
{

    std::unique_ptr<Dir> root = ParseInput(m_input);
    std::vector<Dir> dirsList;
    root->GetAllDirs(dirsList);
    size_t sum = 0;

    for (auto dir : dirsList)
    {
        size_t dirSum = dir.sumUp();

        if (dirSum < 100000)
        {
            sum += dirSum;
        }
    }
    return std::to_string(sum);
}

std::string AoCSolution_2022_7::PartTwo()
{
    std::unique_ptr<Dir> root = ParseInput(m_input);
    std::vector<Dir> dirsList;
    root->GetAllDirs(dirsList);
    size_t toRemove = 30000000 - (70000000 - root->sumUp());
    size_t smallest = 0;

    for (auto dir : dirsList)
    {
        size_t dirSum = dir.sumUp();

        if (dirSum > toRemove && (dirSum < smallest || smallest == 0))
        {
            smallest = dirSum;
        }
    }
    return std::to_string(smallest);
}