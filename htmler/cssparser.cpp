#include"cssparser.h"

static inline std::string getPropertyName(Property prop) {
	switch (prop) {
	case Property::COLOR:return "color";
	case Property::MARGIN:return "margin";
	case Property::MARGIN_TOP:return "margin_top";
	case Property::MARGIN_RIGHT:return "margin_right";
	case Property::MARGIN_BOTTOM:return "margin_bottom";
	case Property::MARGIN_LEFT:return "margin_left";
	case Property::BORDER:return "border";
	case Property::BORDER_TOP:return "border_top";
	case Property::BORDER_RIGHT:return "border_right";
	case Property::BORDER_BOTTOM:return "border_bottom";
	case Property::BORDER_LEFT:return "border_left";
	case Property::PADDING:return "padding";
	case Property::PADDING_TOP:return "padding_top";
	case Property::PADDING_RIGHT:return "padding_right";
	case Property::PADDING_BOTTOM:return "padding_bottom";
	case Property::PADDING_LEFT:return "padding_left";
	case Property::WIDTH:return "width";
	case Property::UNKNOWN:return "unknownn ";
	}
}

inline Property getPropertyNameAsEnum(const std::string& prop) {
	if (prop == "color")return Property::COLOR;
	if (prop == "padding")return Property::PADDING;
	if (prop == "width")return Property::WIDTH;
	if (prop == "border")return Property::BORDER;
	if (prop == "margin")return Property::MARGIN;
	else return Property::UNKNOWN;
}

inline void CssParser::ignoreWhiteSpace(const std::string& str, int& pos) {
	int temp{};
	while (str[pos] == ' ') {
		if (++temp > 1) {
			cout << "Multiple whitespace in propvaluepair" << endl;
		}
		if (++pos >= str.size()) {
			cout << "Illegal property Value Pair";
			exit(EXIT_FAILURE);
		}
	}
}

CssParser::CssParser()
	:currPosition{ 0 }
{}

void CssParser::parse(const std::string& str) {
	CssTokenizer tokenizer;
	while (currPosition < str.length()) {
		CssToken token = tokenizer.getNextToken(str, currPosition);
		if (token.first == ReturnType::SELECTOR) {
			cssRules.push_back({ token.second ,{} });
			cout << "Selector: " << token.second << endl;
		}
		else if (token.first == ReturnType::DECLARATION) {
			Declaration declaration = this->parsePropValue(token.second);
			this->cssRules.back().second.push_back(declaration);
			cout << "PropValue: Prop: " << getPropertyName(declaration.property) << " Value: " << declaration.value << endl;
		}
		else if (token.first == ReturnType::END_OF_FILE) {
			return;
		}
	}
}

Declaration CssParser::parsePropValue(const std::string& propValue) {
	int pos{};
	std::string prop;
	std::string value;
	while (std::isalpha(propValue[pos]) || propValue[pos] == '-') {
		//extracting property
		prop += propValue[pos];
		if (++pos >= propValue.size()) {
			cout << "Illegal property Value Pair";
			exit(EXIT_FAILURE);
		}
	}
	Declaration decl;
	decl.property = getPropertyNameAsEnum(prop);
	int temp{};
	//ignore whitespace
	while (propValue[pos] == ' ') {
		//should run only once ig
		pos++;
		if (++temp > 1) {
			cout << "Multiple whitespace in propvaluepair" << endl;
		}
	}
		if (!propValue[pos++] == ':') {
			cout << "Illegal property Value Pair";
			exit(EXIT_FAILURE);
		}
	ignoreWhiteSpace(propValue, pos);
	while (pos < propValue.length()) {
		decl.value += propValue[pos++];
	}
	return decl;
}
