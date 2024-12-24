#pragma once

#include <utility>
#include <type_traits>

template<typename T = int>
struct Vector2Base {
	T x;
	T y;

	Vector2Base operator+(const Vector2Base& other) const {
		return { x + other.x, y + other.y };
	}

	Vector2Base operator-(const Vector2Base& other) const {
		return { x - other.x, y - other.y };
	}

	Vector2Base operator-() const {
		return { -x, -y };
	}

	void operator+=(const Vector2Base& other) {
		*this = *this + other;
	}
	
	void operator-=(const Vector2Base& other) {
		*this = *this - other;
	}

	bool operator==(const Vector2Base& other) const {
		return x == other.x && y == other.y;
	}
};

template <typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;

template<typename T, Arithmetic S>
Vector2Base<T> operator*(S scalar, const Vector2Base<T>& vec) {
	return { vec.x * scalar, vec.y * scalar };
}

template<typename T, Arithmetic S>
inline Vector2Base<T> operator*(const Vector2Base<T>& vec, S scalar) {
	return { vec.x * scalar, vec.y * scalar };
}

template<typename T, Arithmetic S>
inline Vector2Base<T> operator/(const Vector2Base<T>& vec, S scalar) {
	return { vec.x / scalar, vec.y / scalar };
}

template<typename T, Arithmetic S>
inline Vector2Base<T> operator%(const Vector2Base<T>& vec, S scalar) {
	return { vec.x / scalar, vec.y / scalar };
}

namespace std {
	template<typename T> struct hash<Vector2Base<T>>
	{
		size_t operator()(const Vector2Base<T>& vec2) const {
			return std::hash<T>()(vec2.x) ^ (std::hash<T>()(vec2.y) << 1);
		}
	};
}

using Vector2 = Vector2Base<int>;
using Vector2LL = Vector2Base<int64_t>;
using Vector2F = Vector2Base<float>;
using Vector2D = Vector2Base<double>;