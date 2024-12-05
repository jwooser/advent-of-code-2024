#include "Day1.h"
#include <vector>
#include <unordered_map>
#include <algorithm>

void solveDay1Part1(std::istream& input, std::ostream& output) {
	std::vector<int> list1;
	std::vector<int> list2;
	
	while (true) {
		int num;
		input >> num;
		if (input.eof()) break;
		list1.push_back(num);
		input >> num;
		list2.push_back(num);
	}

	std::sort(list1.begin(), list1.end());
	std::sort(list2.begin(), list2.end());

	int totalDiff = 0;
	for (int i = 0; i < list1.size(); ++i) {
		totalDiff += std::abs(list1[i] - list2[i]);
	}

	output << totalDiff;
}

void solveDay1Part2(std::istream& input, std::ostream& output) {
	std::unordered_map<int, int> list1counts;
	std::unordered_map<int, int> list2counts;

	while (true) {
		int num;
		input >> num;
		if (input.eof()) break;
		list1counts[num]++;
		input >> num;
		list2counts[num]++;
	}

	int totalSim = 0;
	for (auto [num, count] : list1counts) {
		totalSim += num * list2counts[num] * count;
	}

	output << totalSim;
}