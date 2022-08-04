#pragma once	
#include<iostream>
#include<stack>
#include<vector>
#define endl '\n'
using std::cout;

#define WHITESPACE ' ':\
case '\n':\
case '\t':\
case '\r':\
case '\f'

enum class TokenState {
	INITIAL,
	BEFORE_SELECTOR_NAME,
	SELECTOR_NAME,
	AFTER_SELECTOR_NAME,
	BEFORE_DECLARATION,
	DECLARATION
};
enum class ReturnType {
	SELECTOR,
	DECLARATION
};
typedef  std::pair<ReturnType, std::string> Token;
class CssTokenizer {
private:
	std::string currToken;
	ReturnType returnType;
	TokenState tokenState;
	bool reconsume;
	bool returnToken;
	void reset() {
		reconsume = false;
		returnToken = false;
		currToken = "";
	}
public:
	CssTokenizer()
		:returnType{ ReturnType::SELECTOR },//default
		tokenState{ TokenState::INITIAL },
		reconsume{ false },
		returnToken{ false }
	{
	}
	Token getNextToken(const std::string& str, int& currPosition) {
		reset();

		while (1) {
		char current = str[currPosition];
			switch (tokenState)
			{
			case TokenState::INITIAL:
				switch (str[currPosition]) {
				case WHITESPACE:
					//ignore allwhitespace
					break;
				case '.':
				case '#':
					currToken.push_back(str[currPosition]);
					tokenState = TokenState::BEFORE_SELECTOR_NAME;
					break;
				default:
					exit(EXIT_FAILURE);
				}
				break;
			case TokenState::BEFORE_SELECTOR_NAME:
				if (std::isdigit(str[currPosition])) {
					cout << "Selectors Name cannot start with number" << endl;
					exit(EXIT_FAILURE);
				}
				else if (str[currPosition] == '_') {
					if (str[currPosition + 1] == '_' || std::isdigit(str[currPosition])) {
						cout << "Selector name cannot start with a hypern followed by a number or hyphen." << endl;
						exit(EXIT_FAILURE);
					}

				}
				//if not error in above
				reconsume = true;
				tokenState = TokenState::SELECTOR_NAME;
				break;
			case TokenState::SELECTOR_NAME:
				switch (str[currPosition]) {
				case WHITESPACE:
					tokenState = TokenState::AFTER_SELECTOR_NAME;
					break;
				case '{':
					returnType = ReturnType::SELECTOR;
					returnToken = true;
					tokenState = TokenState::BEFORE_DECLARATION;
					break;
				default:
					if (
						std::isalpha(str[currPosition]) ||
						std::isdigit(str[currPosition]) ||
						str[currPosition] == '_' ||
						str[currPosition] == '-'
						) {
						currToken.push_back(str[currPosition]);
					}
					else {
						cout << "Illegal Character: '" << str[currPosition] << "'" << endl;
						exit(EXIT_FAILURE);
					}
				}
				break;
			case TokenState::AFTER_SELECTOR_NAME:
				switch (str[currPosition]) {
				case WHITESPACE:
					//ignore whitespaces
					break;
				case '{':
					tokenState = TokenState::DECLARATION;
					break;
				default:
					cout << "Illegal Character: '" << str[currPosition] << "'" << endl;
					exit(EXIT_FAILURE);
				}
				break;
			case TokenState::BEFORE_DECLARATION:
				switch (str[currPosition]) {
				case WHITESPACE:
					//ignore all preceding whitespace
					break;
				case '}':
					tokenState = TokenState::INITIAL;
					break;
				default:
					reconsume = true;
					tokenState = TokenState::DECLARATION;
					break;
				}
				break;
			case TokenState::DECLARATION:
				switch (str[currPosition]) {
				case WHITESPACE:
					if (!currToken.empty() && currToken.back() != ' ') {
						currToken.push_back(' ');
					}
					break;
				case ';':
					returnType = ReturnType::DECLARATION;
					returnToken = true;
					tokenState = TokenState::BEFORE_DECLARATION;
					break;
				case '}':
					cout << "Illegal Character: '" << str[currPosition] << "'" << endl;
					exit(EXIT_FAILURE);
				default:
					currToken.push_back(str[currPosition]);
				}
				break;
			}
			if (reconsume == true) {
				reconsume = false;
			}
			else {
				currPosition++;
			}
			if (returnToken) {
				return Token{ returnType,currToken };
			}
		}
	}
};
