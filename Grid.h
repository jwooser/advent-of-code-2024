#pragma once

#include <istream>
#include <functional>
#include <optional>
#include <span>
#include <string>
#include <vector>
#include <ranges>
#include "Vector2.h"

template <typename T>
class Grid {
public:
	Grid() { };
	
	Grid(size_t w, size_t h)
		: width{ w }, height{ h } {
		data.resize(w * h);
	}

	Grid(size_t w, size_t h, const T& val)
		: width{ w }, height{ h } {
		data.resize(w * h, val);
	}

	Grid(size_t w, size_t h, std::vector<T> d)
		: width{ w }, height{ h }, data{ std::move(d) } {
		data.resize(w * h);
	}

	void resize(size_t w, size_t h) {
		width = w;
		height = h;
		data.resize(w * h);
	}

	std::span<T> operator[](size_t row) {
		return { &data[row * width], width };
	}

	std::span<const T> operator[](size_t row) const {
		return { &data[row * width], width };
	}

	auto rows() {
		return std::views::iota(size_t{}, getHeight()) |
			std::views::transform([this](size_t i) { return this->operator[](i); });
	}

	auto rows() const {
		return std::views::iota(size_t{}, getHeight()) |
			std::views::transform([this](size_t i) { return this->operator[](i);  });
	}

	T& at(Vector2 p) {
		return data[pointToIndex(p)];
	}

	const T& at(Vector2 p) const {
		return data[pointToIndex(p)];
	}

	std::span<T> span() { return data; }
	
	std::span<const T> span() const { return data; }

	size_t getWidth() const { return width; }

	size_t getHeight() const { return height; }

	size_t getSize() const { return data.size(); }

	bool inBounds(Vector2 p) const {
		return p.x >= 0 && p.x < width && p.y >= 0 && p.y < height;
	}

	auto getPoints() const {
		return std::views::iota(size_t{}, getSize()) |
			   std::views::transform([this](size_t i){ return indexToPoint(i); });
	}

	std::optional<Vector2> find(const T & val) const {
		auto it = std::find(data.begin(), data.end(), val);
		if (it == data.end()) {
			return std::nullopt;
		}
		size_t i = it - data.begin();
		return indexToPoint(i);
	}

	auto findAll(const T& val) const {
		return getPoints() | 
			   std::views::filter([this, &val](Vector2 p){ return at(p) == val; });
	}

	bool match(Vector2 p, Vector2 dir, std::span<const T> elements) const {
		size_t elemIdx = 0;
		while (inBounds(p)) {
			if (at(p) != elements[elemIdx]) {
				return false;
			}
			++elemIdx;
			if (elemIdx == elements.size()) {
				return true;
			}
			p += dir;
		}
		return false;
	}

	void forEachCell(std::function<void(Vector2, const T&)> fn) const {
		for (int i = 0; i < getSize(); ++i) {
			fn(indexToPoint(i), data[i]);
		}
	}

private:

	Vector2 indexToPoint(size_t i) const {
		return Vector2{ int(i % width), int(i / width) };
	}

	size_t pointToIndex(Vector2 p) const {
		return p.y * width + p.x;
	}

	size_t width = 0;
	size_t height = 0;
	std::vector<T> data;
};

template <typename T = char>
Grid<T> parseGrid(std::istream& input, std::function<T(char)> proj = std::identity{}) {
	std::vector<T> data;
	std::string line;
	size_t height = 0;
	while (getline(input, line)) {
		++height;
		for (char c : line) {
			data.push_back(proj(c));
		}
	}
	if (height > 0) {
		size_t width = data.size() / height;
		return { width, height, std::move(data) };
	}
	return {};
}

inline void printGrid(const Grid<char> grid, std::ostream& output) {
	for (auto row : grid.rows()) {
		for (char cell : row) {
			output << cell;
		}
		output << '\n';
	}
}