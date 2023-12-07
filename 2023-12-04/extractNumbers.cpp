#include "extractNumbers.h"

void extractNumbersByRange(const std::string &line, size_t startIndex, size_t endIndex, std::vector<int> &numbers)
{
    std::regex pattern("(\\d+)");
    std::sregex_iterator iter(line.begin() + startIndex, line.begin() + endIndex, pattern);
    std::sregex_iterator end;

    while (iter != end)
    {
        numbers.push_back(std::stoi(iter->str()));
        ++iter;
    }
}