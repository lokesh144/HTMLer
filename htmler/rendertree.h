#pragma once
#include"node.h"
#include"states.h"
#include"defaultstyle.h"
#include"window.h"
struct Rect {
	float x;
	float y;
	float w;
	float h;

};
class RenderTree {
private:
	static Window* windowptr;
	Element* element = nullptr;
	Style* styles = nullptr;
	Rect rect;
	RenderTree* parent{ nullptr };
	std::vector<RenderTree*> children;
	void calculateLayout();
public:
	static void setStatic(Window* window) {
		windowptr = window;
	}
	friend class Window;
	RenderTree();
	RenderTree(Element* elem, Style* stptr);
	~RenderTree();
	bool isRenderable(Style* styleptr);
	void createFromDom(Document* document);
	Style* addDefaultStyleSheets(Element* el);
	void addChild(Node* node);
	void calculateLayout(int);
	SDL_Color getColor();
	//if html has color let the color be that color
	//if not let the color of html be white
	//parse till the html element until it gets color
	//ifnot found: not possible html shoulud have color white by defualt
};

