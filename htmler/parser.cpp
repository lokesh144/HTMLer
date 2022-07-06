#include<iostream>
#include "parser.h"
#include "tokenizer.h"
using std::cout;
#define endl '\n'

Parser::Parser()
	:insertionState{ INITIAL },
	currPosition{}
{
}

/*enum tokenType {

	space,
	tab,
	linefeed,
	linefeed,
	formfeed,
	carriage_return,
	html,

};*/
std::ostream& operator<<(std::ostream& out, struct token token) {
	out << getTokenType(token.type) << ": " << token.token << " ";
	return out;
}
void Parser::parse(const std::string& str) {

	Tokenizer tokenizer;
	while (str[currPosition] != '\0') {
		struct token token = tokenizer.getNextToken(str, currPosition);
		cout << token << endl;
	}
}
