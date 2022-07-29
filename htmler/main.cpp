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
int mmain() {
	Document* document =new Document;
	Parser parser{document};
	parser.parse(str);
	delete document;
	return 0;
}

#include"window.h"
int main(int argc,char* argv[]) {
	Window window;
	window.init();
	window.eventloop();
	return 0;
}
