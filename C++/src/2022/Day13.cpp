#include "Day13.h"
#include <sstream>

enum class CompareResult
{
    Correct,
    Incorrect,
    Continue
};

struct wrapped_list {
    list val;

    bool operator==(const wrapped_list& other) const
    {
        return val == other.val;
    }

    CompareResult compare(const wrapped_list & other)
    {
        unsigned int* uintPtr = std::get_if<unsigned int>(&val);
        std::vector<wrapped_list>* wlPtr = std::get_if<std::vector<wrapped_list>>(&val);

        if(uintPtr)
        {
            auto otherPtr = std::get_if<unsigned int>(&other.val);
            if(otherPtr)
            {
                if(*uintPtr < *otherPtr)
                {
                    return CompareResult::Correct;
                }
                else if(*uintPtr > *otherPtr)
                {
                    return CompareResult::Incorrect;
                }
                else
                {
                    return CompareResult::Continue;
                }
            }
            else
            {
                auto otherPtrList = std::get_if<std::vector<wrapped_list>>(&other.val);
                if(otherPtrList)
                {
                    wrapped_list tmpLeft{wrapped_list{std::vector<wrapped_list>{wrapped_list{*uintPtr}}}};
                    return tmpLeft.compare(other);
                }
                else 
                {
                    return CompareResult::Incorrect;
                }
            }
        }
        else if(wlPtr)
        {
            auto otherPtr = std::get_if<std::vector<wrapped_list>>(&other.val);
            if(otherPtr)
            {
                for(unsigned int i = 0; i < wlPtr->size(); i++)
                {
                    // Right list has run out of items
                    if(i >= otherPtr->size())
                    {
                        return CompareResult::Incorrect;
                    }
                    CompareResult res = wlPtr->at(i).compare(otherPtr->at(i));
                    
                    if(res != CompareResult::Continue)
                    {
                        // Comparison has made a decision. Return it.
                        return res;
                    }
                }

                // Left list has run out of items.
                if(wlPtr->size() == otherPtr->size())
                    return CompareResult::Continue;
                else
                    return CompareResult::Correct;
            }
            else
            {
                auto otherPtrVal = std::get_if<unsigned int>(&other.val);
                if(otherPtrVal)
                {
                    wrapped_list tmpRight{std::vector<wrapped_list>{wrapped_list{*otherPtrVal}}};
                    return compare(tmpRight);
                }
                else
                {
                    return CompareResult::Incorrect;
                }
            }
        }
        else
        {
            return CompareResult::Incorrect;
        }
    }

    std::vector<wrapped_list> parseLine(std::stringstream& ss)
    {
        std::vector<wrapped_list> lst;
        unsigned int val;
        char trash;
        ss >> trash; // Should be "["

        while(true)
        {
            if(ss.peek() == ',')
            {
                ss.ignore();
            }
            else if(ss.peek() == ']')
            {
                ss >> trash;
                break;
            }
            else if(ss.peek() == '[')
            {
                lst.emplace_back(wrapped_list{parseLine(ss)});
            }
            else if(ss >> val)
            {
                lst.emplace_back(wrapped_list{val});
            }
            else
            {
                throw "ERROR!";
                break;
            }
        }

        return lst;
    }

    std::string printMe()
    {
        std::string printOut = "";
        unsigned int* uintPtr = std::get_if<unsigned int>(&val);
        std::vector<wrapped_list>* wlPtr = std::get_if<std::vector<wrapped_list>>(&val);
        if (uintPtr)
        {
            printOut += std::to_string(*uintPtr);
        }
        else if (wlPtr)
        {
            printOut += "[";
            for(auto wl = wlPtr->begin(); wl != wlPtr->end(); wl++)
            {
                printOut += (*wl).printMe();
                if(wl + 1 != wlPtr->end())
                {
                    printOut += ", ";
                }
            }
            printOut += "]";
        }

        return printOut;
    }
};

AoCSolution_2022_13::AoCSolution_2022_13(AoCUtilityTool& tool) : AoCDaySolution(tool, {"2022", "13"})
{
}

std::string AoCSolution_2022_13::PartOne()
{
    std::vector<wrapped_list> list;
    for(auto line : m_input)
    {
        if(line.size() != 0)
        {
            std::stringstream ss(line);
            wrapped_list entry;
            entry.val = entry.parseLine(ss);
            list.emplace_back(entry);
        }

    }

    unsigned int sum = 0;
    unsigned int count = 1;
    for(unsigned int i = 0; i < list.size(); i+=2)
    {
        sum += list[i].compare(list[i+1]) == CompareResult::Correct ? count : 0;
        count++;
    }
	return std::to_string(sum);
}

std::string AoCSolution_2022_13::PartTwo()
{
    std::vector<wrapped_list> list;
    for(auto line : m_input)
    {
        if(line.size() != 0)
        {
            std::stringstream ss(line);
            wrapped_list entry;
            entry.val = entry.parseLine(ss);
            list.emplace_back(entry);
        }

    }
    std::stringstream ssTwo("[[2]]");
    wrapped_list two;
    two.val = two.parseLine(ssTwo);

    std::stringstream ssSix("[[6]]");
    wrapped_list six;
    six.val = six.parseLine(ssSix);

    list.emplace_back(two);
    list.emplace_back(six);

    std::vector<wrapped_list> sortedList;

    for(auto left : list)
    {
        bool placed = false;
        for(auto right = sortedList.begin(); right < sortedList.end(); right++)
        {
            if(left.compare(*right) == CompareResult::Correct)
            {
                sortedList.insert(right, left);
                placed = true;
                break;
            }
        }
        if(!placed)
            sortedList.emplace_back(left);
    }

    unsigned int twoPos = 1 + std::distance(sortedList.begin(), std::find(sortedList.begin(), sortedList.end(), two));
    unsigned int sixPos = 1 + std::distance(sortedList.begin(), std::find(sortedList.begin(), sortedList.end(), six));
    return std::to_string(twoPos * sixPos);
}