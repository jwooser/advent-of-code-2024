#pragma once

#include <istream>
#include <optional>
#include <span>
#include <string>
#include <vector>
#include <ranges>
#include <functional>
#include "Vector2.h"

template <typename T>
class Grid {
public:
	Grid() { };
	
	Grid(size_t w, size_t h)
		: w{ w }, h{ h } {
		data.resize(w * h);
	}

	Grid(size_t w, size_t h, const T& val)
		: w{ w }, h{ h } {
		data.resize(w * h, val);
	}

	Grid(size_t w, size_t h, std::vector<T> d)
		: w{ w }, h{ h }, data{ std::move(d) } {
		data.resize(w * h);
	}

	void resize(size_t w, size_t h) {
		w = w;
		h = h;
		data.resize(w * h);
	}

	std::span<T> operator[](size_t row) {
		return { &data[row * w], w };
	}

	std::span<const T> operator[](size_t row) const {
		return { &data[row * w], w };
	}

	auto rows() {
		return std::views::iota(size_t{}, height()) |
			std::views::transform([this](size_t i) { return this->operator[](i); });
	}

	auto rows() const {
		return std::views::iota(size_t{}, height()) |
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

	size_t width() const { return w; }

	size_t height() const { return h; }

	size_t size() const { return data.size(); }

	bool inBounds(Vector2 p) const {
		return p.x >= 0 && p.x < w && p.y >= 0 && p.y < h;
	}

	auto points() const {
		return std::views::iota(size_t{}, size()) |
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
		return points() | 
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
		for (int i = 0; i < size(); ++i) {
			fn(indexToPoint(i), data[i]);
		}
	}

	Vector2 indexToPoint(size_t i) const {
		return Vector2{ int(i % w), int(i / w) };
	}

	size_t pointToIndex(Vector2 p) const {
		return p.y * w + p.x;
	}

private:

	size_t w = 0;
	size_t h = 0;
	std::vector<T> data;
};

template <typename T = char, typename Proj = std::identity>
Grid<T> parseGrid(std::istream& input, Proj proj = {}) {
	std::vector<T> data;
	std::string line;
	size_t height = 0;
	while (getline(input, line)) {
		if (line == "") break;
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

template <typename T = char, typename Proj = std::identity>
void printGrid(const Grid<T>& grid, 
			   std::ostream& output, 
			   Proj proj = {}) {
	for (auto row : grid.rows()) {
		for (const T& cell : row) {
			output << proj(cell);
		}
		output << '\n';
	}
}