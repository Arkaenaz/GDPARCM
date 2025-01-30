#pragma once

#include <string>
#include <vector>

class StringUtility
{
public:
	static std::vector<std::string> split(const std::string& s, char delimiter);
};