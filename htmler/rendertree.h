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
	void addDefaultStyleSheets(Element* el, Style*& styleptr);
	void addChild(Node* node);
	void calculateLayout(int);
};

