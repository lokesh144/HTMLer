
#include<iostream>
#include<SDL_ttf.h>
//#include"winuser.h"
#include "window.h"
#define endl '\n'
using std::cout;

void Window::test() {
	int w, h;
	SDL_GetWindowSize(mwindow, &w, &h);
	cout << w << "  width  " << h << " height " << endl;
	font.test("Hello");
	font.test("iiiii");
	font.test("abcde");
	font.test("nepal");
	font.test("zzzzz");
	font.test("ooooo");
}

Window::Window() :
	mSCREEN_HEIGHT{ 500 },
	mSCREEN_WIDTH{ 1200 },
	mwindow{ nullptr },
	mrenderer{ nullptr },
	mtexture{ nullptr }
{
	init();
	font.loadFont("Roboto");
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
	TTF_Quit();
	SDL_Quit();
}
void Window::eventloop() {
	bool quit = false;
	SDL_Event event;
	Uint8 r{ 255 }, g{ 255 }, b{ 255 };
	int refresh{};
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
		//SDL_RenderClear(mrenderer);
		SDL_RenderPresent(mrenderer);
		refresh++;
	}
	cout << " refresh rate" << refresh << " Hz" << endl;
}

Font::Font(const std::string& name) {
}
Font::~Font() {
	cout << "closing font  " << mname << endl;
	TTF_CloseFont(mfont);
}
bool Font::loadFont(const std::string& n) {
	bool success = true;
	mfont = TTF_OpenFont(("../fonts/" + n + ".ttf").c_str(), 16);
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
