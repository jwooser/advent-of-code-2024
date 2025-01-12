#pragma once

#include <array>
#include <format>
#include <ranges>
#include <stdexcept>

// Convenience methods for creating mappings between enums and chars

template<typename EnumType, char... Values>
EnumType charToEnum(char value) {
	constexpr std::array<char, sizeof...(Values)> arr{ Values... };
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] == value) {
			return static_cast<EnumType>(i);
		}
	}
	throw std::invalid_argument(std::format("Value is not allowed: {}", value));
}

template<typename EnumType, char... Values>
char enumToChar(EnumType e) {
	constexpr std::array<char, sizeof...(Values)> arr{ Values... };
	int i = static_cast<int>(e);
	if (i >= arr.size()) {
		throw std::invalid_argument(std::format("Enum value is out of range: {}", i));
	}
	return arr[i];
}