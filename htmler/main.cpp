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

	Window window;
	RenderTree::setStatic(&window);
	window.eventloop(nullptr);
	//	SDL_Delay(100000);

	//auto hi = window.getFontSize(str2);
	//cout << "=======================================" << endl;
	//cout << "width " << hi.first << endl;
	//cout << "=======================================" << endl;
	return 0;
}
int mainm(int argc, char* argv[]) {
	//window.test();
	//window.eventloop();
	return 0;
}
