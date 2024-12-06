#include "Day2.h"
#include <sstream>
#include <vector>

namespace {
	bool levelsAreSafe(int level1, int level2, bool isIncr) {
		if (isIncr) {
			if (level1 < level2 && level2 - level1 <= 3) {
				return true;
			}
		}
		else if (level1 > level2 && level1 - level2 <= 3) {
			return true;
		}
		return false;
	}

	bool isReportSafe(const std::vector<int>& report) {
		if (report.size() <= 1) {
			return true;
		}
		bool isIncr = report[0] < report[1];
		for (int i = 0; i < report.size() - 1; ++i) {
			if (!levelsAreSafe(report[i], report[i + 1], isIncr)) {
				return false;
			}
		}
		return true;
	}

	bool isReportSafeWithTolerance(const std::vector<int>& report) {
		if (report.size() <= 2) {
			return true;
		}
		auto checkReport = [&](bool isIncr) {
			for (int i = 0; i < report.size(); ++i) {
				bool success = true;
				for (int j = 0; j < report.size() - 1; ++j) {
					if (j == i) continue;
					int k = j + 1;
					if (k == i) {
						k += 1;
					}
					if (k >= report.size()) {
						break;
					}
					if (!levelsAreSafe(report[j], report[k], isIncr)) {
						success = false;
						break;
					}
				}
				if (success) {
					return true;
				}
			}
			return false;
		};
		return checkReport(true) || checkReport(false);
	}
}

void solveDay2Part1(std::istream& input, std::ostream& output) {
	std::string line;
	int totalSafe = 0;
	while (getline(input, line)) {
		std::istringstream ss(line);
		std::vector<int> report;
		while (!ss.eof()) {
			int val;
			ss >> val;
			report.push_back(val);
		}
		if (isReportSafe(report)) {
			++totalSafe;
		}
	}
	output << totalSafe;
}

void solveDay2Part2(std::istream& input, std::ostream& output) {
	std::string line;
	int totalSafe = 0;
	while (getline(input, line)) {
		std::istringstream ss(line);
		std::vector<int> report;
		while (!ss.eof()) {
			int val;
			ss >> val;
			report.push_back(val);
		}
		if (isReportSafeWithTolerance(report)) {
			++totalSafe;
		}
	}
	output << totalSafe;
}