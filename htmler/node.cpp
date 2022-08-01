#include"node.h"

Node::Node(NodeType ntype)
	:nodeType{ ntype } {
	switch (nodeType) {
	case NodeType::ATTRIBUTE_NODE:
		nodeName = "#attr";//todo https://dom.spec.whatwg.org/#dom-node-nodename:~:text=The%20nodeName%20getter%20steps%20are%20to%20return%20the%20first%20matching%20statement%2C%20switching%20on%20the%20interface%20this%20implements%3A
		break;
	case NodeType::ELEMENT_NODE:
		//todo above
		nodeName = "#element";
		break;
	case NodeType::TEXT_NODE:
		nodeName = "#text";
		break;
	case NodeType::COMMENT_NODE:
		nodeName = "#comment";
		break;
	case NodeType::DOCUMENT_NODE:
		//todo above
		nodeName = "#document";
		break;
	}
}

Node* Node::appendChild(Node* cn) {
	childNodes.push_back(cn);
	return cn;
}

bool Node::hasChildNodes() {
	return childNodes.empty();
}

Element::Element() :Node(NodeType::ELEMENT_NODE) {}
Element::Element(const std::string& tn) : tagName{ tn }, localName{ tn } {
}
void Element::setAttribute(const std::string& name, const std::string& value) {

}

void Element::setAttributes(const std::vector<Attribute>& as) {
	for (const auto& it : as) {
		attributes.push_back(it);
	}
}
std::string Element::getTagName() {
	return tagName;

}
Element Document::createElement(const std::string& tname) {
	return Element{ tname };
}


Text::Text() :Node(NodeType::TEXT_NODE) {}
Text::Text(const std::string& s) : Node(NodeType::TEXT_NODE), mdata{ s } { }
Document::Document() : Node(NodeType::DOCUMENT_NODE) {}
Attribute::Attribute() : Node(NodeType::ATTRIBUTE_NODE) {}
