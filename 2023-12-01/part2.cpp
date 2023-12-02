/*
    Task (Part2):

    Your calculation isn't quite right. It looks like some of the digits are actually spelled out with letters: one, two, three, four, five, six, seven, eight, and nine also count as valid "digits".

    Equipped with this new information, you now need to find the real first and last digit on each line. For example:

    two1nine
    eightwothree
    abcone2threexyz
    xtwone3four
    4nineeightseven2
    zoneight234
    7pqrstsixteen
    In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76. Adding these together produces 281.

    What is the sum of all of the calibration values?

    Result (Part2): 55358
*/

#include "part2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <map>

void resultPart2()
{

    std::map<std::string, int> stringNumbersMap = {
        {"1", 1},
        {"2", 2},
        {"3", 3},
        {"4", 4},
        {"5", 5},
        {"6", 6},
        {"7", 7},
        {"8", 8},
        {"9", 9},
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}};

    std::ifstream inputFile("input.txt");
    std::string line;

    int result = 0;

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }

    while (std::getline(inputFile, line))
    {

        std::map<std::string, int> firstOccurrenceMap;
        std::map<std::string, int> lastOccurrenceMap;

        for (const auto &number : stringNumbersMap)
        {
            // extract numbers(integers or string number) from line
            size_t firstOccurrence = line.find(number.first);
            size_t lastOccurrence = line.rfind(number.first);

            // read from left to right
            if (firstOccurrence != std::string::npos)
            {
                firstOccurrenceMap[number.first] = firstOccurrence;
            }

            // read from right to left
            if (lastOccurrence != std::string::npos)
            {
                lastOccurrenceMap[number.first] = lastOccurrence;
            }
        }

        std::map<std::string, int> firstOccurenceValue;
        std::map<std::string, int> lastOccurenceValue;

        // get first by min value
        for (const auto &pair : firstOccurrenceMap)
        {
            if (firstOccurenceValue.empty())
            {
                firstOccurenceValue.insert(pair);
            }
            else if (pair.second < firstOccurenceValue.begin()->second)
            {
                auto it = firstOccurenceValue.begin();
                firstOccurenceValue.erase(it);
                firstOccurenceValue.insert(pair);
            }
        }

        // get last by min value
        for (const auto &pair : lastOccurrenceMap)
        {
            if (lastOccurenceValue.empty())
            {
                lastOccurenceValue.insert(pair);
            }
            else if (pair.second > lastOccurenceValue.begin()->second)
            {
                auto it = lastOccurenceValue.begin();
                lastOccurenceValue.erase(it);
                lastOccurenceValue.insert(pair);
            }
        }

        std::string firstKey = firstOccurenceValue.begin()->first;
        std::string lastKey = lastOccurenceValue.begin()->first;

        int first = stringNumbersMap[firstKey];
        int last = stringNumbersMap[lastKey];

        // concat strings and convert to int
        int concatInt = std::stoi(std::to_string(first) + std::to_string(last));

        // acc to the result
        result += concatInt;
    }

    std::cout << "Result (part 2): " << result << std::endl;
}