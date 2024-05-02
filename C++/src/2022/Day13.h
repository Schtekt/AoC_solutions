#pragma once
#include "Utility.h"
#include <iostream>
#include <variant>

class AoCSolution_2022_13 : public AoCDaySolution
{
public:
	AoCSolution_2022_13();
	std::string PartOne();

	std::string PartTwo();
private:
};

struct wrapped_list;
using list = std::variant<unsigned int, std::vector<wrapped_list>>;
