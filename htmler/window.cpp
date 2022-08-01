#include<iostream>
#include<SDL_ttf.h>
//#include"winuser.h"
#include "window.h"
#include "rendertree.h"
#define endl '\n'
using std::cout;

void Window::test() {
	int w, h;
	SDL_GetWindowSize(mwindow, &w, &h);
	cout << w << "  width  " << h << " height " << endl;
	mfont.test("Hello");
	mfont.test("iiiii");
	mfont.test("abcde");
	mfont.test("nepal");
	mfont.test("zzzzz");
	mfont.test("ooooo");
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
	bool quit = false;
	SDL_Event event;
	Uint8 r{ 255 }, g{ 255 }, b{ 255 };
	int refresh{};
	render(tree->children[0]);
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
		SDL_RenderPresent(mrenderer);
		refresh++;
	}
	cout << " refresh rate" << refresh << " Hz" << endl;
}
void Window::getWindowSize(int* w) {
	SDL_GetWindowSize(mwindow, w, nullptr);
}
std::pair<int, int> Window::getFontSize(const std::string& text) {
	return mfont.fontSize(text.c_str());
}

void Window::render(const RenderTree* tree) {
	//free texture
	if (mtexture != nullptr) {
		SDL_DestroyTexture(mtexture);
		mtexture = nullptr;
	}
	SDL_Rect parentRect = {
		tree->rect.x,
		tree->rect.y,
		tree->rect.w,
		tree->rect.h,
	};
	SDL_SetRenderDrawColor(mrenderer, 100, 100, 100, 100);
	//rendering the tree element
	SDL_RenderFillRect(mrenderer, &parentRect);
	auto isTextNode = [](Node* node) {
		if (dynamic_cast<Text*>(node))
			return true;
		else
			return false;
	};

	auto& childNodes = tree->element->childNodes;

	int i = 0;
	int sumOfSiblingsHeight{0};
	for (auto node : childNodes) {
		//iterating throught the childNode of current tree
		auto textNodeptr = dynamic_cast<Text*>(node);
		if (textNodeptr) {
			//curr Node is textNode
			auto& text = textNodeptr->getText();
			auto [width, height] = RenderTree::windowptr->getFontSize(text);
			auto pwidth = tree->rect.w;
			int linecount = static_cast<int>(width / pwidth);
			if (width > pwidth * linecount) {
				linecount++;
			}
			SDL_Color textColor = { 0,255,0 };
			SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(mfont.mfont, text.c_str(), textColor, mSCREEN_WIDTH);
			if (textSurface == nullptr) {
				cout << "cannot load text" << endl;
				exit(EXIT_FAILURE);
			}
			if (linecount > 1) {
				//cout << endl << endl;
				//cout << "==============================" << endl;
				//cout << tree->rect.h << " height: " << height << endl;
				//cout << "==============================" << endl;
				//cout << endl << endl;
			}
			SDL_Rect fillRect = {
				tree->rect.x,
				//tree->rect.y,//prev sibling ->y ++prev->sibling height
				tree->rect.y+sumOfSiblingsHeight,
				//tree->rect.w,
				width > tree->rect.w ? tree->rect.w : width,
				//height
				linecount*height
			};
			sumOfSiblingsHeight += linecount * height;
			mtexture = SDL_CreateTextureFromSurface(mrenderer, textSurface);
			SDL_RenderCopyEx(mrenderer, mtexture, NULL, &fillRect, 0.0, NULL, SDL_FLIP_NONE);
			SDL_FreeSurface(textSurface);

			SDL_RenderPresent(mrenderer);
		}
		else {
			//if not text node apply recursion
			render(tree->children[i++]);
			sumOfSiblingsHeight += tree->children[i - 1]->rect.h;
		}
	}
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
