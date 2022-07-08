#include<vector>
#include<string>

enum NodeType {
	ATTRIBUTE_NODE,
	ELEMENT_NODE,
	TEXT_NODE,
	COMMENT_NODE,
	DOCUMENT_NODE,

};
class Node {
	NodeType nodeType;
	std::string nodeName;
	std::string nodeValue;
	std::vector<Node*> childNodes;
	Node* parentNode = nullptr;
	//NamedNodeMap attributes;//idk licwhat is this exactly

};