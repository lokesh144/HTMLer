#pragma once
#include"node.h"
#include"defaultstyle.h"
class RenderTree {
public:
	Element* element = nullptr;
	Style styles;
	std::vector<RenderTree*> children;
public:
	bool isRenderable(Element* node) {
		cout << 'test';
		switch (getTagNameAsEnum(node->tagName)) {
		case HEAD:
		case TITLE:
			return false;
		}
		

		return true;
	}
	RenderTree() {
	}
	RenderTree(Element* elem) :element{ elem } {

	}

	~RenderTree() {
		for (std::vector<RenderTree*>::iterator it = children.begin(); it != children.begin(); it++) {
			delete(*it);
			std::cout << "delete render tree element" << endl;
		}
	}
	void createFromDom(Document* document) {
		//assuming document has only one child and which is HTMl
		element = dynamic_cast<Element*>(document->childNodes[0]);
		if (!element) {
			cout << "Document has no child html" << endl;
			exit(EXIT_FAILURE);
		}
		this->addChild(document->childNodes[0]);
	}
	void addDefaultStyleSheets() {
		switch (getTagNameAsEnum(this->element->tagName)) {
		case DIV:

		}

	}

	//void addChild(RenderTree* rt,Node* node) {
	void addChild(Node* node) {
		for (const auto& currNode : node->childNodes) {
			Element* elptr = nullptr;
			elptr = dynamic_cast<Element*>(currNode);
			if (elptr) {
				if (!isRenderable(elptr)) {
					continue;
				}
				addDefaultStyleSheets();
				RenderTree* rt = new RenderTree{ elptr };
				this->children.push_back(rt);
				rt->addChild(currNode);
			}
		}
	}

};

