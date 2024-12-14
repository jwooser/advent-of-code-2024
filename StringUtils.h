#pragma once

#include <string>
#include <vector>
#include <functional>

template<typename T = std::string>
std::vector<T> split(const std::string& string, 
					 const std::string& delim, 
					 std::function<T(const std::string&)> projection = std::identity{}) {
	std::vector<T> result;
	size_t curr = 0;
	while (true) {
		size_t next = string.find(delim, curr);
		if (next == std::string::npos) {
			result.push_back(projection(string.substr(curr)));
			return result;
		}
		result.push_back(projection(string.substr(curr, next - curr)));
		curr = next + delim.size();
	}
}