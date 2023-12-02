/*
    Task (Part2):

    consider the example games from earlier:

    Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
    Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
    Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
    Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
    Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

    In game 1, the game could have been played with as few as 4 red, 2 green, and 6 blue cubes. If any color had even one fewer cube, the game would have been impossible.
    Game 2 could have been played with a minimum of 1 red, 3 green, and 4 blue cubes.
    Game 3 must have been played with at least 20 red, 13 green, and 6 blue cubes.
    Game 4 required at least 14 red, 3 green, and 15 blue cubes.
    Game 5 needed no fewer than 6 red, 3 green, and 2 blue cubes in the bag.
    The power of a set of cubes is equal to the numbers of red, green, and blue cubes multiplied together. The power of the minimum set of cubes in game 1 is 48. In games 2-5 it was 12, 1560, 630, and 36, respectively. Adding up these five powers produces the sum 2286.

    For each game, find the minimum set of cubes that must have been present. What is the sum of the power of these sets?

    Result (Part2): 49710
*/

#include "part2.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <numeric>

int extractHighestNumbersByCubeColor(std::string str, std::regex pattern)
{
    std::vector<int> numbers;
    std::sregex_iterator iter(str.begin(), str.end(), pattern);
    std::sregex_iterator end;

    while (iter != end)
    {
        std::smatch match = *iter;
        std::string strMatch = match.str();

        std::regex patternNum("(\\d+)");
        std::string numberString;

        if (std::regex_search(strMatch, match, patternNum))
        {
            numberString = match[1];
        }

        numbers.push_back(std::stoi(numberString));
        ++iter;
    }

    auto maxElementIterator = std::max_element(numbers.begin(), numbers.end());
    int maxValue = *maxElementIterator;

    return maxValue;
}

void resultPart2()
{
    int maxRed = 12;
    int maxGreen = 13;
    int maxBlue = 14;
    int sum = 0;

    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        int powerOfSet;
        std::regex patternRed("(\\d+) red");
        std::regex patternGreen("(\\d+) green");
        std::regex patternBlue("(\\d+) blue");

        int maxNumberRed = extractHighestNumbersByCubeColor(line, patternRed);
        int maxNumberGreen = extractHighestNumbersByCubeColor(line, patternGreen);
        int maxNumberBlue = extractHighestNumbersByCubeColor(line, patternBlue);

        powerOfSet = maxNumberRed * maxNumberGreen * maxNumberBlue;
        sum += powerOfSet;
    }

    std::cout << "Result (part 2): " << sum << std::endl;
}