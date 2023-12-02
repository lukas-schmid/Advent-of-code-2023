/*
    Task (Part1):

    The engine schematic (your puzzle input) consists of a visual representation of the engine. There are lots of numbers and symbols you don't really understand, but apparently any number adjacent to a symbol, even diagonally, is a "part number" and should be included in your sum. (Periods (.) do not count as a symbol.)

    Here is an example engine schematic:

    467..114..
    ...*......
    ..35..633.
    ......#...
    617*......
    .....+.58.
    ..592.....
    ......755.
    ...$.*....
    .664.598..
    In this schematic, two numbers are not part numbers because they are not adjacent to a symbol: 114 (top right) and 58 (middle right). Every other number is adjacent to a symbol and so is a part number; their sum is 4361.

    Of course, the actual engine schematic is much larger. What is the sum of all of the part numbers in the engine schematic?

    Result (Part1): 546563
*/

#include "part1.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

/*
    Function to extract number with their starting index
    Updates foundIntegers and foundIntegerIndices by reference.
*/
void findNumbersInString(const std::string &line, std::vector<int> &foundIntegers, std::vector<int> &foundIntegerIndices)
{
    size_t pos = 0;

    while ((pos = line.find_first_of("01234567489", pos)) != std::string::npos)
    {
        foundIntegers.push_back(std::stoi(line.substr(pos)));
        foundIntegerIndices.push_back(static_cast<int>(pos));
        pos = line.find_first_not_of("0123456789", pos + 1);
    }
}

/*
    Function to extract symbols (excluding dot(.)) with their starting index
    Updates foundSymbol and foundSymbolIndice by reference.
*/
void findSymbols(const std::string &line, std::vector<char> &foundSymbols, std::vector<int> &foundSymbolIndices)
{
    size_t pos = 0;

    while ((pos = line.find_first_not_of("01234567489.", pos)) != std::string::npos)
    {
        foundSymbols.push_back(line[pos]);
        foundSymbolIndices.push_back(static_cast<int>(pos));
        pos = line.find_first_not_of("0123456789.", pos + 1);
    }
}

/*
    Function to extract number with that have a symbol as adjecant.
    Updates matchinIntegers by reference.
*/
void findIntegersWithAdjacentSymbol(std::vector<int> &foundIntegers,
                                    std::vector<int> &foundIntegerIndices,
                                    std::vector<char> &foundSymbols,
                                    std::vector<int> &foundSymbolIndices,
                                    std::vector<int> &matchingIntegers)
{
    for (size_t i = 0; i < foundIntegers.size(); i++)
    {
        int startIndex = foundIntegerIndices[i];
        int endIndex = startIndex + std::to_string(foundIntegers[i]).length() - 1;

        // lambda condition to get adjecant by indexes
        auto symbolIsAdjacent = [startIndex, endIndex](int number)
        {
            return (number >= startIndex - 1 && number <= endIndex + 1);
        };

        auto result = std::find_if(foundSymbolIndices.begin(), foundSymbolIndices.end(), symbolIsAdjacent);

        if (result != foundSymbolIndices.end())
        {
            matchingIntegers.push_back(foundIntegers[i]);
        }
    }
}

void resultPart1()
{
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
    }

    std::vector<std::string> lines;
    std::string line;
    std::vector<int> matchingIntegers;
    int sum = 0;

    // Store lines in vector to access previous and next lines
    while (getline(inputFile, line))
    {
        lines.push_back(line);
    }

    inputFile.close();

    // iterate over each line
    for (size_t i = 0; i < lines.size(); i++)
    {

        size_t currentIndex = i;
        std::string previousLine;
        std::string currentLine;
        std::string nextLine;

        // previous line
        if (currentIndex > 0)
        {
            previousLine = lines[currentIndex - 1];
        }

        // current line
        currentLine = lines[i];

        // next line
        if (currentIndex < lines.size() - 1)
        {
            nextLine = lines[currentIndex + 1];
        }

        std::vector<int> foundIntegers;
        std::vector<int> foundIntegerIndices;
        std::vector<char> foundSymbols;
        std::vector<int> foundSymbolIndices;

        findNumbersInString(currentLine, foundIntegers, foundIntegerIndices);
        findSymbols(previousLine, foundSymbols, foundSymbolIndices);
        findSymbols(currentLine, foundSymbols, foundSymbolIndices);
        findSymbols(nextLine, foundSymbols, foundSymbolIndices);

        findIntegersWithAdjacentSymbol(foundIntegers, foundIntegerIndices, foundSymbols, foundSymbolIndices, matchingIntegers);
    }

    // Sum all integers with adjacent symbol
    for (size_t i = 0; i < matchingIntegers.size(); i++)
    {
        sum += matchingIntegers[i];
    }

    std::cout << "Result (part 1): " << sum << std::endl;
}