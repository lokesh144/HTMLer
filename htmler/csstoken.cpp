
#pragma once
#include<iostream>
#include "csstokenizer.h"
#define endl '\n'

CssToken::CssToken()
	:currState{ INIT },
	currToken{ "" },
	returnType{ DATA },

	//currPosition{ 0 },
	shouldReturn{ false },
	increase{ true }{
}

void CssToken::reset() {
	increase = true;
	currToken = "";
	shouldReturn = false;
	returnType = DATA;//default
}
struct token CssToken::getNextToken(const std::string& str, int& currPosition) {
	while (true)
	{
		reset();
		switch (currState)
		{
		case INIT:
			switch (str[currPosition])
				case '/':
					currState = INIT;
					shouldReturn = true;
					increase = true;
					switch (str[currPosition])
					{
					case '*':
						currState = COMMENT_START;
						shouldReturn = false;
						increase = true;
						switch (str[currPosition])
						{
						case '*':
							increase = true;
							case '\\':
								currState = COMMENT_END;
								shouldReturn = true;
								increase = true;

						default:
							increase = true;
							shouldReturn = false;
							break;
						}
					default:
						break;
					}
					break;

				case ' ':
					currState = WHITESPACE;
					shouldReturn = false;
					increase = true;
				case '.':
				currState:CLASS_NAME_BEGIN;
				shouldReturn:true;
				increase: true;



			
			default:
				break;
			}
		case'/': {
		case '*': {
		
		}
		}
		//default:
			//break;
		}
		if (increase) {
			currPosition++;
		}
		else {
			increase = true;
		}
		if (shouldReturn) {
			return (token{ .type = returnType,.token = currToken });
		}
	}
}
