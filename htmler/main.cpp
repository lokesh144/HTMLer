#pragma once
#include<iostream>
#include<stack>
#include "parser.h"
#define endl '\n'
using std::cout;
/*
<a href='#'> Home </a>  \
</li>  \
<li>  \
<a href='#'> About </a>  \
</li>  \
<li>  \
<a href='#'> Contact </a>  \
</li>  \
<li> <a href='#'> Terms of use </a>  \
</li>  \
<li>  \
*/
std::string str = "\
<html>\
<head > \
<title>Page Title</title>\
</head>\
<body>   \
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

/*
html
----head
--------title
----body
--------nav
------------ul
----------------li
--------------------a
--------div
*/

#include "node.h" 
int main() {
	Document* document =new Document;
	Parser parser{document};
	parser.parse(str);
	delete document;
	return 0;
}
