#pragma once
#include<iostream>
#include<stack>
#include "parser.h"
#include "tokenizer.h"
#define endl '\n'
using std::cout;
std::string str = "\
<html>\
<head > \
<title>Page Title</title>\
</head>\
<body hello=\"hifads\">   \
<div>  \
p<div>  \
<div> join us hh </div>  \
<!-- this is is  is a comment-->\
</div>  \
<p> hello world</p>\
</div>\
<div>\
hello\
</div>\
</body>\
</html>\
";

#include "node.h" 
#include "rendertree.h" 
int main(int mainc, char* argv[]) {
	Document* document =new Document;
	Parser parser{document};
	parser.parse(str);
	RenderTree* root=new RenderTree;
	root->createFromDom(document);
	delete root;
	delete document;
	return 0;
}

#include"window.h"
int mainm(int argc,char* argv[]) {
	Window window;
	window.test();
	//window.eventloop();
	return 0;
}
