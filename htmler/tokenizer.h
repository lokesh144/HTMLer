#pragma once
#include<string>
#include<vector>
#include<string>
#include "states.h"
#include "elements.h"
#include "node.h"

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
	struct Token getNextToken(const std::string& str, int& currPosition);

};

enum class TTstate {
	TAG_NAME,
	BEFORE_ATTRIBUTE_NAME,
	ATTRIBUTE_NAME,
	BEFORE_ATTRIBUTE_VALUE,
	AFTER_ATTRIBUTE_NAME,
	ATTRIBUTE_VALUE_DOUBLE_QUOTE,
	ATTRIBUTE_VALUE_SINGLE_QUOTE,
	ATTRIBUTE_VALUE_UNQUOTED,
	AFTER_ATTRIBUTE_VALUE_QUOTED,
};

class TagTokenizer {
private:
	TagName tagName;
	std::vector<Attribute> attributes;
public:
	TagTokenizer(const std::string& str) {
		int currPosition = 0;
		bool reconsume = false;
		TTstate ttstate = TTstate::TAG_NAME;
		while (str[currPosition]) {
			if (reconsume) {
				reconsume = false;
			}
			else {
				currPosition++;
			}
		}

	}
};
