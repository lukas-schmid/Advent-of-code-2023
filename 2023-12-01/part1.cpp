/*
    Task (Part1):

    The newly-improved calibration document consists of lines of text; each line originally contained a specific calibration value that the Elves now need to recover. On each line, the calibration value can be found by combining the first digit and the last digit (in that order) to form a single two-digit number.

    For example:

    1abc2
    pqr3stu8vwx
    a1b2c3d4e5f
    treb7uchet
    In this example, the calibration values of these four lines are 12, 38, 15, and 77. Adding these together produces 142.

    Consider your entire calibration document. What is the sum of all of the calibration values?

    Result (Part1): 56042
*/

#include "part1.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <map>

void resultPart1()
{
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }

    std::string line;
    int result = 0;
    while (std::getline(inputFile, line))
    {
        char firstCharDigit = '0';
        char lastCharDigit = '0';
        int lineInt;

        std::reverse(line.begin(), line.end());

        for (char c : line)
        {
            if (isdigit(c))
            {

                if (lastCharDigit == '0')
                {
                    lastCharDigit = c;
                }
                else
                {
                    firstCharDigit = c;
                }
            }
            if (firstCharDigit == '0')
            {
                firstCharDigit = lastCharDigit;
            }
        }

        lineInt = stoi(std::string(1, firstCharDigit) + lastCharDigit);

        result += lineInt;
        std::reverse(line.begin(), line.end());
    }

    inputFile.close();

    std::cout << "Result (part 1): " << result << std::endl;
}