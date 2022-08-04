#pragma once
#include<iostream>
#include<stack>
//#include "parser.h"
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
<body>   \
<nav>  \
<ul>  \
<li>  \
<a href='#'> join us hh </a>  \
<!-- this is is  is a comment -->\
</li>  \
</ul>  \
</nav>\
</body>\
";

std::string css = "\
.container{\
	margin: 100%;\
}\
.clr{\
	padding: 0;\
	margin: 0;\
}\
.main{\
	width: 1000px         ;\
	margin: 0 auto   ;\
}\
\
";

#include "cssparserr.h"
int main() {
	CssParser cparser{css};
	cparser.parse(css);
	return 0;
}
