#pragma once

#include <utility>

struct Vector2 {
	int x;
	int y;

	Vector2 operator+(const Vector2& other) const {
		return { x + other.x, y + other.y };
	}

	Vector2 operator-(const Vector2& other) const {
		return { x - other.x, y - other.y };
	}

	Vector2 operator-() const {
		return { -x, -y };
	}

	void operator+=(const Vector2& other) {
		*this = *this + other;
	}
	
	void operator-=(const Vector2& other) {
		*this = *this - other;
	}

	bool operator==(const Vector2& other) const {
		return x == other.x && y == other.y;
	}
};

namespace std {
	template <> struct hash<Vector2>
	{
		size_t operator()(const Vector2& vec2) const {
			return std::hash<int>()(vec2.x) ^ (std::hash<int>()(vec2.y) << 1);
		}
	};
}

inline Vector2 operator*(int scalar, const Vector2& vec) {
	return { vec.x * scalar, vec.y * scalar };
}

inline Vector2 operator*(const Vector2& vec, int scalar) {
	return { vec.x * scalar, vec.y * scalar };
}

enum Direction4 {
	Up,
	Right,
	Down,
	Left
};

enum Direction8 {
	North,
	NorthEast,
	East,
	SouthEast,
	South,
	SouthWest,
	West,
	NorthWest
};

inline Vector2 dirToVec2(Direction4 dir) {
	switch (dir)
	{
	case Up:
		return { 0, -1 };
	case Right:
		return { 1, 0 };
	case Down:
		return { 0, 1 };
	case Left:
		return { -1, 0 };
	default:
		return {};
	}
}

inline Vector2 dirToVec2(Direction8 dir) {
	switch (dir)
	{
	case North:
		return { 0, -1 };
	case NorthEast:
		return { 1, -1 };
	case East:
		return { 1, 0 };
	case SouthEast:
		return { 1, 1 };
	case South:
		return { 0, 1 };
	case SouthWest:
		return { -1, 1 };
	case West:
		return { -1, 0 };
	case NorthWest:
		return { -1, -1 };
	default:
		return {};
	}
}

inline Direction8 rotate45(Direction8 dir) {
	return Direction8((dir + 1) % 8);
}

inline Direction8 rotate90(Direction8 dir) {
	return Direction8((dir + 2) % 8);
}

inline Direction4 rotate90(Direction4 dir) {
	return Direction4((dir + 1) % 4);
}