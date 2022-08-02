#include<algorithm>
#include"rendertree.h"
#define endl '\n'
using std::cout;
RenderTree::RenderTree() {}

RenderTree::RenderTree(Element* elem, Style* stptr)
	: element{ elem },
	styles{ stptr }
{
}

Window* RenderTree::windowptr = nullptr;
RenderTree::~RenderTree() {
	for (std::vector<RenderTree*>::iterator it = children.begin(); it != children.begin(); it++) {
		delete(*it);
		std::cout << "delete render tree element" << endl;
	}
	delete styles;
}

bool RenderTree::isRenderable(Style* styleptr) {
	if (styleptr->getDisplay() == styles::Display::NONE) {
		return false;
	}
	return true;
}

void RenderTree::createFromDom(Document* document) {
	//assuming document has only one child and which is HTMl
	element = dynamic_cast<Element*>(document->childNodes[0]);
	if (!element) {
		cout << "Document has no child html" << endl;
		exit(EXIT_FAILURE);
	}
	this->addChild(document->childNodes[0]);
}
void RenderTree::addChild(Node* node) {
	for (const auto& currNode : node->childNodes) {
		Element* elptr = nullptr;
		elptr = dynamic_cast<Element*>(currNode);
		if (elptr) {
			Style* styleptr = nullptr;
			addDefaultStyleSheets(elptr, styleptr);
			if (!isRenderable(styleptr)) {
				delete styleptr;
				continue;
			}
			RenderTree* rt = new RenderTree{ elptr,styleptr };
			rt->parent = this;
			this->children.push_back(rt);
			if (currNode->childNodes.size() == 0) {
				//this->calculateLayout();
			}
			else {
				rt->addChild(currNode);
				//this->calculateLayout();
			}
		}
	}
}

void RenderTree::addDefaultStyleSheets(Element* el, Style*& styleptr) {
	switch (getTagNameAsEnum(el->tagName)) {
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
	case SPAN:
		styleptr = new SS::HTMLStrikeStyle{};
		break;
	default:
		cout << "NOT IMPLEMENTED" << endl;
		exit(EXIT_FAILURE);
	}
}


void RenderTree::calculateLayout(int w) {
	this->rect.w = w;
	for (auto& element : children) {
		element->calculateLayout();
	}
}

bool isBlockLevelElement(const std::string& tn) {

	//switch (getTagNameAsEnum(this->element->tagName)) {
	switch (getTagNameAsEnum(tn)) {
	case BODY:
	case DIV:
	case ARTICLE:
	case NAV:
	case H1:
	case H2:
	case H3:
	case H4:
	case H5:
	case H6:
	case UL:
	case OL:
	case P:
		return true;

		//block level
		/*
		double marginx = this->styles->mmargin[1] +
			this->styles->mmargin[3];
		double borderx = this->styles->mborder[1] +
			this->styles->mborder[3];
		double paddingx = this->styles->mpadding[1] +
			this->styles->mpadding[3];
		*/
		//x-> parents x
		//y-> if(first child) parents y preceding siblings y+ its height
	}
	return false;
}

void RenderTree::calculateLayout() {
	if (!RenderTree::windowptr) {
		cout << "null winodowptr" << endl;
		exit(EXIT_FAILURE);
	}
	if (isBlockLevelElement(this->element->tagName)) {
		this->rect.w = this->parent->rect.w;
	}
	else {


	}
	auto isTextNode = [](Node* node) {
		if (dynamic_cast<Text*>(node))
			return true;
		else
			return false;
	};
	this->rect.y += this->parent->rect.y;
	int i = 0;
	for (auto node : this->parent->element->childNodes) {
		//preceding textNode siblings
		if (isTextNode(node)) {
			auto textNodeptr = dynamic_cast<Text*>(node);
			if (textNodeptr) {
				auto& text = textNodeptr->getText();
				auto [width, height] = RenderTree::windowptr->getFontSize(text);
				//this->rect.w = width;
				auto pwidth = this->parent->rect.w;
				int linecount = static_cast<int>(width / pwidth);
				if (width > pwidth * linecount) {
					linecount++;
				}
				this->rect.y += linecount * height;
			}
		}
		else {
			if (this->parent->children[i++] == this) {
				break;
			}
			else {
			}
		}
	}
	for (auto child : this->parent->children) {
		//preceding sibling
		if (child == this)
			break;
		else {
			this->rect.y += child->rect.h;
		}
	}

	for (auto& element : children) {
		element->calculateLayout();
	}

	i = 0;
	for (auto node : this->element->childNodes) {
		auto textNodeptr = dynamic_cast<Text*>(node);
		if (textNodeptr) {
			//curr Node is textNode
			auto& text = textNodeptr->getText();
			auto [width, height] = RenderTree::windowptr->getFontSize(text);
			auto pwidth = this->parent->rect.w;
			int linecount = static_cast<int>(width / pwidth);
			if (width > pwidth * linecount) {
				linecount++;
			}
			this->rect.h += linecount * height;
		}
	}
	for (auto rt : children) {
		this->rect.h += rt->rect.h;
	}
	cout << this->element->tagName
		<< "   ";
	cout << endl;
	if (this->element->attributes.size() != 0) {

		cout << this->element->attributes[0].getName() << " : " << this->element->attributes[0].getValue() << endl;
	}
	cout << "(x,y)= " << this->rect.x << "," << this->rect.y << ")" << endl;
	cout << "width: " << this->rect.w << " height: " << rect.h << endl << endl;
}
