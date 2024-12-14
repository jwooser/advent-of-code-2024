#include "Day8.h"

#include "Grid.h"
#include <set>

void solveDay8Part1(std::istream& input, std::ostream& output) {
	auto grid = parseGrid(input);
	std::unordered_map<char, std::vector<Vector2>> antennas;
	grid.forEachCell([&](Vector2 loc, char freq) {
		if (freq != '.') {
			antennas[freq].push_back(loc);
		}
	});
	std::set<std::pair<int, int>> antinodes;
	for (const auto& [freq, locs] : antennas) {
		for (int i = 0; i < locs.size(); ++i) {
			for (int j = 0; j < locs.size(); ++j) {
				if (i == j) continue;
				Vector2 antinodeLoc = locs[i] + (locs[i] - locs[j]);
				if (grid.inBounds(antinodeLoc)) {
					antinodes.insert(antinodeLoc.toPair());
				}
			}
		}
	}
	output << antinodes.size();
}

void solveDay8Part2(std::istream& input, std::ostream& output) {
	auto grid = parseGrid(input);
	std::unordered_map<char, std::vector<Vector2>> antennas;
	grid.forEachCell([&](Vector2 loc, char freq) {
		if (freq != '.') {
			antennas[freq].push_back(loc);
		}
		});
	std::set<std::pair<int, int>> antinodes;
	for (const auto& [freq, locs] : antennas) {
		for (int i = 0; i < locs.size(); ++i) {
			for (int j = 0; j < locs.size(); ++j) {
				if (i == j) continue;
				Vector2 curr = locs[i];
				Vector2 slope = locs[i] - locs[j];
				while (grid.inBounds(curr)) {
					antinodes.insert(curr.toPair());
					curr += slope;
				}
			}
		}
	}
	output << antinodes.size();
}