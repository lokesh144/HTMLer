#pragma once
#include<stack>
#include<string>
#include"states.h"
#include "node.h"
#define endl '\n'
class Parser {
private:
	std::stack<TagName> stack;
	ParseState parseState;
	int currPosition;
	Document document;
	
public:
	Parser();
	void parse(const std::string& str);
	void printStackOfOpenElements();
};
