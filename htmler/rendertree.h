#pragma once
#include"node.h"
#include"defaultstyle.h"
class RenderTree {
public:
	Element* element = nullptr;
	Style* styles = nullptr;
	std::vector<RenderTree*> children;
public:
	bool isRenderable(Style* styleptr) {
		if (styleptr->getDisplay() == styles::Display::NONE) {
			return false;
		}
		return true;
	}
	RenderTree() {
	}
	RenderTree(Element* elem, Style* stptr) :
		element{ elem },
		styles{ stptr }
	{

	}

	~RenderTree() {
		for (std::vector<RenderTree*>::iterator it = children.begin(); it != children.begin(); it++) {
			delete(*it);
			std::cout << "delete render tree element" << endl;
		}
		delete styles;
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
	void addDefaultStyleSheets(Style*& styleptr) {
		switch (getTagNameAsEnum(this->element->tagName)) {
		case HTML:
			styleptr = new SS::HTMLHtmlStyle{};
			break;
		case HEAD:
			styleptr = new SS::HTMLHeadStyle{};
			break;
		case META:
			styleptr = new SS::HTMLMetaStyle{};
			break;
		case BODY:
			styleptr = new SS::HTMLBodyStyle{};
			break;
		case TITLE:
			styleptr = new SS::HTMLTitleStyle{};
			break;
		case P:
			styleptr = new SS::HTMLPStyle{};
			break;
		case DIV:
			styleptr = new SS::HTMLDivStyle{};
			break;
		case NAV:
			styleptr = new SS::HTMLNavStyle{};
			break;
		case UL:
			styleptr = new SS::HTMLUlStyle{};
			break;
		//case MAIN:
			//styleptr = new Style;
		default:
			cout << "NOT IMPLEMENTED" << endl;
			exit(EXIT_FAILURE);
		}
	}

	void addChild(Node* node) {
		for (const auto& currNode : node->childNodes) {
			Element* elptr = nullptr;
			elptr = dynamic_cast<Element*>(currNode);
			if (elptr) {
				Style* styleptr=nullptr;
				addDefaultStyleSheets(styleptr);
				if (!isRenderable(styleptr)) {
					delete styleptr;
					continue;
				}
				RenderTree* rt = new RenderTree{ elptr,styleptr };
				this->children.push_back(rt);
				rt->addChild(currNode);
			}
		}
	}

};

