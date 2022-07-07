#pragma once
#include<string_view>
enum TokenType {
	CHARACTER,
	TAG,
	TOK_COMMENT,
};
struct token {
	TokenType type;
	std::string_view token;
};
enum ParseState :int {
	//LINK: https://html.spec.whatwg.org/multipage/parsing.html#the-insertion-mode
	//NOTE: ofcourse, We don't intend to parse it all
	INITIAL,
	BEFORE_HTML,
	BEFORE_HEAD,
	IN_HEAD,
	IN_HEAD_NOSCRIPT,
	AFTER_HEAD,
	IN_BODY,
	TEXT,
	IN_TABLE,
	IN_TABLE_TEXT,
	IN_CAPTION,
	IN_COLUMN_GROUP,
	IN_TABLE_BODY,
	IN_ROW,
	IN_CELL,
	IN_SELECT,
	IN_SELECT_IN_TABLE,
	IN_TEMPLATE,
	AFTER_BODY,
	IN_FRAMESET,
	AFTER_FRAMESET,
	AFTER_AFTER_BODY,
	AFTER_AFTER_FRAMESET,
};
enum FormattingElements :int {
	A,
	B,
	BIG,
	CODE,
	EM,
	FONT,
	I,
	NOBR,
	S,
	SMALL,
	STRIKE,
	STRONG,
	TT,
	U
};
enum TokenState {
	DATA,
	TAG_OPEN,
	MARK_UP_DECLARATION_OPEN,
	END_TAG_OPEN,
	TAG_NAME,
	SELF_CLOSING_START_TAG,
	BEFORE_ATTRIBUTE_NAME,
	RAWTEXT,
	RAW_TEXT_LESS_THAN_SIGN,
	COMMENT_START,
	ATTRIBUTE_NAME,
	BEFORE_ATTRIBUTE_VALUE,
	AFTER_ATTRIBUTE_NAME,
	ATTRIBUTE_VALUE_DOUBLE_QUOTE,
	ATTRIBUTE_VALUE_SINGLE_QUOTE,
	ATTRIBUTE_VALUE_UNQUOTED,
	AFTER_ATTRIBUTE_VALUE_QUOTED,
	COMMENT_START_DASH,
	COMMENT,
	COMMENT_END,
	COMMENT_LESS_THAN_SIGN,
	COMMENT_END_DASH,
	COMMENT_LESS_THAN_SIGN_BANG,
	COMMENT_LESS_THAN_SIGN_BANG_DASH,
	COMMENT_LESS_THAN_SIGN_BANG_DASH_DASH,
	COMMENT_END_BANG,


};
enum StackElement {

};
enum TagName {
	HTML,
	HEAD,
	BODY,
	TITLE,
	DIV,
	H1,
	H2,
	H3,
	H4,
	H5,
	H6,
	P,
	UL,
	LI,
	NAV,
};
std::string_view getTokenType(TokenType t);
TagName getTagNameAsEnum(const std::string_view& s);
std::string_view getTagName(TagName t);


/*std::string_view getTagState(tokenState s) {
	switch (s) {
	case DATA:return "DATA";
	case TAG_OPEN:return "TAG_OPEN";
	case MARK_UP_DECLARATION_OPEN:return "MARK_UP_DECLARATION_OPEN";
	case END_TAG_OPEN:return "END_TAG_OPEN";
	case TAG_NAME:return "TAG_NAME";
	case SELF_CLOSING_START_TAG:return "SELF_CLOSING_START_TAG";
	case BEFORE_ATTRIBUTE_NAME:return "BEFORE_ATTRIBUTE_NAME";
	default: return "NOT A TAG";
	}
}
*/