#include "Day5.h"

#include <string>
#include "Graph.h"
#include "StringUtils.h"

void solveDay5Part1(std::istream& input, std::ostream& output) {
	std::string line;
	auto stoiFunc = [](const std::string& str) {
		return std::stoi(str);
	};
	AdjList graph;
	while (getline(input, line)) {
		if (line == "") {
			break;
		}
		auto rule = split<int>(line, "|", stoiFunc);
		graph.addEdge(rule[0], rule[1]);
	}
	int sum = 0;
	while (getline(input, line)) {
		std::vector<int> update = split<int>(line, ",", stoiFunc);
		AdjList subgraph = inducedSubgraph(graph, { update.begin(), update.end() });
		std::vector<int> ordering = topologicalOrdering(subgraph);
		if (update == ordering) {
			sum += update[update.size() / 2];
		}
	}
	output << sum;
}

void solveDay5Part2(std::istream& input, std::ostream& output) {
	std::string line;
	auto stoiFunc = [](const std::string& str) {
		return std::stoi(str);
	};
	AdjList graph;
	while (getline(input, line)) {
		if (line == "") {
			break;
		}
		auto rule = split<int>(line, "|", stoiFunc);
		graph.addEdge(rule[0], rule[1]);
	}
	int sum = 0;
	while (getline(input, line)) {
		std::vector<int> update = split<int>(line, ",", stoiFunc);
		AdjList subgraph = inducedSubgraph(graph, { update.begin(), update.end() });
		std::vector<int> ordering = topologicalOrdering(subgraph);
		if (update != ordering) {
			sum += ordering[ordering.size() / 2];
		}
	}
	output << sum;
}