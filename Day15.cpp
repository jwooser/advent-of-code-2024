#include "Day15.h"

#include <stdexcept>
#include <string>
#include <array>
#include <sstream>
#include "Directions.h"
#include "Grid.h"
#include "Utils.h"
#include "EnumUtils.h"

namespace {
	enum Tile {
		Empty,
		Wall,
		Box,
		BigBoxL,
		BigBoxR,
		Robot
	};	

	struct RobotController {
		Vector2 robotPos;
		Grid<Tile>* map;

		void advanceRobot(Direction4 d) {
			if (canPushTile(robotPos, d)) {
				pushTile(robotPos, d);
				robotPos += vec2(d);
			}
		}

	private:

		bool canPushTile(Vector2 pos, Direction4 d) {
			Tile& tile = map->at(pos);

			if (tile == Empty) {
				return true;
			}
			if (tile == Wall) {
				return false;
			}

			// must be able to push the other side of the big box as well
			if ((tile == BigBoxL || tile == BigBoxR) && (d == Up || d == Down)) {
				ScopedRevert tileRev(tile); // backtracking RAII
				Direction4 otherSide = (tile == BigBoxL) ? Right : Left;
				tile = Empty;
				if (!canPushTile(pos + vec2(otherSide), d)) {
					return false;
				}
			}
			// must be able to push the tile in front
			return canPushTile(pos + vec2(d), d);
		}

		void pushTile(Vector2 pos, Direction4 d) {
			Tile& tile = map->at(pos);
			if (tile == Empty || tile == Wall) {
				return;
			}
			if ((tile == BigBoxL || tile == BigBoxR) && (d == Up || d == Down)) {
				ScopedRevert tileRev(tile);
				Direction4 otherSide = (tile == BigBoxL) ? Right : Left;
				tile = Empty; // prevent infinite recursion between sides
				pushTile(pos + vec2(otherSide), d);
			}
			Vector2 nextPos = pos + vec2(d);
			pushTile(nextPos, d);
			Tile& nextTile = map->at(nextPos);
			if (nextTile == Empty) {
				std::swap(tile, nextTile);
			}
		}
	};

	void userInputLoop(RobotController& rc) {
		while (true) {
			printGrid(*rc.map, std::cout, enumToChar<Tile ,'.', '#', 'O', '[', ']', '@'>);
			char in;
			std::cin >> in;
			if (in == 'q') return;
			rc.advanceRobot(charToEnum<Direction4, 'w', 'd', 's', 'a'>(in));
		}
	}
}

void solveDay15Part1(std::istream& input, std::ostream& output) {
	auto map = parseGrid<Tile>(input, charToEnum<Tile, '.', '#', 'O', '[', ']', '@'>);
	Vector2 robotPos = map.find(Robot).value();
	RobotController rc{robotPos, &map};

	std::string line;
	while (getline(input, line)) {
		if (line == "debug") {
			userInputLoop(rc);
		}
		for (char c : line) {
			rc.advanceRobot(charToEnum<Direction4, '^', '>', 'v', '<'>(c));
		}
	}
	int gpsSum = 0;
	map.forEachCell([&](Vector2 pos, const Tile& t) {
		if (t == Box || t == BigBoxL) {
			gpsSum += pos.x + pos.y * 100;
		}
	});
	output << gpsSum;
}

void solveDay15Part2(std::istream& input, std::ostream& output) {
	std::string line;
	std::string mapStr;
	while (getline(input, line)) {
		if (line == "") {
			break;
		}
		for (char c : line) {
			if (c == 'O') {
				mapStr += "[]";
			}
			else if (c == '@') {
				mapStr += "@.";
			}
			else {
				mapStr += c;
				mapStr += c;
			}
		}
		mapStr += '\n';
	}
	std::stringstream augmentedInput;
	augmentedInput << mapStr;
	augmentedInput << '\n';
	augmentedInput << input.rdbuf();
	solveDay15Part1(augmentedInput, output);
}