#pragma once
#include<stack>
#include<string>
#include"states.h"
#define endl '\n'
class Parser {
private:
	std::stack<TagName> stack;
	ParseState insertionState;
	int currPosition;
	
public:
	Parser();
	void parse(const std::string& str);
};
