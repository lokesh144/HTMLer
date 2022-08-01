#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<stack>
#include "parser.h"
#include "tokenizer.h"
#include "node.h" 
#include "rendertree.h" 
#include"window.h"
#define endl '\n'
using std::cout;
//<!DOCTYPE html>
std::string str = "\
<html lang=\"en\">\
<head > \
<title>Page Title</title>\
</head>\
<body hello=\"hifads\">   \
<div id=\"1\">  \
p<div id=\"2\">  \
<div id=\"3\">  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh join us hh </div>  \
<!-- this is is  is a comment-->\
</div>  \
 Welcome to the internet\
<p id=\"4\"> hello world</p>\
</div>\
<div id=\"6\">\
 join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh  join us hh join us hh \
</div>\
<div id=\"7\">\
Lokesh\
</div>\
</body>\
</html>\
";

//const char* str2 = "1abcdefghijklmnop 2abcdefghijklmnop 3abcdefghijklmnop 4abcdefghijklmnop 5abcdefghijklmnop 6abcdefghijklmnop 7abcdefghijklmnop 8abcdefghijklmnop 9abcdefghijklmnop 10abcdefghijklmnop 11abcdefghijklmnop 12abcdefghijklmnop 13abcdefghijklmnop";
int main(int mainc, char* argv[]) {
	//std::ifstream file{ "index.html" };
	//std::stringstream buffer;
	//buffer << file.rdbuf();
	Document* document = new Document;
	Parser parser{ document };
	//parser.parse(buffer.str());
	parser.parse(str);
	RenderTree* root = new RenderTree;
	root->createFromDom(document);
	Window window;
	RenderTree::setStatic(&window);
	int w{};
	window.getWindowSize(&w);
	root->calculateLayout(w);
	window.eventloop(root);
	//auto hi = window.getFontSize(str2);
	//cout << "=======================================" << endl;
	//cout << "width " << hi.first << endl;
	//cout << "=======================================" << endl;
	delete root;
	delete document;
	return 0;
}
int mainm(int argc, char* argv[]) {
	//window.test();
	//window.eventloop();
	return 0;
}
