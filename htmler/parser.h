#pragma once
#include<stack>
#include<string>
#include"states.h"
#include "node.h"
#define endl '\n'
class Parser {
private:
	std::stack<Element> mstack;
	ParseState parseState;
	ParseState originalParseState;
	int currPosition;
	Document document;
	Element* headptr = nullptr;

public:
	Parser();
	void parse(const std::string& str);
	void printStackOfOpenElements();
	void  create_element_for_token(const std::string_view& tn);
	void  generic_rcdata_parse(const std::string_view& tn);
};
