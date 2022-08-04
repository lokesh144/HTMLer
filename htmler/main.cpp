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
using std::cout;
std::string str = "\
<!DOCTYPE html>\
< html lang = \"en\">\
<head > \
<title>Page Title</title>\
</head>\
<body hello=\"hifads\">   \
<div id='in-div'>\
<span id='span a'> Span A</span>\
<span id='span b'> Span B</span>\
</div>\
</body>\
</html>\
";

//const char* str2 = "1abcdefghijklmnop 2abcdefghijklmnop 3abcdefghijklmnop 4abcdefghijklmnop 5abcdefghijklmnop 6abcdefghijklmnop 7abcdefghijklmnop 8abcdefghijklmnop 9abcdefghijklmnop 10abcdefghijklmnop 11abcdefghijklmnop 12abcdefghijklmnop 13abcdefghijklmnop";
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
	rendertree->addStyle(cssparser);


	Window window;
	RenderTree::setStatic(&window);
	int w{};
	window.getWindowSize(&w);
	rendertree->calculateLayout(w);
	window.eventloop(rendertree);

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
