#pragma once	
#include"csstokenizer.h"
#include<iostream>
#define endl '\n'
using std::cout;


enum class Property {
	COLOR,
	MARGIN,
	MARGIN_TOP,
	MARGIN_RIGHT,
	MARGIN_BOTTOM,
	MARGIN_LEFT,
	BORDER,
	BORDER_TOP,
	BORDER_RIGHT,
	BORDER_BOTTOM,
	BORDER_LEFT,
	PADDING,
	PADDING_TOP,
	PADDING_RIGHT,
	PADDING_BOTTOM,
	PADDING_LEFT,
	WIDTH,
	UNKNOWN
};
struct Declaration {
	Property property;
	std::string value;
};
typedef std::vector<Declaration> DeclarationList;
typedef std::string Selector;
typedef  std::pair<Selector, DeclarationList>CSSRule;
class CssParser {
private:
	int currPosition;
	std::vector<CSSRule>cssRules;
	inline void ignoreWhiteSpace(const std::string& str, int& pos);
public:
	CssParser();
	void parse(const std::string& str);
	Declaration parsePropValue(const std::string& propValue);
};
