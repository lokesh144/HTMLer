#include"states.h"

std::string_view getTokenType(tokenType t) {
	switch (t) {
	case CHARACTER:return "CHARACTER";
	case TAG:return "TAG";
	case TOK_COMMENT:return "COMMENT";
	default: return "OTHER";
	}
}
