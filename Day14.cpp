#include "Day14.h"

#include <array>
#include <unordered_set>
#include <vector>
#include <string>
#include "MathUtils.h"
#include "Vector2.h"
#include "StringUtils.h"
#include "Grid.h"
#include "Directions.h"

namespace {
	Vector2 stringToVec2(const std::string& str) {
		auto nums = split<int>(str, ",", stoiFunc);
		return { nums[0], nums[1] };
	}

	struct Robot {
		Vector2 pos;
		Vector2 vel;
	};

	void timestep(std::vector<Robot>& robots, int w, int h) {
		for (auto& r : robots) {
			r.pos += r.vel;
			if (r.pos.x < 0) {
				r.pos.x += w * intDivCeil(-r.pos.x, w);
			}
			else if (r.pos.x >= w) {
				r.pos.x %= w;
			}
			if (r.pos.y < 0) {
				r.pos.y += h * intDivCeil(-r.pos.y, h);
			}
			else if (r.pos.y >= h) {
				r.pos.y %= h;
			}
		}
	}

	using QuadrantCounts = std::array<int, 4>;

	QuadrantCounts calcQuadrantCounts(const std::vector<Robot>& robots, int w, int h) {
		int mx = w / 2;
		int my = h / 2;
		QuadrantCounts q{};
		for (auto& r : robots) {
			if (r.pos.x < mx) {
				if (r.pos.y < my) {
					++q[0];
				}
				else if (r.pos.y > my) {
					++q[1];
				}
			}
			else if (r.pos.x > mx) {
				if (r.pos.y < my) {
					++q[2];
				}
				else if (r.pos.y > my) {
					++q[3];
				}
			}
		}
		return q;
	}
}


void solveDay14Part1(std::istream& input, std::ostream& output) {
	std::vector<Robot> robots;
	std::string line;
	int w = 101;
	int h = 103;
	while (getline(input, line)) {
		if (line[0] == 'w') {
			w = parseNumber(line, "w=");
			h = parseNumber(line, "h=");
			continue;
		}
		auto pos = parseDescriptor<Vector2>(line, "p=", stringToVec2);
		auto vel = parseDescriptor<Vector2>(line, "v=", stringToVec2);
		robots.emplace_back(pos, vel);
	}
	for (int t = 0; t < 100; ++t) {
		timestep(robots, w, h);
	}

	auto [q1, q2, q3, q4] = calcQuadrantCounts(robots, w, h);

	output << q1 * q2 * q3 * q4;
}

void solveDay14Part2(std::istream& input, std::ostream& output) {
	std::vector<Robot> robots;
	std::string line;
	int w = 101;
	int h = 103;
	while (getline(input, line)) {
		if (line[0] == 'w') {
			w = parseNumber(line, "w=");
			h = parseNumber(line, "h=");
			continue;
		}
		auto pos = parseDescriptor<Vector2>(line, "p=", stringToVec2);
		auto vel = parseDescriptor<Vector2>(line, "v=", stringToVec2);
		robots.emplace_back(pos, vel);
	}
	int t = 0;
	double minVar = DBL_MAX;
	while (true) {
		++t;
		timestep(robots, w, h);
		Vector2D centroid{};
		for (auto& r : robots) {
			centroid += Vector2D(r.pos.x, r.pos.y);
		}
		centroid = centroid / robots.size();
		double variance = 0;
		for (auto& r : robots) {
			variance  += pow(r.pos.x - centroid.x, 2) + pow(r.pos.y - centroid.y, 2);
		}
		variance /= robots.size();
		if (variance < minVar) {
			minVar = variance;
			Grid grid(w, h, '.');
			for (auto& r : robots) {
				grid.at(r.pos) = '#';
			}
			printGrid(grid, std::cout);
			char response = 'n';
			std::cout << "Is this a Christmas tree? (y/n): ";
			std::cin >> response;
			if (response == 'y') {
				break;
			}
		}
	}
	output << t;
}