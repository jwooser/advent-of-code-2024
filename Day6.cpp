#include "Day6.h"

#include <array>
#include <vector>
#include <bitset>
#include <string>
#include <set>;

namespace {
	enum GridState {
		Unvisited,
		Visited,
		Blocked
	};

	using Grid = std::vector<std::vector<GridState>>;

	enum Direction {
		Up,
		Right,
		Down,
		Left
	};

	struct Vector2 {
		int x;
		int y;

		Vector2 operator+(const Vector2& other) const {
			return { x + other.x, y + other.y };
		}

		void operator+=(const Vector2& other) {
			*this = *this + other;
		}

		bool operator==(const Vector2& other) const {
			return x == other.x && y == other.y;
		}
	};

	Vector2 dirToVec2(Direction dir) {
		std::array<Vector2, 4> dirVectors = {
			Vector2{0, -1},
			Vector2{1, 0},
			Vector2{0, 1},
			Vector2{-1, 0},
		};

		return dirVectors[dir];
	}

	bool isInsideGrid(const Grid& grid, Vector2 pos) {
		int height = grid.size();
		int width = grid[0].size();
		return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
	}

	struct GuardState {
		Vector2 pos;
		Direction dir;

		bool advance(const Grid& grid) {
			int height = grid.size();
			int width = grid[0].size();
			Vector2 posInFront = getPosInFront();
			if (!isInsideGrid(grid, posInFront)) {
				return false; // advanced out of grid
			}
			if (grid[posInFront.y][posInFront.x] == Blocked) {
				dir = Direction((dir + 1) % 4); // turn 90 deg
			}
			else {
				pos = posInFront; // move forward
			}
			return true;
		}

		Vector2 getPosInFront() const {
			return pos + dirToVec2(dir);
		}

		bool operator==(const GuardState& other) const {
			return pos == other.pos && dir == other.dir;
		}
	};

	std::pair<Grid, Vector2> parseGrid(std::istream& input) {
		std::vector<std::vector<GridState>> grid;
		Vector2 pos;
		std::string line;
		while (getline(input, line)) {
			int x = 0;
			int y = grid.size();
			grid.push_back({});

			for (char c : line) {
				if (c == '.') {
					grid[y].push_back(Unvisited);
				}
				else if (c == '#') {
					grid[y].push_back(Blocked);
				}
				else {
					grid[y].push_back(Visited);
					pos = { x, y };
				}
				++x;
			}
		}
		return { std::move(grid), pos };
	}

	// Slow and fast pointer algorithm for detecting cycles
	bool isPathLoop(const Grid& grid, GuardState guard) {
		GuardState fast = guard;
		GuardState slow = guard;
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
};

void solveDay6Part1(std::istream& input, std::ostream& output) {
	auto [grid, pos] = parseGrid(input);
	GuardState guard{ pos, Up };

	while (guard.advance(grid)) {
		grid[guard.pos.y][guard.pos.x] = Visited;
	}

	int totalVisited = 0;
	for (auto& row : grid) {
		for (auto cell : row) {
			totalVisited += (cell == Visited);
		}
	}
	output << totalVisited;
}

void solveDay6Part2(std::istream& input, std::ostream& output) {
	auto [grid, pos] = parseGrid(input);
	GuardState guard{ pos, Up };
	std::set<std::pair<int, int>> obs;
	do {
		grid[guard.pos.y][guard.pos.x] = Visited;
		Vector2 posInFront = guard.getPosInFront();
		if (!isInsideGrid(grid, posInFront)) {
			continue;
		}
		if (grid[posInFront.y][posInFront.x] == Unvisited && 
			!obs.contains({ posInFront.y, posInFront.x })) {
			grid[posInFront.y][posInFront.x] = Blocked;
			if (isPathLoop(grid, guard)) {
				obs.insert({ posInFront.y, posInFront.x });
			}
			grid[posInFront.y][posInFront.x] = Unvisited;
		}
	} while (guard.advance(grid));
	output << obs.size();
}