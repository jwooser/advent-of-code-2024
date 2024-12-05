#include <iostream>
#include <fstream>
#include <functional>
#include <array>
#include <string>
#include "InputParser.h"

#include "Day1.h"

using Solution = std::function<void(std::istream&, std::ostream&)>;

int main(int argc, const char* argv[])
{
    std::array<Solution, 50> solutions = {
        solveDay1Part1,
        solveDay1Part2,
    };

    InputParser runEnv(argc, argv);

    int day = std::stoi(std::string(runEnv.getCmdOptionOrDefaultVal("-d", "1")));
    int part = std::stoi(std::string(runEnv.getCmdOptionOrDefaultVal("-p", "1")));
    auto file = runEnv.getCmdOptionOrDefaultVal("-f", "inputs\\day1-input.txt");
    std::ifstream inFile {file.data()};

    int solutionId = 2 * (day - 1) + (part - 1);
    solutions[solutionId](inFile, std::cout);
}
