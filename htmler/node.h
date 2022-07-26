#pragma once
#include<vector>
#include<string>
class HTML;
class Element;
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
	Node appendChild(Node& childNode);//insert at last
	bool hasChildNodes();
};

class Element :public Node {
protected:
	std::string tagName;
	std::string localName;
public:
	Element() = default;
	Element(const std::string_view& tn);
	void setAttribute(const std::string& name, const std::string& value);
	std::string getTagName();
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
	bool specified;
public:
};
