#include "Day10.h"

#include <unordered_set>
#include "Vector2.h"
#include "StringUtils.h"
#include "Grid.h"
#include "Directions.h"

namespace {
	void dfsTrailScore(const Grid<int>& map,
		               Vector2 pos,
		               Grid<char>& seen,
		               std::unordered_set<Vector2>& reachable) {
		int currHeight = map.at(pos);
		if (currHeight == 9) {
			reachable.insert(pos);
			return;
		}
		Direction4 dir = Direction4::Up;
		for (int i = 0; i < 4; ++i) {
			Vector2 nextPos = pos + dirToVec2(dir);
			dir = rotate90(dir);
			if (map.inBounds(nextPos) && 
				!seen.at(nextPos) && 
				map.at(nextPos) == currHeight + 1) {
				seen.at(nextPos) = true;
				dfsTrailScore(map, nextPos, seen, reachable);
			}
		}
	}

	int getTrailheadScore(const Grid<int>& map, Vector2 trailhead) {
		std::unordered_set<Vector2> reachable;
		// use char instead of bool because we can't make a Grid of
		// bools due to the template specialization of the underlying
		// std::vector - we'd need to specialize Grid to bool as well
		Grid<char> seen(map.getWidth(), map.getHeight());
		dfsTrailScore(map, trailhead, seen, reachable);
		return int(reachable.size());
	}

	int dfsTrailRating(const Grid<int>& map,
		                Vector2 pos,
		                Grid<int>& memo) {
		int currHeight = map.at(pos);
		if (currHeight == 9) {
			return 1;
		}
		if (memo.at(pos) != -1) {
			return memo.at(pos);
		}
		int paths = 0;
		Direction4 dir = Direction4::Up;
		for (int i = 0; i < 4; ++i) {
			Vector2 nextPos = pos + dirToVec2(dir);
			dir = rotate90(dir);
			if (map.inBounds(nextPos) &&
				map.at(nextPos) == currHeight + 1) {
				paths += dfsTrailRating(map, nextPos, memo);
			}
		}
		memo.at(pos) = paths;
		return paths;
	}

	int getTrailheadRating(const Grid<int>& map, Vector2 trailhead) {
		Grid<int> memo(map.getWidth(), map.getHeight(), -1);
		return dfsTrailRating(map, trailhead, memo);
	}
}

void solveDay10Part1(std::istream& input, std::ostream& output) {
	auto map = parseGrid<int>(input, charToInt);
	int totalScore = 0;
	for (Vector2 trailhead : map.findAll(0)) {
		totalScore += getTrailheadScore(map, trailhead);
	}
	output << totalScore;
}

void solveDay10Part2(std::istream& input, std::ostream& output) {
	auto map = parseGrid<int>(input, charToInt);
	int totalScore = 0;
	for (Vector2 trailhead : map.findAll(0)) {
		totalScore += getTrailheadRating(map, trailhead);
	}
	output << totalScore;
}