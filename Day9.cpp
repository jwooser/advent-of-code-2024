#include "Day9.h"

#include <string>
#include <stack>
#include <queue>
#include <ranges>
#include "StringUtils.h"

namespace {
	struct Block {
		int index;
		int size;
		int id;

		long long checksum() {
			return (long long(index) + index + size - 1) * size / 2 * id;
		}
	};
}

void solveDay9Part1(std::istream& input, std::ostream& output) {
	std::string line;
	getline(input, line);
	std::queue<Block> free;
	std::stack<Block> files;
	int totalSize = 0;
	int id = 0;
	for (int i = 0; i < line.size(); ++i) {
		int size = charToInt(line[i]);
		if (size == 0) continue;
		if (i % 2 == 0) {
			files.push({ totalSize, size, id });
			++id;
		}
		else {
			free.push({ totalSize, size, -1 });
		}
		totalSize += size;
	}
	std::vector<Block> defrag;
	while (!files.empty()) {
		Block file = files.top();
		files.pop();
		while (!free.empty() && free.front().index < file.index) {
			int blocksToMove = std::min(free.front().size, file.size);
			defrag.emplace_back(free.front().index, blocksToMove, file.id);
			free.front().index += blocksToMove;
			free.front().size -= blocksToMove;
			file.size -= blocksToMove;
			if (file.size == 0) break;
			if (free.front().size == 0) {
				free.pop();
			}
		}
		if (file.size > 0) {
			defrag.push_back(file);
		}
	}
	long long checksum = 0;
	for (auto& block : defrag) {
		checksum += block.checksum();
	}
	output << checksum;
}

void solveDay9Part2(std::istream& input, std::ostream& output) {
	std::string line;
	getline(input, line);
	std::list<Block> free;
	std::stack<Block> files;
	int totalSize = 0;
	int id = 0;
	for (int i = 0; i < line.size(); ++i) {
		int size = charToInt(line[i]);
		if (size == 0) continue;
		if (i % 2 == 0) {
			files.push({ totalSize, size, id });
			++id;
		}
		else {
			free.push_back({ totalSize, size, -1 });
		}
		totalSize += size;
	}
	std::vector<Block> defrag;
	while (!files.empty()) {
		Block file = files.top();
		files.pop();
		for (auto it = free.begin(); it != free.end(); ++it) {
			if (it->index >= file.index) break;
			if (it->size >= file.size) {
				defrag.emplace_back(it->index, file.size, file.id);
				it->index += file.size;
				it->size -= file.size;
				file.size = 0;
				if (it->size == 0) {
					free.erase(it);
				}
				break;
			}
		}
		if (file.size > 0) {
			defrag.push_back(file);
		}
	}
	long long checksum = 0;
	for (auto& block : defrag) {
		checksum += block.checksum();
	}
	output << checksum;
}