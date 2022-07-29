#pragma once
#include<vector>
#include<SDL.h>
#include<SDL_ttf.h>

class Font {
private:
	std::string mname;
	TTF_Font* mfont;
	int size{ 16 };
public:
	Font(const std::string& nam="Roboto");
	~Font();
	void test(const std::string& t="a");
	bool loadFont(const std::string& n);
};

class Window {
	int mSCREEN_WIDTH;
	int mSCREEN_HEIGHT;
	SDL_Window* mwindow;
	SDL_Renderer* mrenderer ;
	SDL_Texture* mtexture ;
	//std::vector<Font> fonts;
	Font font;
public:
	Window();
	~Window();
	bool init();
	void close();
	void eventloop();
	void test();
};



