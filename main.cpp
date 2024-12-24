#include <iostream>
#include <fstream>
#include <functional>
#include <array>
#include <string>
#include "CommandLineParser.h"

#include "Day1.h"
#include "Day2.h"
#include "Day3.h"
#include "Day4.h"
#include "Day5.h"
#include "Day6.h"
#include "Day7.h"
#include "Day8.h"
#include "Day9.h"
#include "Day10.h"
#include "Day11.h"
#include "Day12.h"
#include "Day13.h"

using Solution = std::function<void(std::istream&, std::ostream&)>;

int main(int argc, const char* argv[])
{
    std::array<Solution, 50> solutions = {
        // Day 1
        solveDay1Part1,
        solveDay1Part2,
        // Day 2
        solveDay2Part1,
        solveDay2Part2,
        // Day 3
        solveDay3Part1,
        solveDay3Part2,
        // Day 4
        solveDay4Part1,
        solveDay4Part2,
        // Day 5
        solveDay5Part1,
        solveDay5Part2,
        // Day 6
        solveDay6Part1,
        solveDay6Part2,
        // Day 7
        solveDay7Part1,
        solveDay7Part2,
        // Day 8
        solveDay8Part1,
        solveDay8Part2,
        // Day 9
        solveDay9Part1,
        solveDay9Part2,
        // Day 10
        solveDay10Part1,
        solveDay10Part2,
        // Day 11
        solveDay11Part1,
        solveDay11Part2,
        // Day 12
        solveDay12Part1,
        solveDay12Part2,
        // Day 12
        solveDay13Part1,
        solveDay13Part2,
    };

    CommandLineParser runEnv(argc, argv);

    int day = std::stoi(std::string(runEnv.getCmdOptionOrDefaultVal("-d", "13")));
    int part = std::stoi(std::string(runEnv.getCmdOptionOrDefaultVal("-p", "2")));
    auto file = runEnv.getCmdOptionOrDefaultVal("-f", "inputs\\day13-input.txt");
    std::ifstream inFile {file.data()};

    int solutionId = 2 * (day - 1) + (part - 1);
    solutions[solutionId](inFile, std::cout);
}
