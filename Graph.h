#pragma once
#include <vector>
#include <queue>
#include <span>
#include <unordered_map>
#include <unordered_set>
#include <ranges>

template <typename T = int, typename Hash = std::hash<T>>
class AdjList {
public:
	void addVertex(const T& v) {
		graph[v];
	}

	void addEdge(const T& from, const T& to) {
		graph[from].push_back(to);
		addVertex(to);
	}

	auto getVertices() const {
		return std::views::keys(graph);
	}

	int numVertices() const {
		return graph.size();
	}
	
	bool hasVertex(const T& v) const {
		return graph.contains(v);
	}

	std::span<const T> getSuccessors(const T& v) const {
		return graph.at(v);
	}

	bool hasEdge(const T& from, const T& to) const {
		auto neighbors = getSuccessors(from);
		return std::ranges::find(neighbors, to) != neighbors.end();
	}

private:
	std::unordered_map<T, std::vector<T>, Hash> graph;
};

template<typename T, typename Hash = std::hash<T>>
AdjList<T> inducedSubgraph(const AdjList<T, Hash>& graph, const std::unordered_set<T>& vertices) {
	AdjList<T> subgraph;
	for (const auto& u : vertices) {
		for (const auto v : graph.getSuccessors(u)) {
			if (vertices.contains(v)) {
				subgraph.addEdge(u, v);
			}
		}
	}
	return subgraph;
}

template<typename T, typename Hash = std::hash<T>>
std::vector<T> topologicalOrdering(const AdjList<T, Hash>& graph) {
	std::unordered_map<T, int> inEdges;
	for (const auto& u : graph.getVertices()) {
		for (const auto& v : graph.getSuccessors(u)) {
			++inEdges[v];
		}
	}
	std::queue<T> q;
	for (const auto& v : graph.getVertices()) {
		if (inEdges[v] == 0) {
			q.push(v);
		}
	}
	std::vector<T> result;
	while (!q.empty()) {
		T u = q.front();
		q.pop();
		result.push_back(u);
		for (auto& v : graph.getSuccessors(u)) {
			int& n = inEdges[v];
			--n;
			if (n == 0) {
				q.push(v);
			}
		}
	}
	return result;
}

template<typename T, typename Hash = std::hash<T>>
std::unordered_set<T, Hash> dfsFromVertex(const AdjList<T, Hash>& graph, const T& v) {
	std::unordered_set<T, Hash> seen;
	auto dfs = [&](const T& v, auto _dfs) -> void {
		seen.insert(v);
		for (const auto& u : graph.getSuccessors(v)) {
			if (!seen.contains(u)) {
				_dfs(u, _dfs);
			}
		}
	};
	if (graph.hasVertex(v)) {
		dfs(v, dfs);
	}
	return seen;
}