/*
    Task (Part1):

    As you walk, the Elf shows you a small bag and some cubes which are either red, green, or blue. Each time you play this game, he will hide a secret number of cubes of each color in the bag, and your goal is to figure out information about the number of cubes.

    To get information, once a bag has been loaded with cubes, the Elf will reach into the bag, grab a handful of random cubes, show them to you, and then put them back in the bag. He'll do this a few times per game.

    You play several games and record the information from each game (your puzzle input). Each game is listed with its ID number (like the 11 in Game 11: ...) followed by a semicolon-separated list of subsets of cubes that were revealed from the bag (like 3 red, 5 green, 4 blue).

    For example, the record of a few games might look like this:

    Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
    Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
    Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
    Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
    Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
    In game 1, three sets of cubes are revealed from the bag (and then put back again). The first set is 3 blue cubes and 4 red cubes; the second set is 1 red cube, 2 green cubes, and 6 blue cubes; the third set is only 2 green cubes.

    The Elf would first like to know which games would have been possible if the bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?

    In the example above, games 1, 2, and 5 would have been possible if the bag had been loaded with that configuration. However, game 3 would have been impossible because at one point the Elf showed you 20 red cubes at once; similarly, game 4 would also have been impossible because the Elf showed you 15 blue cubes at once. If you add up the IDs of the games that would have been possible, you get 8.

    Determine which games would have been possible if the bag had been loaded with only 12 red cubes, 13 green cubes, and 14 blue cubes. What is the sum of the IDs of those games?

    Result (Part1): 2683
*/

#include "part1.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <numeric>

std::vector<int> extractNumbersByCubeColor(std::string str, std::regex pattern)
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

    return numbers;
}

void validateNotPossible(std::vector<int> &cubes, int max, bool &isPossible)
{
    for (int number : cubes)
    {
        if (number > max)
        {
            isPossible = false;
            return;
        }
    }
}

void resultPart1()
{
    int maxRed = 12;
    int maxGreen = 13;
    int maxBlue = 14;
    std::vector<int> gameIds;
    int sum = 0;

    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        bool isPossible = true; // initially for each line
        std::regex patternGameId("Game (\\d+):");
        std::regex patternRed("(\\d+) red");
        std::regex patternGreen("(\\d+) green");
        std::regex patternBlue("(\\d+) blue");

        int gameId;
        std::smatch match;

        if (std::regex_search(line, match, patternGameId))
        {
            gameId = std::stoi(match[1]);
        }

        std::vector<int> numbersRed = extractNumbersByCubeColor(line, patternRed);
        std::vector<int> numbersGreen = extractNumbersByCubeColor(line, patternGreen);
        std::vector<int> numbersBlue = extractNumbersByCubeColor(line, patternBlue);

        validateNotPossible(numbersRed, maxRed, isPossible);
        validateNotPossible(numbersGreen, maxGreen, isPossible);
        validateNotPossible(numbersBlue, maxBlue, isPossible);

        if (isPossible == true)
        {
            gameIds.push_back(gameId);
        }
    }

    sum = std::accumulate(gameIds.begin(), gameIds.end(), 0);
    std::cout << "Result (part 1): " << sum << std::endl;
}