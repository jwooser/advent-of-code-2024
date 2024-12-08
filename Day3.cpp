#include "Day3.h"
#include <string>
#include <vector>

namespace {
	bool isValidParam(std::string_view str) {
		if (str.size() < 1 && str.size() > 3) {
			return false;
		}
		if (str.find_first_not_of("0123456789") != std::string::npos) {
			return false;
		}
		return true;
	}

	struct Token {
		enum Type {
			Mul,
			Do,
			Dont
		};
		Type type;
		int val;
	};

	bool isValidStrPos(size_t pos) {
		return pos != std::string::npos;
	}

	void tokenize(std::string_view line, std::vector<Token>& tokens) {
		size_t mulPos = line.find("mul(");
		size_t doPos = line.find("do()");
		size_t dontPos = line.find("don't()");
		while (isValidStrPos(mulPos) ||
			   isValidStrPos(doPos) ||
			   isValidStrPos(dontPos)) {
			if (mulPos < doPos && mulPos < dontPos) {
				size_t commaPos = line.find(",", mulPos);
				size_t rBrackPos = line.find(")", commaPos);
				if (isValidStrPos(commaPos) && isValidStrPos(rBrackPos)) {
					auto param1 = line.substr(mulPos + 4, commaPos - mulPos - 4);
					auto param2 = line.substr(commaPos + 1, rBrackPos - commaPos - 1);
					if (isValidParam(param1) && isValidParam(param2)) {
						int val = std::stoi(std::string(param1)) * std::stoi(std::string(param2));
						tokens.push_back({ Token::Mul, val });
					}
				}
				mulPos = line.find("mul(", mulPos + 4);
			}
			else if (doPos < dontPos) {
				tokens.push_back({ Token::Do });
				doPos = line.find("do()", doPos + 4);
			}
			else {
				tokens.push_back({ Token::Dont });
				dontPos = line.find("don't()", dontPos + 7);
			}
		}
	}
}

void solveDay3Part1(std::istream& input, std::ostream& output) {
	std::string line;
	std::vector<Token> tokens;
	while (getline(input, line)) {
		tokenize(line, tokens);
	}
	int totalSum = 0;
	for (auto token : tokens) {
		if (token.type == Token::Mul) {
			totalSum += token.val;
		}
	}
	output << totalSum;
}

void solveDay3Part2(std::istream& input, std::ostream& output) {
	std::string line;
	std::vector<Token> tokens;
	while (getline(input, line)) {
		tokenize(line, tokens);
	}
	int totalSum = 0;
	bool enableMul = true;
	for (auto token : tokens) {
		if (enableMul && token.type == Token::Mul) {
			totalSum += token.val;
		}
		else if (token.type == Token::Do) {
			enableMul = true;
		}
		else {
			enableMul = false;
		}
	}
	output << totalSum;
}