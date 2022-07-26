#include"node.h"

Node::Node(NodeType ntype, std::string nname, std::string nvalue = "")
	:nodeType{ ntype }, nodeName{ nname }, nodeValue{ nvalue }
{

}


Node Node::appendChild(Node& childNode) {
	childNodes.push_back(&childNode);
	return childNode;
}

bool Node::hasChildNodes() {
	return childNodes.empty();
}

Element::Element(const std::string_view& tn) :tagName{ tn }, localName{ tn } {
}
void Element::setAttribute(const std::string& name, const std::string& value) {

}

std::string Element::getTagName() {
	return tagName;
	
}
Element Document::createElement(const std::string& tname) {
	return Element{ tname };
}

