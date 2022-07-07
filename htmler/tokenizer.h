#pragma once
#include "states.h"
#include<string_view>

class Tokenizer {
private:
	TokenState currState;
	std::string currToken;
	//int currPosition;
	bool increase;
	bool shouldReturn;
	void reset();
	TokenType returnType;//CHARACTER by default


public:
	Tokenizer();
	struct token getNextToken(const std::string& str, int& currPosition);

};
