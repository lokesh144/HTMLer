#pragma once
#include<iostream>
#include "csstoken.h"
class Csstoken
{
private:
	TokenType currState;
	std::string currToken;
	//int currPosition;
	bool increase;
	bool shouldReturn;
	void reset();
	TokenType returnType;//CHARACTER by default
public:
	Csstoken();
	~Csstoken();
};
