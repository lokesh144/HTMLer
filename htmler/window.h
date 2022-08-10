#pragma once
#include<vector>
#include<SDL.h>
#include<SDL_ttf.h>

class RenderTree;
class Window;
class Font {
private:
	std::string mname;
	TTF_Font* mfont;
	int size{ 18 };
public:
	friend class Window;
	Font(const std::string& nam = "Roboto");
	~Font();
	void test(const std::string& t = "a");
	bool loadFont(const std::string& n);
	std::pair<int, int> fontSize(const char* text);
};

class Window {
	int mSCREEN_WIDTH;
	int mSCREEN_HEIGHT;
	SDL_Window* mwindow;
	SDL_Renderer* mrenderer;
	SDL_Texture* mtexture;
	//static std::string title;
	//std::vector<Font> fonts;
	Font mfont;
public:
	Window();
	~Window();
	bool init();
	void close();
	void eventloop(RenderTree*);
	void test();
	void getWindowSize(int* w);
	std::pair<int, int> getFontSize(const std::string& text);
	void render(const RenderTree* tree);
	void renderBox(const RenderTree* tree);
void 	setRootColor();

};












