#include "Day11.h"

#include <cstdint>
#include <string>
#include <ranges>
#include "StringUtils.h"

namespace {
	int64_t getNumRocks(std::unordered_map<int64_t, int64_t> rockCounts, int blinks) {
		for (int i = 0; i < blinks; ++i) {
			std::unordered_map<int64_t, int64_t> temp;
			for (auto [rock, count] : rockCounts) {
				if (rock == 0) {
					temp[1] += count;
				}
				else {
					auto rockStr = std::to_string(rock);
					if (rockStr.size() % 2 == 0) {
						size_t half = rockStr.size() / 2;
						int64_t l = std::stoll(rockStr.substr(0, half));
						int64_t r = std::stoll(rockStr.substr(half, half));
						temp[l] += count;
						temp[r] += count;
					}
					else {
						temp[rock * 2024] += count;
					}
				}
			}
			rockCounts = std::move(temp);
		}
		int64_t numRocks = 0;
		for (int64_t count : std::views::values(rockCounts)) {
			numRocks += count;
		}
		return numRocks;
	}
}

void solveDay11Part1(std::istream& input, std::ostream& output) {
	std::string line;
	getline(input, line);
	auto rocks = split<int64_t>(line, " ", stollFunc);
	std::unordered_map<int64_t, int64_t> rockCounts;
	for (int64_t rock : rocks) {
		++rockCounts[rock];
	}
	output << getNumRocks(rockCounts, 25);
}

void solveDay11Part2(std::istream& input, std::ostream& output) {
	std::string line;
	getline(input, line);
	auto rocks = split<int64_t>(line, " ", stollFunc);
	std::unordered_map<int64_t, int64_t> rockCounts;
	for (int64_t rock : rocks) {
		++rockCounts[rock];
	}
	output << getNumRocks(rockCounts, 75);
}