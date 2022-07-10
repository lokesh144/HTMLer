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

class Document :public Node {
protected:
	 Element documentElement;//default html element
public:
	Document() = default;

	Element createElement(const std::string& tname);
};

class Element :public Node {
protected:
	std::string tagName;
public:
	Element(const std::string& tn);
	void setAttribute(const std::string& name, const std::string& value);
};

class Attribute :public Node {
protected:
	std::string name;
	std::string value;
	bool specified;
public:
};
