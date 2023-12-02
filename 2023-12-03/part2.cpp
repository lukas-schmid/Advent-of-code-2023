/*
    Task (Part2):

    The missing part wasn't the only issue - one of the gears in the engine is wrong. A gear is any * symbol that is adjacent to exactly two part numbers. Its gear ratio is the result of multiplying those two numbers together.

    This time, you need to find the gear ratio of every gear and add them all up so that the engineer can figure out which gear needs to be replaced.

    Consider the same engine schematic again:

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
    In this schematic, there are two gears. The first is in the top left; it has part numbers 467 and 35, so its gear ratio is 16345. The second gear is in the lower right; its gear ratio is 451490. (The * adjacent to 617 is not a gear because it is only adjacent to one part number.) Adding up all of the gear ratios produces 467835.

    What is the sum of all of the gear ratios in your engine schematic?

    Result (Part2): 91031374
*/

#include "part2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cctype>
#include <unordered_set>

void resultPart2()
{
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    int sum = 0;
    std::string line;
    int lineIndex = 0;

    std::vector<std::vector<char>> grid;

    // store file as 2d vector
    do
    {
        grid.push_back(std::vector<char>(line.begin(), line.end()));
        lineIndex++;
    } while (getline(inputFile, line));

    inputFile.close();

    // lambda
    auto checkAdjacentNumber = [&](int r, int c, std::unordered_set<std::string> &numbers)
    {
        if (r >= 0 && r < grid.size() && c >= 0 && c < grid[r].size() &&
            std::isdigit(grid[r][c]))
        {
            std::string currentNumber;

            // Check left column for adjacent digits
            int leftCol = c;
            while (leftCol >= 0 && std::isdigit(grid[r][leftCol]))
            {
                currentNumber = grid[r][leftCol] + currentNumber;
                leftCol--;
            }

            // Check right column for adjacent digits
            int rightCol = c + 1;
            while (rightCol < grid[r].size() && std::isdigit(grid[r][rightCol]))
            {
                currentNumber = currentNumber + grid[r][rightCol];
                rightCol++;
            }

            // Insert the number as a string into the set
            numbers.insert(currentNumber);
        }
    };

    // loop over grid
    for (size_t row = 0; row < grid.size(); ++row)
    {
        for (size_t col = 0; col < grid[row].size(); ++col)
        {
            // find the gear
            if (grid[row][col] == '*')
            {
                std::unordered_set<std::string> uniqueNumbers;

                checkAdjacentNumber(row - 1, col, uniqueNumbers);     // top
                checkAdjacentNumber(row - 1, col + 1, uniqueNumbers); // top right
                checkAdjacentNumber(row, col + 1, uniqueNumbers);     // right
                checkAdjacentNumber(row + 1, col + 1, uniqueNumbers); // right bottom
                checkAdjacentNumber(row + 1, col, uniqueNumbers);     // bottom
                checkAdjacentNumber(row + 1, col - 1, uniqueNumbers); // bottom left
                checkAdjacentNumber(row, col - 1, uniqueNumbers);     // left
                checkAdjacentNumber(row - 1, col - 1, uniqueNumbers); // top left

                if (uniqueNumbers.size() == 2)
                {
                    int product = 1;
                    for (const auto &number : uniqueNumbers)
                    {
                        product *= std::stoi(number);
                    }
                    sum += product;
                }
            }
        }
    }

    std::cout << "Result (part 2): " << sum << std::endl;
}