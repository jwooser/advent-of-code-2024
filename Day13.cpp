#include "Day13.h"
#include <string>
#include "StringUtils.h"
#include "Vector2.h"
#include "MathUtils.h"

namespace {
	int64_t minCostToPosition(Vector2LL a, Vector2LL b, Vector2LL pos) {
		bool oneSolution = false;
		auto [a1, a2] = a;
		auto [b1, b2] = b;
		auto [p1, p2] = pos;
		int64_t b3 = a1 * b2 - a2 * b1;
		int64_t p3 = a1 * p2 - a2 * p1;
		if (b3 != 0) {
			if (p3 % b3 != 0) {
				return 0;
			}
			int64_t y = p3 / b3;
			int64_t x = (p1 - y * b1) / a1;
			if (x * a1 + y * b1 == p1) {
				return 3 * x + y;
			}
		}
		else if (p3 == 0) {
			auto sol = solveLinearDiophantineEquation(a1, b1, p1);
			if (!sol.has_value()) {
				return 0;
			}
			auto [x0, y0, alpha, beta] = sol.value();
			// Binary search for the minimum cost (concave sequence)
			int64_t l = -y0 / alpha;
			int64_t r = x0 / beta;
			while (l < r) {
				int64_t m = (l + r) / 2;
				int64_t x = x0 - beta * m;
				if (x < 0) {
					l = m;
					continue;
				}
				int64_t y = y0 + alpha * m;
				if (y < 0) {
					r = m;
					continue;
				}
				int64_t cost = 3 * x + y;
				int64_t cost2 = 3 * (x - beta) + (y + alpha);
				if (cost < cost2) {
					r = m + 1;
				}
				else {
					l = m;
				}
			}
			return 3 * (x0 - beta * l) + (y0 + alpha * l);
		}
		return 0;
	}
}

void solveDay13Part1(std::istream& input, std::ostream& output) {
	std::string line;
	int64_t totalCost{};
	while (getline(input, line)) {
		Vector2LL a;
		a.x = parseNumber(line, "X+");
		a.y = parseNumber(line, "Y+");

		getline(input, line);
		Vector2LL b;
		b.x = parseNumber(line, "X+");
		b.y = parseNumber(line, "Y+");

		getline(input, line);
		Vector2LL p;
		p.x = parseNumber(line, "X=");
		p.y = parseNumber(line, "Y=");

		totalCost += minCostToPosition(a, b, p);

		getline(input, line); //skip a line
	}
	output << totalCost;
}

void solveDay13Part2(std::istream& input, std::ostream& output) {
	std::string line;
	int64_t totalCost{};
	while (getline(input, line)) {
		Vector2LL a;
		a.x = parseNumber(line, "X+");
		a.y = parseNumber(line, "Y+");

		getline(input, line);
		Vector2LL b;
		b.x = parseNumber(line, "X+");
		b.y = parseNumber(line, "Y+");

		getline(input, line);
		Vector2LL p;
		p.x = parseNumber(line, "X=") + 10000000000000;
		p.y = parseNumber(line, "Y=") + 10000000000000;

		totalCost += minCostToPosition(a, b, p);

		getline(input, line); //skip a line
	}
	output << totalCost;
}