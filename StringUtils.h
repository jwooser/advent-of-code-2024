#pragma once

#include <string>s
#include <vector>
#include <functional>
#include <cstdlib>

inline bool tryStrToLong(const std::string& str, long& val, int base = 10) {
	errno = 0;
	char* endptr;
	val = std::strtol(str.c_str(), &endptr, base);
	if (errno == ERANGE || endptr == str.c_str()) {
		return false;
	}
}

inline bool tryStrToLongLong(const std::string& str, long long& out, int base = 10) {
	errno = 0;
	char* endptr;
	out = std::strtoll(str.c_str(), &endptr, base);
	if (errno == ERANGE || endptr != str.c_str() + str.size()) {
		return false;
	}
}

inline bool tryConcat(long long left, long long right, long long& out) {
	std::string leftStr = std::to_string(left);
	std::string rightStr = std::to_string(right);
	std::string concat = leftStr + rightStr;
	return tryStrToLongLong(concat, out);
}

inline int stoiFunc(const std::string& str) {
	return std::stoi(str);
};

inline long stolFunc(const std::string& str) {
	return std::stol(str);
};

inline long long stollFunc(const std::string& str) {
	return std::stoll(str);
};

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