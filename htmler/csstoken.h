#pragma once
#include<iostream>
/*enum TokenType {
	DATA,
	COMMENT,
	NEWLINE,
	WHITESPACE,
	HEX_Digit,
	ESCAPE,
	WHITESPACE_TOKEN,
	WS,
	IDENT_TOKEN,
	FUNCTION_TOKEN,
	AT_KEYWORD_TOKEN,
	STRING_TOKEN,
	URL_TOKEN,
	NUMBER_TOKEN,
	DIMENSION_TOKEN,
	PERCENTAGE_TOKEN,
	CDO_TOKEN,
	CDC_TOKEN,
	QUOTATION_MARK,
	NUMBER_SIGN,
	APOSTROPHE,
	PLUS_SIGN,
	COMMA,
	HYPHEN_MINUS,
	FULL_STOP,

	LESS_THAN_SIGN,
	COMMERCIAL_AT,
	LEFT_SQUARE_BRACKET,
	RIGHT_SQUARE_BRACKET,
	REVERSE_SOLIDUS,
	BAD_STRING_TOKEN
};
*/
enum TokenState {
	CHARACTER,
};
enum TokenType //return type of token
{
 DATA,
 TOK_COMMENT,  
 CURLY_BRACKET,
 COLON,//:
 SEMI_COLON
};
struct token {
	TokenType type;
	std::string_view token;
};
/*enum ParseState :int {
	//LINK: https://www.w3.org/TR/css-syntax-3/#consume-comments
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
}; */
enum Parsestate
{
	//DATA,
	TAG_NAME,
	CLASS,
	LEFT_CURLY_BRACKET,
	RIGHT_CURLY_BRACKET,
	ID
};

