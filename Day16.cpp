#include "Day16.h"

#include <optional>
#include <unordered_set>
#include <queue>
#include "Graph.h"
#include "Grid.h"
#include "Vector2.h"
#include "Directions.h"
#include "EnumUtils.h"
#include "Utils.h"

namespace {
	enum Tile {
		Start,
		End,
		Floor,
		Wall
	};

	using State = std::pair<Vector2, Direction4>;

	struct StateNode {
		int cost;
		State state;
		std::optional<State> prev;
	};

	std::pair<int, int> searchMaze(const Grid<Tile>& maze) {
		// Dijkstra's Algorithm
		const auto comparator = makeMemberComparator(&StateNode::cost, std::greater<int>{});  
		using MinQueue = std::priority_queue<StateNode, std::vector<StateNode>, decltype(comparator)>;
		MinQueue q(comparator);

		AdjList<State, PairHash> pathGraph;
		std::unordered_set<Vector2> bestPos;
		std::unordered_map<State, int, PairHash> costMemo;
		State startState = { maze.find(Start).value(), Right };
		q.push({0, startState});

		int minScore = -1;

		while (!q.empty()) {
			auto [cost, state, prev] = q.top();
			auto [pos, dir] = state;
			q.pop();
			if (costMemo.contains(state)) {
				if (costMemo.at(state) == cost) {
					pathGraph.addEdge(state, prev.value());
				}
				continue;
			}
			if (prev.has_value()) {
				pathGraph.addEdge(state, prev.value());
			}
			if (maze.at(pos) == End) {
				if (minScore == -1) {
					minScore = cost;
				}
				if (cost == minScore) {
					for (auto step : dfsFromVertex(pathGraph, state)) {
						bestPos.insert(step.first);
					}
				}
				continue;
			}
			costMemo.insert({ state, cost });
			for (int i = -1; i <= 1; ++i) {
				Direction4 newDir = rotate90x(dir, i);
				Vector2 newPos = pos + vec2(newDir);
				State newState = { newPos, newDir };
				Tile tile = maze.at(newPos);
				if (tile == Floor || tile == End) {
					int newCost = cost + 1 + std::abs(i) * 1000;
					q.push({newCost, newState, state});
				}
			}
		}
		return { minScore, bestPos.size()};
	}
}

void solveDay16Part1(std::istream& input, std::ostream& output) {
	auto maze = parseGrid<Tile>(input, charToEnum<Tile, 'S', 'E', '.', '#'>);
	output << searchMaze(maze).first;
}

void solveDay16Part2(std::istream& input, std::ostream& output) {
	auto maze = parseGrid<Tile>(input, charToEnum<Tile, 'S', 'E', '.', '#'>);
	output << searchMaze(maze).second;
}