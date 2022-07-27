#include<iostream>
#include "parser.h"
#include "tokenizer.h"
#include"node.h"
#include"elements.h"
using std::cout;
#define endl '\n'

Parser::Parser(Document* doc)
	:parseState{ BEFORE_HTML },
	mdocument{ doc },
	//:parseState{ INITIAL },
	currPosition{}
{
}
std::ostream& operator<<(std::ostream& out, struct Token token) {
	out << getTokenType(token.type) << ": " << token.token << " ";
	return out;
}

typedef struct MockeElement {
	std::string _namespace;
	std::string localName;
	std::vector<std::pair<std::string, std::string>> attributeList;
	std::vector<Element> elementList{};

} MockElement;
//Element create_element(Document* document, std::string ln) {

//}
void Parser::create_element_for_token(const std::string& tn) {
	Element* el;
	switch(getTagNameAsEnum(tn)) {
	case HTML:
		el = new HTMLHtmlElement{};
		break;
	case HEAD:
		el = new HTMLHeadElement{};
		break;
	case BODY:
		el = new HTMLBodyElement{};
		break;
	case TITLE:
		el = new HTMLTitleElement{};
		break;
	case P:
		el = new HTMLParagraphElement{};
		break;
	case DIV:
		el = new HTMLDivElement{};
		break;
	default:
		el = new HTMLElement{"el"};
		break;
	}

	cout << "create " << endl;
	if (mstack.empty()) {
		mdocument->appendChild(el);
		mstack.push(el);//this must be a html element
		return;
	}
	mstack.top()->appendChild(el);
	//leave attribute for now
	mstack.push(el);
}

void Parser::insert_character(const std::string& ch) {
	Text* te = new Text(ch);
	mstack.top()->appendChild(te);
	//if current node be document return
	//if text node in previous node append to text node
}
void Parser::generic_rcdata_parse(const std::string& tn) {
	Element el{ tn };
	originalParseState = parseState;
	//switch tokenizer to rcdata state?
	parseState = TEXT;
	//leave attribute for now
	//mstack.push(el);
}

/*MockElement create_speculative_mock_element(std::string& ns, const std::string& tn, std::vector<std::pair<std::string, std::string>> al)
{
	struct MockeElement el {
		._namespace = ns,
			.localName = tn,
			.attributeList = al
	};

	return el;
}
*/
void Parser::parse(const std::string& str) {
	Tokenizer tokenizer;
	struct Token token;
	bool reprocessToken = false;
	while (str[currPosition] != '\0') {
		if (!reprocessToken) {
			token = tokenizer.getNextToken(str, currPosition);
			if (token.type == TAG || token.type == END_TAG) {
				cout << token.token << endl;
			}
		}
		else {
			reprocessToken = false;
		}
		if (token.type == TAG) {
			//mstack.push(getTagNameAsEnum(token.token));
		}
		switch (parseState) {
		case INITIAL:
			switch (token.type) {
			case DOCTYPE:
				parseState = BEFORE_HTML;
				break;//later
			case COMMENT:
				////document.appendChild(Comment token.token);//document cant have more than one child so ignore for now
				break;
			default:
				parseState = BEFORE_HTML;
				reprocessToken = true;
				//exit(EXIT_FAILURE);//TODO:
			}
			break;
		case BEFORE_HTML:
			switch (token.type) {
			case DOCTYPE:
				exit(EXIT_FAILURE);
				break;
			case COMMENT:
				//document.appendChild(Comment token.token);//document can have only one child
				break;
			case TAG:
				switch (getTagNameAsEnum(token.token)) {
				case HTML:
				{
					create_element_for_token(token.token);
					parseState = BEFORE_HEAD;
					break;
				}
				default:
					exit(EXIT_FAILURE);
				}
				break;
			case END_TAG:
				TagName tempTagName;
				tempTagName = getTagNameAsEnum(token.token);//for no error
				if (tempTagName == HTML || tempTagName == HEAD || tempTagName == BODY
					|| tempTagName == BR) {
					//will fallthrough to default;
										//NOTE: the case END_TAG must always be just above default case
				}
				else { exit(EXIT_FAILURE); break; }
				//[[fallthrough]];
			default:
				//Create an html element whose node document is the Document object. Append it to the Document object. Put this element in the stack of open elements.
				parseState = BEFORE_HEAD;
				reprocessToken = true;
				break;

			}
			break;
		case BEFORE_HEAD:
			switch (token.type) {
			case DOCTYPE:
				exit(EXIT_FAILURE);
				break;
			case COMMENT:
				//document.appendChild(Comment token.token);
				break;
			case TAG:
				switch (getTagNameAsEnum(token.token)) {
				case HTML:
					//Process the token using the rules for the "in body" insertion mode.
					break;
				case HEAD:
					//insert html element
					//set head pointer 
					create_element_for_token(token.token);
					//*headptr=
					parseState = IN_HEAD;

				}
				break;
			case END_TAG:
				TagName tempTagName;
				tempTagName = getTagNameAsEnum(token.token);
				if (tempTagName == HTML || tempTagName == HEAD || tempTagName == BODY
					|| tempTagName == BR) {
					//will fallthrough to default
					//NOTE: the case END_TAG must always be just above default case
				}
				else { exit(EXIT_FAILURE); break; }
			default:
				//insert html element for head start tag token
				//set head element pointer
				parseState = IN_HEAD;
				reprocessToken = true;
			}
			break;
		case IN_HEAD:
			switch (token.type) {
			case COMMENT:
				//insert comment
				break;
			case DOCTYPE:
				exit(EXIT_FAILURE);
				break;
			case TAG:
				switch (getTagNameAsEnum(token.token)) {
				case HTML:
					// Process the token using the rules for the "in body" insertion mode.
					break;
				case BASE:
				case BASEFONT:
				case BGSOUND:
				case LINK:
					//idk ept
					//Insert an HTML element for the token. Immediately pop the current node off the stack of open elements.
					break;
				case META:
					//TODO: 
					this->create_element_for_token(token.token);
					mstack.pop();
					break;
				case TITLE:
					this->create_element_for_token(token.token);
					originalParseState = parseState;
					parseState = TEXT;
					//rcdata parsing
					break;
				case STYLE:
					//raw text parsing element
					break;
				case SCRIPT:
					exit(EXIT_FAILURE);
					break;
				case HEAD:
					exit(EXIT_FAILURE);
					break;
				}
				break;
			case END_TAG:
				TagName tempTagName;
				tempTagName = getTagNameAsEnum(token.token);
				if (tempTagName == HEAD) {
					parseState = AFTER_HEAD;
					mstack.pop();//TODO: check for head to  be the last element
					break;
				}
				else if (tempTagName == BODY || tempTagName == HTML || tempTagName == BR)
				{
					//will fallthrough to default
					//NOTE: the case END_TAG must always be just above default case
				}
				else {
					exit(EXIT_FAILURE);
					break;
				}
			default:
				//pop the head from stack
				parseState = AFTER_HEAD;
				reprocessToken = false;
			}
			break;
		case AFTER_HEAD:
			switch (token.type)
			{
			case COMMENT:
				break;
			case DOCTYPE:
				exit(EXIT_FAILURE);

			case TAG:
				switch (getTagNameAsEnum(token.token)) {
				case BODY:
					this->create_element_for_token(token.token);
					parseState = IN_BODY;
					break;
				}
			default:
				break;
			}
			break;
		case IN_BODY:
			switch (token.type)
			{
			case END_TAG:
			{
				//todo: handle later with all cojnjditions 
				TagName currOpenTag = getTagNameAsEnum(mstack.top()->getTagName());
				TagName currEndTag = getTagNameAsEnum(token.token);
				switch (currEndTag) {
				case BODY:
					if (currOpenTag != BODY)exit(EXIT_FAILURE);
					mstack.pop();
					parseState = AFTER_BODY;
					break;
				case DIV:
				case NAV:
				case UL:
				case LI:
				case P:
					if (currEndTag = currOpenTag) {
						//exit(EXIT_FAILURE);
						mstack.pop();
					}
					//check stuffs
				}
				break;
			}
			case TAG:
				TagName tn;
				switch (tn = getTagNameAsEnum(token.token)) {
				case DIV:
				case NAV:
				case UL:
				case LI:
				case P:
					//If the stack of open elements has a p element in button scope, then close a p element.
					create_element_for_token(token.token);

					//insert an html element
					//check stuffs
					break;
					//case Headinfs:
				}
			default:
				break;
			}
			break;
		case TEXT:
			switch (token.type) {
			case CHARACTER:
				insert_character(token.token);//todo
				break;
			case END_TAG:
				mstack.pop();
				parseState = originalParseState;
				break;
			}
			break;
		}
	}
	cout << token << endl;
}

void insertHtmlElement() {
	int adjusted_insertion_location = 1;//=current Node
	int element;//create elemetn
	//push element to stack

}
void Parser::printStackOfOpenElements() {
	while (!mstack.empty()) {
		//cout << getTagName(mstack.top()) << endl;
		mstack.pop();
	}
}


/*
case ADDRESS:
case ARTICLE:
case ASIDE:
case BLOCKQUote:
case CENTER:
case DETAILS:
case DIALOG:
case DIR:
case DIV:
case DL:
case FIELDSEt:
case FIGCAPTion:
case FIGURE:
case FOOTER:
case HEADER:
case HGROUP:
case MAIN:
case MENU:
case NAV:
case OL:
case P:
case SECTION:
case SUMMARY:
case UL:
*/
