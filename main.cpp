#include <iostream>
#include <fstream>
#include <functional>
#include <array>
#include <string>
#include "InputParser.h"

#include "Day1.h"
#include "Day2.h"

using Solution = std::function<void(std::istream&, std::ostream&)>;

int main(int argc, const char* argv[])
{
    std::array<Solution, 50> solutions = {
        solveDay1Part1,
        solveDay1Part2,
        solveDay2Part1,
        solveDay2Part2
    };

    InputParser runEnv(argc, argv);

    int day = std::stoi(std::string(runEnv.getCmdOptionOrDefaultVal("-d", "2")));
    int part = std::stoi(std::string(runEnv.getCmdOptionOrDefaultVal("-p", "2")));
    auto file = runEnv.getCmdOptionOrDefaultVal("-f", "inputs\\day2-input.txt");
    std::ifstream inFile {file.data()};

    int solutionId = 2 * (day - 1) + (part - 1);
    solutions[solutionId](inFile, std::cout);
}
