#include "Day6.h"

#include <array>
#include <vector>
#include <bitset>
#include <string>
#include <unordered_set>
#include "Vector2.h"
#include "Grid.h"
#include "Directions.h"
#include "EnumUtils.h"

namespace {
	enum State {
		Unvisited,
		Visited,
		Blocked
	};

	struct Guard {
		Vector2 pos;
		Direction4 dir;
		
		bool advance(const Grid<State>& grid) {
			Vector2 posInFront = getPosInFront();
			if (!grid.inBounds(posInFront)) {
				return false; // advanced out of grid
			}
			if (grid.at(posInFront) == Blocked) {
				dir = rotate90(dir); // turn 90 deg
			}
			else {
				pos = posInFront; // move forward
			}
			return true;
		}

		Vector2 getPosInFront() const {
			return pos + vec2(dir);
		}

		bool operator==(const Guard& other) const {
			return pos == other.pos && dir == other.dir;
		}
	};

	// Slow and fast pointer algorithm for detecting cycles
	bool isPathLoop(const Grid<State>& grid, Guard guard) {
		Guard fast = guard;
		Guard slow = guard;
		while (true) {
			fast.advance(grid);
			if (!fast.advance(grid)) {
				return false;
			}
			slow.advance(grid);
			if (fast == slow) {
				return true;
			}
		}
	}
}

void solveDay6Part1(std::istream& input, std::ostream& output) {
	auto grid = parseGrid<State>(input, charToEnum<State, '.', '^', '#'>);

	Vector2 pos = grid.find(Visited).value();
	Guard guard{ pos, Up };

	while (guard.advance(grid)) {
		grid.at(guard.pos) = Visited;
	}

	int totalVisited = 0;
	for (auto& cell : grid.span()) {
		totalVisited += (cell == Visited);
	}
	output << totalVisited;
}

void solveDay6Part2(std::istream& input, std::ostream& output) {
	auto grid = parseGrid<State>(input, charToEnum<State, '.', '^', '#'>);
	Vector2 pos = grid.find(Visited).value();
	Guard guard{ pos, Up };

	std::unordered_set<Vector2> obs;
	do {
		grid.at(guard.pos) = Visited;
		Vector2 posInFront = guard.getPosInFront();
		if (!grid.inBounds(posInFront)) {
			continue;
		}
		if (grid.at(posInFront) == Unvisited && !obs.contains(posInFront)) {
			grid.at(posInFront) = Blocked;
			if (isPathLoop(grid, guard)) {
				obs.insert(posInFront);
			}
			grid.at(posInFront) = Unvisited;
		}
	} while (guard.advance(grid));
	output << obs.size();
}