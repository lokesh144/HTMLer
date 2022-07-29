
#include<iostream>
//#include"winuser.h"
#include "window.h"
#define endl '\n'
using std::cout;

Window::Window() :
	mSCREEN_HEIGHT{ 500 },
	mSCREEN_WIDTH{ 1200 },
	mwindow{ nullptr },
	mrenderer{ nullptr },
	mtexture{ nullptr }
{

}
Window::~Window() {
	close();
	cout << "closing" << endl;
}
bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL couldnot be initialized\n" << SDL_GetError();
		return false;
	}
	//creating window
	mwindow = SDL_CreateWindow("HTMLER", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mSCREEN_WIDTH, mSCREEN_HEIGHT, SDL_WINDOW_MAXIMIZED|SDL_WINDOW_SHOWN);
	if (mwindow == NULL) {
		cout << "winkdow couldnot be created";
		return false;
	}

	mrenderer = SDL_CreateRenderer(mwindow, -1, SDL_RENDERER_PRESENTVSYNC);
	if (mrenderer == NULL) {
		cout << "Couldnot create renderer " << SDL_GetError() << endl;
		return false;
	}

	SDL_SetRenderDrawColor(mrenderer, 255, 255, 255, 255);
	return true;
}
void Window::close() {
	//deallocate surface
	SDL_DestroyRenderer(mrenderer);
	mrenderer = NULL;
	//destroy window
	SDL_DestroyWindow(mwindow);
	mwindow = NULL;
	//destroy window
	//SDL_FreeSurface(gimage);
	//gimage = NULL;
	//quitting SDL subsystem
	//IMG_Quit();
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
		SDL_SetRenderDrawColor(mrenderer, 255, 255, 255, 255);
		SDL_RenderClear(mrenderer);

		SDL_RenderPresent(mrenderer);
		refresh++;
	}
	cout <<" refresh rate" << refresh <<  " Hz"<<endl;
}
