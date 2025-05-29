#include <vector>
#include <sstream>
#include <string>
#include "header/parser.h"

std::vector<std::string> input_parser(const std::string& input) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(input);
	while (std::getline(tokenStream, token, ' ')) {
		if (!token.empty()) {
			tokens.push_back(token);
		}
	}
	return tokens;
}