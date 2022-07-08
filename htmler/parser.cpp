#include<iostream>
#include "parser.h"
#include "tokenizer.h"
using std::cout;
#define endl '\n'

Parser::Parser()
	:parseState{ INITIAL },
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
	struct token token;
	bool reprocessToken = false;
	while (str[currPosition] != '\0') {
		if (!reprocessToken) {
			token = tokenizer.getNextToken(str, currPosition);
		}
		else {
			reprocessToken = false;
		}
		if (token.type == TAG) {
			stack.push(getTagNameAsEnum(token.token));
		}
		switch (parseState) {
		case INITIAL:
			switch (token.type) {
			case DOCTYPE:
				break;//later
			case COMMENT:
				document.appendChild(Comment token.token);
				break;
			default:
				parseState = BEFORE_HTML;
				//exit(EXIT_FAILURE);//TODO:
			}
			break;

		case BEFORE_HTML:
			switch (token.type) {
			case DOCTYPE:
				exit(EXIT_FAILURE);
				break;
			case COMMENT:
				//document.appendChild(Comment token.token);
				break;
			case TAG:
				switch (token.type) {
				case HTML:
					//TODO: create speculative mock element 
					stack.push(HTML);
					parseState = BEFORE_HEAD;
					break;
				default:
					exit(EXIT_FAILURE);
				}
				break;

			case END_TAG:
				TagName tempTagName = getTagNameAsEnum(token.token);
				if (tempTagName == HTML || tempTagName == HEAD || tempTagName == BODY
					|| tempTagName == BR) {
					//will fallthrough to default;
										//NOTE: the case END_TAG must always be just above default case
				}
				else { exit(EXIT_FAILURE); break; }
			default:
				//Create an html element whose node document is the Document object. Append it to the Document object. Put this element in the stack of open elements.
				parseState = BEFORE_HEAD;
				reprocessToken = true;
				break;

			}
		case BEFORE_HEAD:
			switch (token.type) {
			case DOCTYPE:
				exit(EXIT_FAILURE);
				break;
			case COMMENT:
				//document.appendChild(Comment token.token);
				break;
			case TAG:
				switch (getTagNameAsEnum(token.token)) {
				case HTML:
					//Process the token using the rules for the "in body" insertion mode.
					break;
				case HEAD:
					//insert html element
					//set head pointer 
					parseState = IN_HEAD;

				}
				break;
			case END_TAG:
				TagName tempTagName = getTagNameAsEnum(token.token);
				if (tempTagName == HTML || tempTagName == HEAD || tempTagName == BODY
					|| tempTagName == BR) {
					//will fallthrough to default
					//NOTE: the case END_TAG must always be just above default case
				}
				else { exit(EXIT_FAILURE); break; }
			default:
				//insert html element for head start tag token
				//set head element pointer
				parseState = IN_HEAD;
				reprocessToken = true;
			}
			break;
		case IN_HEAD:
			switch (token.type) {
			case COMMENT:
				//insert comment
				break;
			case DOCTYPE:
				exit(EXIT_FAILURE);
				break;
			case TAG:
				switch (getTagNameAsEnum(token.token)) {
				case HTML:
					// Process the token using the rules for the "in body" insertion mode.
					break;
				case BASE:
				case BASEFONT:
				case BGSOUND:
				case LINK:
					//idk ept
					//Insert an HTML element for the token. Immediately pop the current node off the stack of open elements.
					break;
				case META:
					//TODO: 
					break;
				case TITLE:
					//rcdata parsing
					break;
				case STYLE:
					//raw text parsing element
					break;
				case SCRIPT:
					exit(EXIT_FAILURE);
					break;
				case HEAD:
					exit(EXIT_FAILURE);
					break;
				}
				break;
			case END_TAG:
				TagName tempTagName = getTagNameAsEnum(token.token);
				if (tempTagName == HEAD) {
					parseState = AFTER_HEAD;
					stack.pop();//TODO: check for head to  be the last element
					break;
				}
				else if (tempTagName == BODY || tempTagName == HTML || tempTagName == BR)
				{
					//will fallthrough to default
					//NOTE: the case END_TAG must always be just above default case
				}
				else {
					exit(EXIT_FAILURE);
					break;
				}
			default:
				//pop the head from stack
				parseState = AFTER_HEAD;
				reprocessToken = false;
			}
		}
	}
	cout << token << endl;
}

void Parser::printStackOfOpenElements() {
	while (!stack.empty()) {
		cout << getTagName(stack.top()) << endl;
		stack.pop();
	}
}
