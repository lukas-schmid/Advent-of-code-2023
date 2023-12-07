#ifndef EXTRACT_NUMBERS_H
#define EXTRACT_NUMBERS_H

#include <vector>
#include <string>
#include <regex>

void extractNumbersByRange(const std::string &line, size_t startIndex, size_t endIndex, std::vector<int> &numbers);

#endif