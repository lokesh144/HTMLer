#pragma once
#include<SDL.h>

class Window {
	int mSCREEN_WIDTH;
	int mSCREEN_HEIGHT;
	SDL_Window* mwindow;
	SDL_Renderer* mrenderer ;
	SDL_Texture* mtexture ;
public:
	Window();
	~Window();
	bool init();
	void close();
	void eventloop();
};
