#include <vector>
#include <sstream>
#include <string>
#include "header/parser.h"
using namespace std;

vector<string> input_parser(const string& input) {
	vector<std::string> tokens;
	string token;
	istringstream tokenStream(input);
	while (std::getline(tokenStream, token, ' ')) {
		if (!token.empty()) {
			tokens.push_back(token);
		}
	}
	return tokens;
}