#include "Day4.h"
#include <vector>
#include <string>
#include <array>
#include "Vector2.h"
#include "Grid.h"
#include "Directions.h"

void solveDay4Part1(std::istream& input, std::ostream& output) {
	auto grid = parseGrid(input);
	int matches = 0;
	std::array<char, 4> xmas = { 'X', 'M', 'A', 'S'};
	for (int i = 0; i < 8; ++i) {
		Direction8 dir = Direction8(i);
		for (int y = 0; y < grid.getHeight(); ++y) {
			for (int x = 0; x < grid.getWidth(); ++x) {
				if (grid.match({ x, y }, dirToVec2(dir), xmas)) {
					matches += 1;
				}
			}
		}
	}
	output << matches;
}

void solveDay4Part2(std::istream& input, std::ostream& output) {
	auto grid = parseGrid(input);
	int matches = 0;
	std::array<char, 3> mas = { 'M', 'A', 'S' };
	for (int y = 0; y < grid.getHeight(); ++y) {
		for (int x = 0; x < grid.getWidth(); ++x) {
			int diag = 0;
			for (int i = 1; i < 8; i += 2) {
				Direction8 dir = Direction8(i);
				Direction8 opp = Direction8((dir + 4) % 8);
				Vector2 pos = Vector2{ x, y } + dirToVec2(opp);
				if (grid.match(pos, dirToVec2(dir), mas)) {
					++diag;
				}
			}
			if (diag >= 2) {
				++matches;
			}
		}
	}
	output << matches;
}