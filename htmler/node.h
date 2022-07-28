#pragma once
#include<vector>
#include<string>
#include<iostream>
class HTML;
class Element;
class Attribute;
typedef std::string DOMString;
enum NodeType {
	ATTRIBUTE_NODE,
	ELEMENT_NODE,
	TEXT_NODE,
	COMMENT_NODE,
	DOCUMENT_NODE,
};

class ELement;
class Node {
protected:
	NodeType nodeType;
	std::string nodeName;
	std::string nodeValue;
	std::vector<Node*> childNodes;
	Node* parentNode = nullptr;
	//NamedNodeMap attributes;//contains attribute if it is element
	//NamedNodeMap attributes;//idk licwhat is this exactly
public:

	Node() = default;
	Node(NodeType ntype, std::string nname, std::string nvalue);
	Node* appendChild(Node* childNode);//insert at last
	bool hasChildNodes();
	virtual ~Node() {
		for (std::vector<Node*>::iterator it = childNodes.begin(); it != childNodes.end(); it++) {
			delete(*it);
			std::cout << "delete " << std::endl;
		}
	}
};

class Element :public Node {
protected:
	std::string tagName;
	std::string localName;
	std::vector<Attribute> attributes;

public:
	Element() = default;
	Element(const std::string& tn);
	void setAttribute(const std::string& name, const std::string& value);
	void setAttributes(const std::vector<Attribute>& as);
	std::string getTagName();
};

class Text :public Node {
private:
	std::string mdata;
public:
	Text() = default;
	Text(const std::string& s) :mdata{ s } { }
	void appendData(const std::string& c) {
		mdata += c;
	}
	~Text() {
		//delete this;
	}

};

class Document :public Node {
protected:
	Element documentElement;//default html element
public:
	Document() = default;
	Element createElement(const std::string& tname);
};
class Attribute :public Node {
protected:
	std::string name;
	std::string value;
public:
	Attribute(const std::string& n, const std::string& v) :name{ n }, value{ v }{}
	void setName(const std::string& n) {
		name = n;
	}
	void setValue(const std::string& v) {
		value = v;
	}
};
