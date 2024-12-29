#include "Day15.h"

#include <stdexcept>
#include <string>
#include <array>
#include <sstream>
#include "Directions.h"
#include "Grid.h"
#include "Utils.h"

namespace {
	enum Tile {
		Empty,
		Wall,
		Box,
		BigBoxL,
		BigBoxR,
		Robot
	};

	char tileToChar(Tile tile) {
		const std::array<char, 6> chars{ '.', '#', 'O', '[', ']', '@' };
		return chars[tile];
	}

	Tile tileProj(char c) {
		switch (c) {
		case '.':
			return Empty;
		case '#':
			return Wall;
		case 'O':
			return Box;
		case '[':
			return BigBoxL;
		case ']':
			return BigBoxR;
		case '@':
			return Robot;
		default:
			throw std::invalid_argument("Character must be on of: .#O@");
		}
	}

	Direction4 dirProj(char c) {
		switch (c) {
			case '^':
			case 'w':
				return Up;
			case '>':
			case 'd':
				return Right;
			case 'v':
			case 's':
				return Down;
			case '<':
			case 'a':
				return Left;
			default:
				throw std::invalid_argument("Character must be on of: ^>v<");
		}
	}

	struct RobotController {
		Vector2 robotPos;
		Grid<Tile>* map;

		void advanceRobot(Direction4 d) {
			if (canPushTile(robotPos, d)) {
				pushTile(robotPos, d);
				robotPos += dirToVec2(d);
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
				if (!canPushTile(pos + dirToVec2(otherSide), d)) {
					return false;
				}
			}
			// must be able to push the tile in front
			return canPushTile(pos + dirToVec2(d), d);
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
				pushTile(pos + dirToVec2(otherSide), d);
			}
			Vector2 nextPos = pos + dirToVec2(d);
			pushTile(nextPos, d);
			Tile& nextTile = map->at(nextPos);
			if (nextTile == Empty) {
				std::swap(tile, nextTile);
			}
		}
	};

	void userInputLoop(RobotController& rc) {
		while (true) {
			printGrid(*rc.map, std::cout, tileToChar);
			char in;
			std::cin >> in;
			if (in == 'q') return;
			rc.advanceRobot(dirProj(in));
		}
	}
}

void solveDay15Part1(std::istream& input, std::ostream& output) {
	auto map = parseGrid<Tile>(input, tileProj);
	Vector2 robotPos = map.find(Robot).value();
	RobotController rc{robotPos, &map};

	std::string line;
	while (getline(input, line)) {
		if (line == "debug") {
			userInputLoop(rc);
		}
		for (char c : line) {
			rc.advanceRobot(dirProj(c));
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