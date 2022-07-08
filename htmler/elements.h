#pragma once
#include<string>
#include "node.h"
using std::string;
//refrence URL="https://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-html.html"
class HTMLCollection {
public:
	Node item(unsigned long int index);
	Node namedItem(string name);
private:
	unsigned long int length;
};
class HTMLDocument : public Document{ 
public: 
	void open();
	void close(); 
	void write(string text); 
	void writeln(string text); 
	Element getElementById(string elementId);
	NodeList getElementBYName(string elementName);

private: 
	string title; 
	string referrer; 
	string domain; 
	string URL; 
	HTMLElement body;
	HTMLCollection images;
	HTMLCollection applets;
	HTMLCollection links;
	HTMLCollection forms;
	HTMLCollection anchors;
	string cookie;

};
class HTMLElement : public Element{
	string id;
	string title;
	string lang;
	string dir;
	string ClassName;
};
class HTMLHtmlElement : public HTMLElement {
	string version;
};
class HTMLHeadElement : public HTMLElement {
	string profile;
};
class HTMLLinkElement : public HTMLElement {
	bool disabled;
	string charset;
	string href;
	string hreflang;
	string media;
	string rel;
	string rev;
	string target;
	string type;
};
class HTMLTitleElement : public HTMLElement {
	string text;
};
class HTMLMetaElement : public HTMLElement {
	string content;
	string httpEquiv;
	string name;
	string scheme;
};
class HTMLBaseElement : public HTMLElement {
	string href;
	string target;
};
class HTMLIsIndexElement : public HTMLElement {
	string form;
	string prompt;
};
class HTMLStyleElement : public HTMLElement {
	bool disabled;
	string media;
	string type;
};
class HTMLBodyElement : public HTMLElement {
	string aLink;
	string background;
	string bgColor;
	string link;
	string text;
	string vLink;
};
class HTMLFormElement : public HTMLElement {
public:
	void submit();
	void reset();
private:
	HTMLCollection elements;
	int length;
	string name;
	string acceptCharset;
	string action;
	string enctype;
	string method;
	string target;
};
class HTMLSelectElement : public HTMLElement {
public:
	void add(HTMLElement element, HTMLElement before);
	void remove(long int index);
	void blur();
	void focus();
private:
	string type;
	int selectedIndex;
	string value;
	int length;
	HTMLFormElement form;
	HTMLCollection options;
	bool disabled;
	bool multiple;
	string name;
	int size;
	int tabindex;
};
class HTMLOptGroupElement : public HTMLElement {
	bool disabled;
	string label;
};
class HTMLOptionElement : public HTMLElement {
	HTMLFormElement form;
	bool defaultSelected;
	string text;
	int index;
	bool disabled;
	string label;
	bool selected;
	string value;
};
class HTMLInputElement : public HTMLElement {
public:
	void blur();
	void focus();
	void select();
	void click();
private:
	string defaultValue;
	bool defaultChecked;
	HTMLFormElement form;
	string accept;
	string accesskey;
	string align;
	string alt;
	bool checked;
	bool disabled;
	int maxLength;
	string name;
	bool readOnly;
	string size;
	string src;
	int tabIndex;
	string type;
	string useMap;
	string value;
};
class HTMLTextAreaElement : public HTMLElement {
public:
	void blur();
	void focus();
	void select();
private:
	HTMLFormElement form;
	string defaultValue;
	string accessKey;
	int cols;
	bool disabled;
	string name;
	bool readOnly;
	int rows;
	int tabIndex;
	string type;
	string value;
};
class HTMLButtonElement : public HTMLElement {
	HTMLFormElement form;
	string accessKey;
	bool disabled;
	string name;
	int tabIndex;
	string type;
	string value;
};
class HTMLLabelElement : public HTMLElement {
	HTMLFormElement form;
	string accesskey;
	string hrmlFor;
};
class HTMLFieldSetElement : public HTMLElement {
	HTMLFormElement form;
};
class HTMLLabelElement : public HTMLElement {
	HTMLFormElement form;
	string accessKey;
	string htmlFor;
};
class HTMLFieldSetElement : public HTMLElement {
	HTMLFormElement form;
};
class HTMLLegendElement : public HTMLElement {
	HTMLFormElement form;
	string accessKey;
	string align;
};
class HTMLUListElement : public HTMLElement {
	bool compact;
	string type;
};
class HTMLOListElement : public HTMLElement {
	bool compact;
	int start;
	string type;
};
class HTMLDListElement : public HTMLElement {
	bool compact;
};
class HTMLDirectoryElement : public HTMLElement {
	bool comapct;
};
class HTMLMenuElement : public HTMLElement {
	bool comapct;
};
class HTMLLIElement : public HTMLElement {
	string type;
	int value;
};
class HTMLBlockquoteElement : public HTMLElement {
	string cite;
};
class HTMLDivElement : public HTMLElement {
	string align;
};
class HTMLParagraphElement : public HTMLElement {
	string align;
};
class HTMLHeadingElement : public HTMLElement {
	string align;
};
class HTMLQuoteElement : public HTMLElement {
	string cite;
};
class HTMLPreElement : public HTMLElement {
	int width;
};
class HTMLBRElement : public HTMLElement {
	string clear;
};
class HTMLBaseFrontElement : public HTMLElement {
	string color;
	string face;
	string size;
};
class HTMLFontElement : public HTMLElement {
	string color;
	string face;
	string size;
};
class HTMLHRElement : public HTMLElement {
	string align;
	bool noShade;
	string size;
	string width;
};
class HTMLModElement : public HTMLElement {
	string cite;
	string dateTime;
};
class HTMLAnchorElement : public HTMLElement {
public:
	void blur();
	void focus();
private:
	string accessKey;
	string charset;
	string coords;
	string href;
	string hreflang;
	string name;
	string rel;
	string rev;
	string shape;
	int tabIndex;
	string target;
	string type;
};
class HTMLImageElement : public HTMLElement {
	string lowSrc;
	string name;
	string align;
	string alt;
	string border;
	string height;
	string hspace;
	bool isMap;
	string longDesc;
	string src;
	string useMap;
	string vspace;
	string width;
};
class HTMLObjectElement : public HTMLElement {
	HTMLFormElement form;
	string code;
	string align;
	string archive;
	string border;
	string codeBase;
	string codeType;
	string data;
	bool declare;
	string height;
	string hspace;
	string name;
	string standby;
	int tabIndex;
	string type;
	string useMap;
	string vspace;
	string width;
};
class HTMLParamElement : public HTMLElement {
	string name;
	string type;
	string value;
	string valueType;
};
class HTMLAppletElement : public HTMLElement {
	string align;
	string alt;
	string archive;
	string code;
	string codeBase;
	string height;
	string hspace;
	string name;
	string object;
	string vspace;
	string width;
};
class HTMLMapElement : public HTMLElement {
	HTMLCollection areas;
	string name;
};
class HTMLAreaElement : public HTMLElement {
	string accessKey;
	string alt;
	string coords;
	string href;
	bool noHref;
	string shape;
	int tabIndex;
	string target;
};
class HTMLScriptElement : public HTMLElement {
	string text;
	string htmlFor;
	string event;
	string charset;
	bool defer;
	string src;
	string type;

};
class HTMLTableCaptionElement : public HTMLElement {
	string align;
};
class HTMLTableColElement : public HTMLElement {
	string align;
	string ch;
	string chOff;
	int span;
	string vAlign;
	string width;
};
class HTMLTableSectionElement : public HTMLElement {
public:
	HTMLElement insertRow(int index);
	void deleteRow(int index);
private:
	string align;
	string ch;
	string chOff;
	string vAlign;
	HTMLCollection rows;
};
class HTMLTableRowElement : public HTMLElement {
public:
	HTMLElement insertCell(int index);
	void deleteCell(int index);
private:
	int rowIndex;
	int sectionRowIndex;
	HTMLCollection cells;
	string align;
	string bgcolor;
	string ch;
	string chOff;
	string vAlign;
};
class HTMLTableCellElement : public HTMLElement {
	int cellIndex;
	string abbr;
	string align;
	string axis;
	string bgColor;
	string ch;
	string chOff;
	int colSpan;
	string headers;
	string height;
	bool noWrap;
	int rowSpan;
	string scope;
	string vAlign;
	string width;
};
class HTMLTableElement : public HTMLElement {
public:
	HTMLElement createTHead();
	void deleteTHead();
	HTMLElement createTFoot();
	void deleteTFoot();
	HTMLElement createCaption();
	void deleteCaption();
	HTMLElement insertRow(int index);
	void deleteRow(int index);
private:
	HTMLTableCaptionElement caption;
	HTMLTableSectionElement tHead;
	HTMLTableSectionElement tfoot;
	HTMLCollection rows;
	HTMLCollection tBodies;
	string align;
	string bgColor;
	string border;
	string cellpadding;
	string cellSpacing;
	string frame;
	string rules;
	string summary;
	string width;
};
class HTMLFrameSetElement : public HTMLElement {
	string cols;
	string rows;
};
class HTMLFrameElement : public HTMLElement {
	string frameBorder;
	string longDesc;
	string marginHeight;
	string marginWidth;
	string name;
	bool noResize;
	string scrolling;
	string src;
};
class HTMLIFrameElement : public HTMLElement {
	string align;
	string frameBorder;
	string height;
	string longDesc;
	string marginHeight;
	string marginWidth;
	string name;
	string scrolling;
	string src;
	string width;
};
