#pragma once

#include "Vector2.h"

enum Direction4 {
	Up,
	Right,
	Down,
	Left
};

inline Vector2 vec2(Direction4 dir) {
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

inline Direction4 rotate90(Direction4 dir) {
	return Direction4((dir + 1) % 4);
}

inline Direction4 rotate90x(Direction4 dir, int x = 1) {
	return Direction4((((dir + x) % 4) + 4) % 4);
}

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

inline Vector2 vec2(Direction8 dir) {
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