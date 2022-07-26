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
<nav>  \
<ul>  \
<li>  \
<a> join us hh </a>  \
<!-- this is is  is a comment-->\
</li>  \
</ul>  \
</nav>\
</body>\
</html>\
";


int main() {
	Parser parser;
	parser.parse(str);
	return 0;
}
