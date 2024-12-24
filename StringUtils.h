#pragma once

#include <string>
#include <vector>
#include <functional>
#include <cstdlib>
#include <cstdint>

inline bool tryStrToInt(const std::string& str, long& val, int base = 10) {
	errno = 0;
	char* endptr;
	val = std::strtol(str.c_str(), &endptr, base);
	if (errno == ERANGE || endptr == str.c_str()) {
		return false;
	}
	return true;
}

inline bool tryStrToInt64(const std::string& str, int64_t& out, int base = 10) {
	errno = 0;
	char* endptr;
	out = std::strtoll(str.c_str(), &endptr, base);
	if (errno == ERANGE || endptr != str.c_str() + str.size()) {
		return false;
	}
	return true;
}

inline bool tryConcat(int64_t left, int64_t right, int64_t& out) {
	std::string leftStr = std::to_string(left);
	std::string rightStr = std::to_string(right);
	std::string concat = leftStr + rightStr;
	return tryStrToInt64(concat, out);
}

inline int stoiFunc(const std::string& str) {
	return std::stoi(str);
};

inline int64_t stollFunc(const std::string& str) {
	return std::stoll(str);
};

inline int charToInt(char c) {
	return c - '0';
}

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

inline int parseNumber(const std::string& string, const std::string& descriptor) {
	size_t idx = string.find(descriptor);
	idx += descriptor.size();
	return std::stoi(string.substr(idx));
}