
#pragma once
#include<iostream>
#include "csstokenizer.h"
#define endl '\n'

CssToken::CssToken()
	:currState{ CHARACTER },
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
		
			switch (str[currPosition])
			{
			default:
				break;
			}
		case'/': {
		case '*': {
			cu
		}
		}
		default:
			break;
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
