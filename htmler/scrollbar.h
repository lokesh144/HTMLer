#pragma once
#include<SDL.h>
class Scrollbar {
private:
	int mwidth;
	int mheight;
	int mcurrYPos;
	int mcontentHeight;
public:
	Scrollbar(int w) :mwidth(w),mcurrYPos(0) {}
	void setTotalHeight(int height,int screenHeight) {
		mcontentHeight = height;
		mheight = screenHeight / (mcontentHeight / screenHeight);
	}
	void render(SDL_Renderer* renderer,int currYPos,int screenWidth,int screenHeight) {
		SDL_Rect scrollBackgroundRect{
			screenWidth-mwidth,
			0,
			mwidth,
			screenHeight
		};
		int paddingX = 2;
		mcurrYPos = (static_cast<float>(currYPos) / mcontentHeight) * screenHeight;
		SDL_Rect scrollBarRect{
			screenWidth-mwidth+paddingX,
			mcurrYPos,
			mwidth-2*paddingX,
			mheight
		};
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		SDL_RenderFillRect(renderer, &scrollBackgroundRect);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &scrollBarRect);


	}
};