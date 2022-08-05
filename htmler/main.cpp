#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<stack>
#include "parser.h"
#include "cssparser.h"
#include "tokenizer.h"
#include "node.h" 
#include "rendertree.h" 
#include"window.h"
#define endl '\n'

int main(int mainc, char* argv[]) {
	std::ifstream file{ "index.html" };
	std::ifstream cssfile{ "style.css" };
	if (!file || !cssfile) {
		cout << "Cannot open file" << endl;
		exit(EXIT_FAILURE);
	}
	std::stringstream buffer;
	std::stringstream cssbuffer;
	buffer << file.rdbuf();
	cssbuffer << cssfile.rdbuf();

	Document* document = new Document;
	Parser parser{ document };
	parser.parse(buffer.str());
	CssParser cssparser{ };
	cssparser.parse(cssbuffer.str());

	RenderTree* rendertree = new RenderTree;
	rendertree->createFromDom(document);


	rendertree->addRootStyle();
	rendertree->addStyle(cssparser);

	Window window;
	RenderTree::setStatic(&window);
	int w{};
	window.getWindowSize(&w);
	rendertree->calculateLayout(w);

	window.setRootColor();
	window.eventloop(rendertree);
	//	SDL_Delay(100000);

	//auto hi = window.getFontSize(str2);
	//cout << "=======================================" << endl;
	//cout << "width " << hi.first << endl;
	//cout << "=======================================" << endl;
	delete rendertree;
	delete document;
	return 0;
}
int mainm(int argc, char* argv[]) {
	//window.test();
	//window.eventloop();
	return 0;
}
