#pragma once
#include<iostream>
#include<stack>
#include "parser.h"
#include "tokenizer.h"
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
<div id=\"3\"> join us hh </div>  \
<!-- this is is  is a comment-->\
</div>  \
<p id=\"4\"> hello world</p>\
</div>\
<div id=\"5\">\
hello\
</div>\
<div id=\"6\">\
Lokesh\
</div>\
<div id=\"6\">\
Lokesh\
</div>\
<div id=\"6\">\
Lokesh\
</div>\
<div id=\"6\">\
Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh Lokesh\
</div>\
<div id=\"6\">\
Lokesh\
</div>\
</body>\
</html>\
";
#include "node.h" 
#include "rendertree.h" 
#include"window.h"
int main(int mainc, char* argv[]) {
	Document* document = new Document;
	Parser parser{ document };
	parser.parse(str);
	RenderTree* root = new RenderTree;
	root->createFromDom(document);
	Window window;
	RenderTree::setStatic(&window);
	int w{};
	window.getWindowSize(&w);
	root->calculateLayout(w);
	window.eventloop(root);
	delete root;
	delete document;
	return 0;
}
int mainm(int argc, char* argv[]) {
	//window.test();
	//window.eventloop();
	return 0;
}
