#include<iostream>
#include<sys/stat.h>
#include <ctime>
#include <chrono>
#include<filesystem>
#include<SDL_ttf.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<stack>
//#include"winuser.h"
#include "window.h"
#include "rendertree.h"
#include "parser.h"
#include "cssparser.h"
#include "tokenizer.h"
#include "node.h" 
#include "rendertree.h" 
#define endl '\n'
#define endl '\n'
using std::cout;

void Window::test() {
	int w, h;
	SDL_GetWindowSize(mwindow, &w, &h);
	cout << w << "  width  " << h << " height " << endl;
	//mfont.test("Hello");
	//mfont.test("iiiii");
	//mfont.test("abcde");
	//mfont.test("nepal");
	//mfont.test("zzzzz");
	//mfont.test("ooooo");
}

Window::Window() :
	mwindow{ nullptr },
	mrenderer{ nullptr },
	mtexture{ nullptr }
{
	init();
	SDL_GetWindowSize(mwindow, &mSCREEN_WIDTH, &mSCREEN_HEIGHT);
	mfont.loadFont("Roboto");
}

Window::~Window() {
	cout << "closing window" << endl;
	close();
}
bool Window::init() {
	bool	success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL couldnot be initialized\n" << SDL_GetError() << endl;
		success = false;
	}
	//creating window
	mwindow = SDL_CreateWindow("HTMLER", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mSCREEN_WIDTH, mSCREEN_HEIGHT, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_SHOWN);
	if (mwindow == NULL) {
		cout << "window couldnot be created " << SDL_GetError() << endl;
		success = false;
	}
	else {
		mrenderer = SDL_CreateRenderer(mwindow, -1, SDL_RENDERER_PRESENTVSYNC);
		if (mrenderer == NULL) {
			cout << "Couldnot create renderer " << SDL_GetError() << endl;
			success = false;
		}
		else {
			SDL_SetRenderDrawColor(mrenderer, 255, 255, 255, 255);
			if (TTF_Init() == -1) {
				cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
				exit(EXIT_FAILURE);
			}
		}
	}
	return success;
}
void Window::close() {
	//deallocate surface
	SDL_DestroyRenderer(mrenderer);
	mrenderer = nullptr;
	//destroy window
	SDL_DestroyWindow(mwindow);
	mwindow = nullptr;
	//destroy window
	//SDL_FreeSurface(gimage);
	//gimage = NULL;
	//quitting SDL subsystem
	//IMG_Quit();
}
void Window::eventloop(RenderTree* tree) {

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
	tree = rendertree;
	rendertree->createFromDom(document);

	rendertree->addRootStyle();
	rendertree->addStyle(cssparser);

	int w{};
	this->getWindowSize(&w);
	rendertree->calculateLayout(w);

	this->setRootColor();

	bool quit = false;
	SDL_Event event;
	Uint8 r{ 255 }, g{ 255 }, b{ 255 };
	int refresh{};

	render(tree->children[0]);

	using std::filesystem::last_write_time;
	using std::chrono::time_point;
	time_point htmlModTime = last_write_time("index.html");
	time_point cssModTime = last_write_time("style.css");
	int count = 0;

	while (!quit) {//main loop
		while (SDL_PollEvent(&event) != 0) {//event loop 
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_q:
					quit = true;
					break;
				}
			}
		}
		//SDL_SetRenderDrawColor(mrenderer, 255, 255, 255, 255);
		//	SDL_RenderClear(mrenderer);

		//render(tree->children[0]);
		//SDL_RenderPresent(mrenderer);
		if (!(htmlModTime == last_write_time("index.html") && cssModTime == last_write_time("style.css"))) {
			cout << "rerendering " << endl;
			htmlModTime = last_write_time("index.html");
			cssModTime = last_write_time("style.css");
			file.close();
			cssfile.close();
			file.open({ "index.html" });
			cssfile.open({ "style.css" });
			if (!file || !cssfile) {
				cout << "Cannot open file" << endl;
				exit(EXIT_FAILURE);
			}
			buffer << file.rdbuf();
			cssbuffer << cssfile.rdbuf();

			delete document;
			document = new Document;
			parser = Parser{ document };
			parser.parse(buffer.str());
			cssparser.parse(cssbuffer.str());

			delete rendertree;
			rendertree = new RenderTree;
			tree = rendertree;
			rendertree->createFromDom(document);

			rendertree->addRootStyle();
			rendertree->addStyle(cssparser);

			rendertree->calculateLayout(w);
			//render(tree->children[0]);
			SDL_RenderClear(mrenderer);
			render(tree->children[0]);

		}
		if (count > 120) {
			cout << count << endl;
			//std::time_t ht = std::chrono::system_clock::to_time_t(htmlModTime);
			//std::time_t ct = std::chrono::system_clock::to_time_t(cssModTime);
			cout << "html  " << htmlModTime.time_since_epoch().count() << "  " << last_write_time("index.html").time_since_epoch().count() << endl;
			cout << "css  " << cssModTime.time_since_epoch().count() << "  " << last_write_time("style.css").time_since_epoch().count() << endl;
			count = 0;
		}
		SDL_RenderPresent(mrenderer);
		refresh++;
		count++;
	}
	cout << " Total refresh " << refresh << " Hz" << endl;

	delete rendertree;
	delete document;
}
void Window::getWindowSize(int* w) {
	SDL_GetWindowSize(mwindow, w, nullptr);
}

std::pair<int, int> Window::getFontSize(const std::string& text) {
	return mfont.fontSize(text.c_str());
}

/*
To render an element first render it and then render its child
To render itself we require the rect it convers
the x, y, w and h value of the rect is already calculated
iterate through the child  nodes :
if child node is text node find its x,y width and height and render it
if child node is element node call render(rendertree)
*/
void Window::render(const RenderTree* tree) {
	//free texture
	if (mtexture != nullptr) {
		SDL_DestroyTexture(mtexture);
		mtexture = nullptr;
	}
	//set draw color to the background color of the element

	SDL_Color bgColor(tree->getBgColor());
	SDL_SetRenderDrawColor(mrenderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_RenderFillRect(mrenderer, &tree->rect);

	auto isTextNode = [](Node* node) {
		if (dynamic_cast<Text*>(node))
			return true;
		else
			return false;
	};

	auto& childNodes = tree->element->childNodes;

	int i = 0;
	int sumOfSiblingsHeight{ 0 };
	for (auto node : childNodes) {
		//iterating throught the childNode of current tree
		//calculate the width and height of line of the required text
		//get Parent width(assume block level)
		//this->render box() and find the content width 
		//now calculate the content height 
		//then calculate remaining
		auto textNodeptr = dynamic_cast<Text*>(node);
		if (textNodeptr) {
			//curr Node is textNode
			auto& text = textNodeptr->getText();
			auto [width, height] = RenderTree::windowptr->getFontSize(text);
			int textwidth = tree->rect.w -
				tree->styles->mpadding.left.toPixel() -
				tree->styles->mpadding.right.toPixel() -
				tree->styles->mborder.left.toPixel() -
				tree->styles->mborder.right.toPixel();
			int linecount = static_cast<int>(width / textwidth);
			if (width > textwidth * linecount) {
				linecount++;
			}
			SDL_Color textColor{ tree->getColor() };
			SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(mfont.mfont, text.c_str(), textColor, textwidth);

			//cout<<textSurface->clip_rect.
			if (textSurface == nullptr) {
				cout << "cannot load text" << endl;
				exit(EXIT_FAILURE);
			}

			SDL_Rect textRect = {
				tree->rect.x + tree->styles->mpadding.left.toPixel() + tree->styles->mborder.left.toPixel(),
				tree->rect.y + tree->styles->mpadding.top.toPixel() + tree->styles->mborder.top.toPixel(),
				width < textwidth ? width : textwidth,
				linecount* height
			};

			/*
			The x and y for the text node will be its containing blocks x,y - its padding and border in corr direction
			*/
			this->renderBox(tree);
			//sumOfSiblingsHeight += linecount * height;
			mtexture = SDL_CreateTextureFromSurface(mrenderer, textSurface);
			SDL_RenderCopyEx(mrenderer, mtexture, NULL, &textRect, 0.0, NULL, SDL_FLIP_NONE);
			SDL_FreeSurface(textSurface);

		}
		else {
			//if not text node apply recursion
			render(tree->children[i++]);
			//sumOfSiblingsHeight += tree->children[i - 1]->rect.h;
		}
	}
}

void Window::renderBox(const RenderTree* tree) {
	constexpr int fontSize = 18;
	struct FourRect {
		SDL_Rect top, right, bottom, left;
	};
	struct FourRect margin, padding, border;
	SDL_Rect content;
	//assume border-box for now
	//no margin for now
	border.left.x = tree->rect.x;
	border.left.y = tree->rect.y;
	border.left.w = tree->styles->mborder.left.toPixel();
	border.left.h = tree->rect.h;

	border.right.x = tree->rect.x + tree->rect.w - tree->styles->mborder.right.toPixel();
	border.right.y = tree->rect.y;
	border.right.w = tree->styles->mborder.right.toPixel();
	border.right.h = tree->rect.h;

	border.top.x = tree->rect.x;
	border.top.y = tree->rect.y;
	border.top.w = tree->rect.w;
	border.top.h = tree->styles->mborder.top.toPixel();

	border.bottom.x = tree->rect.x;
	border.bottom.y = tree->rect.y + tree->rect.h - tree->styles->mborder.bottom.toPixel();
	border.bottom.w = tree->rect.w;
	border.bottom.h = tree->styles->mborder.bottom.toPixel();

	padding.left.x = tree->rect.x + border.left.w;
	padding.left.y = border.top.y + border.top.h;
	padding.left.w = tree->styles->mpadding.left.toPixel();
	padding.left.h = tree->rect.h - border.top.h - border.bottom.h;

	padding.right.x = border.right.x - tree->styles->mpadding.right.toPixel();
	padding.right.y = border.top.y + border.top.h;
	padding.right.w = tree->styles->mpadding.right.toPixel();
	padding.right.h = tree->rect.h - border.top.h - border.bottom.h;



	padding.top.x = padding.left.x;
	padding.top.y = padding.right.y;
	padding.top.w = border.top.w - border.left.w - border.right.w;
	padding.top.h = tree->styles->mpadding.top.toPixel();

	padding.bottom.x = padding.left.x;
	padding.bottom.y = border.bottom.y - tree->styles->mpadding.bottom.toPixel();
	padding.bottom.w = padding.top.w;
	padding.bottom.h = tree->styles->mpadding.bottom.toPixel();

	content.x = padding.left.x + padding.left.w;
	content.y = padding.top.y + padding.top.h;
	content.w = padding.top.w - padding.left.w - padding.right.w;
	content.h = padding.left.h - padding.top.h - padding.bottom.h;


	//SDL_SetRenderDrawColor(mrenderer, 0, 0, 255, 100);
	/*
	if (padding.top.h != 0)
		SDL_RenderDrawRect(mrenderer, &padding.top);
	if (padding.right.w != 0)
		SDL_RenderDrawRect(mrenderer, &padding.right);
	if (padding.bottom.h != 0)
		SDL_RenderDrawRect(mrenderer, &padding.bottom);
	if (padding.left.w != 0)
		SDL_RenderDrawRect(mrenderer, &padding.left);
	*/

	//if border-color apply border color
	//else border-color=text color
	if (border.right.w != 0) {
		SDL_SetRenderDrawColor(mrenderer, tree->styles->mborder.right.borderColor.r, tree->styles->mborder.right.borderColor.g, tree->styles->mborder.right.borderColor.b, 255);
		SDL_RenderFillRect(mrenderer, &border.right);
	}
	if (border.top.h != 0) {
		SDL_SetRenderDrawColor(mrenderer, tree->styles->mborder.top.borderColor.r, tree->styles->mborder.top.borderColor.g, tree->styles->mborder.top.borderColor.b, 255);
		SDL_RenderFillRect(mrenderer, &border.top);
	}
	if (border.left.w != 0) {
		SDL_SetRenderDrawColor(mrenderer, tree->styles->mborder.left.borderColor.r, tree->styles->mborder.left.borderColor.g, tree->styles->mborder.left.borderColor.b, 255);
		SDL_RenderFillRect(mrenderer, &border.left);
	}
	if (border.bottom.h != 0) {
		SDL_SetRenderDrawColor(mrenderer, tree->styles->mborder.bottom.borderColor.r, tree->styles->mborder.bottom.borderColor.g, tree->styles->mborder.bottom.borderColor.b, 255);
		SDL_RenderFillRect(mrenderer, &border.bottom);
	}

	//SDL_SetRenderDrawColor(mrenderer, 100, 100, 100, 100);
}


void Window::setRootColor() {
	SDL_SetRenderDrawColor(mrenderer, 255, 255, 255, 255);
}


/*===================================================================*/
/**************************** FONT CLASS *****************************/
/*===================================================================*/
Font::Font(const std::string& name) {
}
Font::~Font() {
	TTF_CloseFont(mfont);
	cout << "closing font  " << mname << endl;
	TTF_Quit();
	SDL_Quit();
	//leave it here for now//warning
}
bool Font::loadFont(const std::string& n) {
	bool success = true;
	mfont = TTF_OpenFont(("../fonts/" + n + ".ttf").c_str(), 18);
	if (mfont == nullptr) {
		cout << "couldnot load font: " << TTF_GetError() << endl;
		success = false;
	}
	return success;
}
void Font::test(const std::string& t) {
	int w{}, h{};
	TTF_SizeText(mfont, t.c_str(), &w, &h);
	cout << t << "  w " << w << " h " << h << endl;

}

std::pair<int, int> Font::fontSize(const char* text) {
	int w, h;
	if (TTF_SizeText(mfont, text, &w, &h) == 0) {
		return { w,h };
	}
	else {
		cout << "Error calculating text width and height: " << TTF_GetError() << endl;
		exit(EXIT_FAILURE);
	};
}


//TODO: add previous sibling whil initializing node
//TODO: active formatting elements
