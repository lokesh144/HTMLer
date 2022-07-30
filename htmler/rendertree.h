#pragma once
#include"node.h"
#include"defaultstyle.h"
class RenderTree {
public:
	Element* element = nullptr;
	Style* styles = nullptr;
	std::vector<RenderTree*> children;
public:
	RenderTree();
	RenderTree(Element* elem, Style* stptr);
	~RenderTree();
	bool isRenderable(Style* styleptr);
	void createFromDom(Document* document);
	void addDefaultStyleSheets(Element* el, Style*& styleptr);
	void addChild(Node* node);
	void calculateLayout();
};

