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
class Node {
	private:
	NodeType nodeType;
	std::string nodeName;
	std::string nodeValue;
	std::vector<Node*> childNodes;
	Node* parentNode = nullptr;
	//NamedNodeMap attributes;//idk licwhat is this exactly
public:
	Node appendChild(const Node& nodeToAdd);
	bool hasChildNodes();
};

class Document:public Node {
private:
	HTML documentElement;//default html element
public:
	Element createElement(std::string_view tagName);
};

class Comment;