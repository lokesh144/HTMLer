#include<algorithm>
#include"rendertree.h"
#include"cssparser.h"

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
			Style* styleptr = addDefaultStyleSheets(elptr);
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

Style* RenderTree::addDefaultStyleSheets(Element* el) {
	Style* styleptr = nullptr;
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
	//
	//SDL_Color c=this->getColor();
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

void RenderTree::calculateLayout(int w) {
	this->rect.w = w;
	for (auto& element : children) {
		element->calculateLayout();
	}
}


/*
this applies to bock level element only

//the width of a element is equal to the width of its parent
//the height of the element is equal to the sum of the height of its childnodes and its margin padding and border

The layout of a element depends upon its childNodes.
- Iterate through child nodes
- If childNode is a text (find the height and weight required to render it)
- if childNode is an element call calculateLayout [recursive]

-- To calculate the text height and width
- first find the margin,padding and border(top,right and left)
- Then calculate the width of content-box
- calculate height required to render the text
-calculate the height for margin,border and padding (bottom)


*/
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
	if (this->element->attributes.size() != 0) {
		if (this->element->attributes[0].getValue() == "4") {
			this->styles->mpadding.left = { 100,styles::LengthType::PIXEL };
			this->styles->mpadding.top = { 10,styles::LengthType::PIXEL };
			this->styles->mpadding.bottom = { 10,styles::LengthType::PIXEL };
		}
	}
	this->rect.h += this->styles->mpadding.top.toPixel();
	this->rect.h += this->styles->mpadding.bottom.toPixel();
	cout << this->element->tagName
		<< "   ";
	cout << endl;
	if (this->element->attributes.size() != 0) {
		cout << this->element->attributes[0].getName() << " : " << this->element->attributes[0].getValue() << endl;
	}
	cout << "(x,y)= " << this->rect.x << "," << this->rect.y << ")" << endl;
	cout << "width: " << this->rect.w << " height: " << rect.h << endl << endl;
}

void RenderTree::calculateBox() {
	constexpr int fontSize = 18;
	struct FourRect {
		SDL_Rect top, right, bottom, left;
	};
	struct FourRect margin, padding, border;
	SDL_Rect content;
	//assume border-box for now
	//no margin for now
	border.left.x = this->rect.x;
	border.left.y = this->rect.y;
	border.left.w = this->styles->mborder.left.borderWidth.toPixel();
	border.left.h = this->rect.h;

	border.right.x = this->rect.x + this->rect.w - this->styles->mborder.right.borderWidth.toPixel();
	border.right.y = this->rect.y;
	border.right.w = this->styles->mborder.right.borderWidth.toPixel();
	border.right.h = this->rect.h;

	border.top.x = this->rect.x;
	border.top.y = this->rect.y;
	border.top.w = this->rect.w;
	border.top.h = this->styles->mborder.top.borderWidth.toPixel();

	border.bottom.x = this->rect.x;
	border.bottom.y = this->rect.y + this->rect.h - this->styles->mborder.bottom.borderWidth.toPixel();
	border.bottom.w = this->rect.w;
	border.bottom.h = this->styles->mborder.bottom.borderWidth.toPixel();

	padding.left.x = this->rect.x + border.left.w;
	padding.left.y = border.top.y + border.top.h;
	padding.left.w = this->styles->mpadding.left.toPixel();
	padding.left.h = this->rect.h - border.top.h - border.bottom.h;

	padding.right.x = border.right.x - this->styles->mpadding.right.toPixel();
	padding.right.y = border.top.y + border.top.h;
	padding.right.w = this->styles->mpadding.right.toPixel();
	padding.right.h = this->rect.h - border.top.h - border.bottom.h;


	padding.top.x = padding.left.x;
	padding.top.y = padding.right.y;
	padding.top.w = border.top.w - border.left.w - border.right.w;
	padding.top.h = this->styles->mpadding.top.toPixel();

	padding.bottom.x = padding.left.x;
	padding.bottom.y = border.bottom.y - this->styles->mpadding.bottom.toPixel();
	padding.bottom.w = padding.top.w;
	padding.bottom.h = this->styles->mpadding.bottom.toPixel();

	content.x = padding.left.x + padding.left.w;
	content.y = padding.top.y + padding.top.h;

	content.w = padding.top.w - padding.left.w - padding.right.w;
	content.h = padding.left.h - padding.top.h - padding.bottom.h;
	//box = content;
}



SDL_Color RenderTree::getColor() {

	return { 0,0,0 };

}

void RenderTree::addStyle(const CssParser& css) {
	//for every css property in find the corresponding element and override styles
	for (auto& cssrule : css.cssRules) {
		int c = this->applyCss(cssrule);
		cout << c << "  total Match" << endl<<endl;
	}
}

int RenderTree::applyCss(const CSSRule& rule) {
	int count{};
	for (auto child : this->children) {
		//iterate thorugh child first
		count += child->applyCss(rule);
	}

	struct Selector selector = rule.first;
	std::string selString = selector.type == SelectorType::ID ? "id" : "class";

	for (auto attribute : this->element->attributes) {
		if (attribute.getName() == selString && attribute.getValue() == selector.name) {
			for (auto propValue : rule.second) {
				this->applyStyle(propValue);
			}
		}
	}
	return count;
}

void RenderTree::applyStyle(const Declaration& style) {
	using namespace styles;
	switch (style.property)
	{
	case CSSProperty::COLOR:

		break;
	case CSSProperty::MARGIN:
		this->styles->mmargin = parseLengthList(style.value);
		break;
	case CSSProperty::MARGIN_TOP:
		this->styles->mmargin.top = parseLength(style.value);
		break;
	case CSSProperty::MARGIN_RIGHT:
		this->styles->mmargin.right = parseLength(style.value);
		break;
	case CSSProperty::MARGIN_BOTTOM:
		this->styles->mmargin.bottom = parseLength(style.value);
		break;
	case CSSProperty::MARGIN_LEFT:
		this->styles->mmargin.left = parseLength(style.value);
		break;
	case CSSProperty::PADDING:
		this->styles->mpadding = parseLengthList(style.value);
		break;
	case CSSProperty::PADDING_TOP:
		this->styles->mpadding.top = parseLength(style.value);
		break;
	case CSSProperty::PADDING_RIGHT:
		this->styles->mpadding.right = parseLength(style.value);
		break;
	case CSSProperty::PADDING_BOTTOM:
		this->styles->mpadding.bottom = parseLength(style.value);
		break;
	case CSSProperty::PADDING_LEFT:
		this->styles->mpadding.left = parseLength(style.value);
		break;
	case CSSProperty::BORDER:
		break;
	case CSSProperty::BORDER_TOP:
		break;
	case CSSProperty::BORDER_RIGHT:
		break;
	case CSSProperty::BORDER_BOTTOM:
		break;
	case CSSProperty::BORDER_LEFT:
		break;
	case CSSProperty::WIDTH:
		break;
	case CSSProperty::UNKNOWN:
		break;
	default:
		break;
	}

}
