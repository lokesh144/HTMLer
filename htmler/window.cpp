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
			//SDL_SetRenderDrawColor(mrenderer, 255, 255, 255, 255);
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
	//SDL_RenderPresent(mrenderer);
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
			auto pwidth = tree->rect.w;
			int linecount = static_cast<int>(width / pwidth);
			if (width > pwidth * linecount) {
				linecount++;
			}
			//tree.getColor();
			SDL_Color textColor = { 0,255,0 };
			SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(mfont.mfont, text.c_str(), textColor, mSCREEN_WIDTH);
			if (textSurface == nullptr) {
				cout << "cannot load text" << endl;
				exit(EXIT_FAILURE);
			}

			SDL_Rect fillRect = {
				tree->rect.x,
				tree->rect.y + sumOfSiblingsHeight,
				width > tree->rect.w ? tree->rect.w : width,
				linecount * height
			};
			if (tree->element->attributes.size() != 0) {
				if (tree->element->attributes[0].getValue() == "imp") {
					tree->styles->mpadding.left = { 100,styles::LengthType::PIXEL };
					tree->styles->mpadding.top = { 10,styles::LengthType::PIXEL };
			tree->styles->mpadding.bottom = { 10,styles::LengthType::PIXEL };
					tree->styles->mpadding.right = { 100,styles::LengthType::PIXEL };
					this->renderBox(tree, fillRect);
				}
			}

			sumOfSiblingsHeight += linecount * height;
			//sumOfSiblingsHeight += linecount * height + tree->styles->mpadding.top.toPixel() + tree->styles->mpadding.bottom.toPixel() ;

			mtexture = SDL_CreateTextureFromSurface(mrenderer, textSurface);
			SDL_RenderCopyEx(mrenderer, mtexture, NULL, &fillRect, 0.0, NULL, SDL_FLIP_NONE);
			SDL_FreeSurface(textSurface);

		}
		else {
			//if not text node apply recursion
			render(tree->children[i++]);
			sumOfSiblingsHeight += tree->children[i - 1]->rect.h;
		}
	}
}

void Window::renderBox(const RenderTree* tree, SDL_Rect& box) {
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
	border.left.w = tree->styles->mborder.left.borderWidth.toPixel();
	border.left.h = tree->rect.h;

	border.right.x = tree->rect.x + tree->rect.w - tree->styles->mborder.right.borderWidth.toPixel();
	border.right.y = tree->rect.y;
	border.right.w = tree->styles->mborder.right.borderWidth.toPixel();
	border.right.h = tree->rect.h;

	border.top.x = tree->rect.x;
	border.top.y = tree->rect.y;
	border.top.w = tree->rect.w;
	border.top.h = tree->styles->mborder.top.borderWidth.toPixel();

	border.bottom.x = tree->rect.x;
	border.bottom.y = tree->rect.y + tree->rect.h - tree->styles->mborder.bottom.borderWidth.toPixel();
	border.bottom.w = tree->rect.w;
	border.bottom.h = tree->styles->mborder.bottom.borderWidth.toPixel();

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


	SDL_SetRenderDrawColor(mrenderer, 0, 0, 255, 100);
	if (padding.top.h != 0)
		SDL_RenderDrawRect(mrenderer, &padding.top);
	if (padding.right.w != 0)
		SDL_RenderDrawRect(mrenderer, &padding.right);
	if (padding.bottom.h != 0)
		SDL_RenderDrawRect(mrenderer, &padding.bottom);
	if (padding.left.w != 0)
		SDL_RenderDrawRect(mrenderer, &padding.left);

	//if border-color apply border color
	//else border-color=text color
	SDL_SetRenderDrawColor(mrenderer, 255, 0, 0, 100);
	if (border.top.h != 0)
		SDL_RenderDrawRect(mrenderer, &border.top);
	if (border.right.w != 0)
		SDL_RenderDrawRect(mrenderer, &border.right);
	if (border.bottom.h != 0)
		SDL_RenderDrawRect(mrenderer, &border.bottom);
	if (border.left.w != 0)
		SDL_RenderDrawRect(mrenderer, &border.left);


	box = {
		content.x,
		content.y,
		box.w,
		box.h
	};

	box = content;
	SDL_SetRenderDrawColor(mrenderer, 100, 100, 100, 100);
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
