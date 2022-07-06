#pragma once
#include "states.h"
#include<string_view>

class Tokenizer {
private:
	tokenState currState;
	std::string currToken;
	//int currPosition;
	bool increase;
	bool shouldReturn;
	void reset();

public:
	Tokenizer();
	std::string_view getNextToken(const std::string& str,int& currPosition);

};
