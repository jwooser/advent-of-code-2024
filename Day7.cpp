#include "Day7.h"

#include <cstdint>
#include <vector>
#include <string>
#include "StringUtils.h"

namespace {
	bool solutionExists(int64_t testVal, 
						const std::vector<int64_t>& operands, 
						int64_t val = 0, 
						size_t i = 0) {
		if (i == operands.size()) {
			return testVal == val;
		}
		if (val > testVal) {
			return false;
		}
		if (i == 0) {
			return solutionExists(testVal, operands, operands[0], 1);
		}
		return solutionExists(testVal, operands, val * operands[i], i + 1) ||
			   solutionExists(testVal, operands, val + operands[i], i + 1);
	}

	bool solutionExistsWithConcat(int64_t testVal,
							      const std::vector<int64_t>& operands,
							      int64_t val = 0,
							      size_t i = 0) {
		if (i == operands.size()) {
			return testVal == val;
		}
		if (val > testVal) {
			return false;
		}
		if (i == 0) {
			return solutionExistsWithConcat(testVal, operands, operands[0], 1);
		}
		bool result = solutionExistsWithConcat(testVal, operands, val * operands[i], i + 1) ||
					  solutionExistsWithConcat(testVal, operands, val + operands[i], i + 1);
		if (!result) {
			int64_t concat{};
			if (tryConcat(val, operands[i], concat)) {
				result |= solutionExistsWithConcat(testVal, operands, concat, i + 1);
			}
		}
		return result;
	}
}

void solveDay7Part1(std::istream& input, std::ostream& output) {
	std::string line;
	int64_t sum = 0;
	while (getline(input, line)) {
		auto eq = split(line, ": ");
		int64_t testVal = std::stoll(eq[0]);
		std::vector<int64_t> operands = split<int64_t>(eq[1], " ", stollFunc);
		if (solutionExists(testVal, operands)) {
			sum += testVal;
		}
	}
	output << sum;
}

void solveDay7Part2(std::istream& input, std::ostream& output) {
	std::string line;
	int64_t sum = 0;
	while (getline(input, line)) {
		auto eq = split(line, ": ");
		int64_t testVal = std::stoll(eq[0]);
		std::vector<int64_t> operands = split<int64_t>(eq[1], " ", stollFunc);
		if (solutionExistsWithConcat(testVal, operands)) {
			sum += testVal;
		}
	}
	output << sum;
}