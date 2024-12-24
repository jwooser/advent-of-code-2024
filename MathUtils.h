#pragma once

#include <utility>
#include <optional>

inline int64_t gcd(int64_t a, int64_t b, int64_t& x, int64_t& y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	int64_t x1;
	int64_t y1;
	int64_t gcdVal = gcd(b % a, a, x1, y1);
	x = y1 - b / a * x1;
	y = x1;
	return gcdVal;
}

// Solutions are of the form
//     x = x0 - beta * t
//     y = y0 + alpha * t
// for some integer t
struct LinearDiophantineSolution {
	int64_t x0;
	int64_t y0;
	int64_t alpha;
	int64_t beta;
};

// Solves the linear diophantine equation ax + by = c
inline std::optional<LinearDiophantineSolution> solveLinearDiophantineEquation(int64_t a, int64_t b, int64_t c) {
	int64_t s;
	int64_t t;
	int64_t d = gcd(a, b, s, t);
	if (c % d != 0) {
		// no solutions
		return std::nullopt;
	}
	int64_t k = c / d;
	return LinearDiophantineSolution{ s * k, t * k, a / d, b / d};
}