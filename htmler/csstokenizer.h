#pragma once
#include<iostream>
#include "csstoken.h"
class CssToken
{
private:
	TokenState currState;
	std::string currToken;
	//int currPosition;
	bool increase;
	bool shouldReturn;
	void reset();
	TokenType returnType;//CHARACTER by default
public:
	CssToken();
	struct token getNextToken(const std::string& str, int& currPosition);
	//~Csstoken();
	
};
