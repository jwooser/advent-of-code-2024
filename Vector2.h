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