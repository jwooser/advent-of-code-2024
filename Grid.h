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
		: width{ w }, height{ h } { data.resize(w * h); }

	Grid(size_t w, size_t h, std::vector<T> d) 
		: width{ w }, height{ h }, data{ std::move(d) } { data.resize(w * h); }

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

	T& at(Vector2 pos) {
		return data[pos.y * width + pos.x];
	}

	const T& at(Vector2 pos) const {
		return data[pos.y * width + pos.x];
	}

	std::span<T> span() { return data; }
	
	std::span<const T> span() const { return data; }

	size_t getWidth() const { return width; }

	size_t getHeight() const { return height; }

	bool inBounds(Vector2 pos) const {
		return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
	}

	std::optional<Vector2> find(const T & val) const {
		auto it = std::find(data.begin(), data.end(), val);
		if (it == data.end()) {
			return std::nullopt;
		}
		size_t i = it - data.begin();
		return Vector2{ int(i % width), int(i / width) };
	}

	bool match(Vector2 pos, Vector2 dir, std::span<const T> elements) const {
		size_t elemIdx = 0;
		while (inBounds(pos)) {
			if (at(pos) != elements[elemIdx]) {
				return false;
			}
			++elemIdx;
			if (elemIdx == elements.size()) {
				return true;
			}
			pos += dir;
		}
		return false;
	}

private:
	size_t width = 0;
	size_t height = 0;
	std::vector<T> data;
};

template <typename T = char>
Grid<T> parseGrid(std::istream & input, std::function<T(char)> proj = std::identity{}) {
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