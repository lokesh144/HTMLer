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
<Body>   \
<nav>  \
<ul>  \
<li>  \
<a href='#'> Join Us </a>  \
<!-- this  is a comment -->\
</li>  \
</ul>  \
</nav>  ";


int main() {
	Parser parser;
	parser.parse(str);
	return 0;
}
