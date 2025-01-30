#include "pch.h"
#include "StringUtility.h"

std::vector<std::string> StringUtility::split(const std::string& s, char delimiter)
{
       std::stringstream ss(s);
       std::string item;
       std::vector<std::string> tokens;
       while (std::getline(ss, item, delimiter))
       {
           tokens.push_back(item);
       }

       return tokens;
}