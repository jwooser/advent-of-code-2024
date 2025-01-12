#include "Day12.h"
#include "Grid.h"
#include <bitset>
#include "Directions.h"

namespace {
	struct State {
		char type;
		bool seen;
	};

	void dfsPerimeterAndArea(Grid<State>& plot, Vector2 pos, int& perim, int& area) {
		area += 1;
		char type = plot.at(pos).type;
		plot.at(pos).seen = true;
		Direction4 dir = Direction4::Up;
		for (int i = 0; i < 4; ++i) {
			Vector2 nextPos = pos + vec2(dir);
			dir = rotate90(dir);
			if (plot.inBounds(nextPos)) {
				const State& nextState = plot.at(nextPos);
				if (type == nextState.type && !nextState.seen) {
					dfsPerimeterAndArea(plot, nextPos, perim, area);
				}
				else if (type != nextState.type) {
					++perim;
				}
			}
			else {
				++perim;
			}
		}
	}

	void dfsSidesAndArea(Grid<State>& plot, Vector2 pos, int& sides, int& area) {
		area += 1;
		char type = plot.at(pos).type;
		plot.at(pos).seen = true;
		Direction4 dir = Direction4::Up;
		for (int i = 0; i < 4; ++i) {
			Vector2 nextPos = pos + vec2(dir);
			dir = rotate90(dir);
			if (plot.inBounds(nextPos)) {
				const State& nextState = plot.at(nextPos);
				if (type == nextState.type && !nextState.seen) {
					dfsSidesAndArea(plot, nextPos, sides, area);
				}
			}
		}
		// Count the number of corners, which is equal to the number of sides
		Direction8 dir8 = Direction8::North;
		for (int i = 0; i < 4; ++i) {
			Direction8 d = dir8;
			dir8 = rotate90(dir8);
			Vector2 frontPos = pos + vec2(d);
			d = rotate45(d);
			Vector2 diagPos = pos + vec2(d);
			d = rotate45(d);
			Vector2 rightPos = pos + vec2(d);
			bool front = plot.inBounds(frontPos) && plot.at(frontPos).type == type;
			bool diag = plot.inBounds(diagPos) && plot.at(diagPos).type == type;
			bool right = plot.inBounds(rightPos) && plot.at(rightPos).type == type;
			if ((!front && !right) || (front && right && !diag)) {
				++sides;
			}
		}
	}
}

void solveDay12Part1(std::istream& input, std::ostream& output) {
	auto grid = parseGrid<State>(input, [](char c) {return State{ c, false }; });
	int totalPrice = 0;
	grid.forEachCell([&](Vector2 pos, const State& state) {
		if (!state.seen) {
			int area = 0;
			int perim = 0;
			dfsPerimeterAndArea(grid, pos, perim, area);
			totalPrice += perim * area;
		}
	});
	output << totalPrice;
}

void solveDay12Part2(std::istream& input, std::ostream& output) {
	auto grid = parseGrid<State>(input, [](char c) {return State{ c, false }; });
	int totalPrice = 0;
	grid.forEachCell([&](Vector2 pos, const State& state) {
		if (!state.seen) {
			int area = 0;
			int sides = 0;
			dfsSidesAndArea(grid, pos, sides, area);
			totalPrice += sides * area;
		}
	});
	output << totalPrice;
}