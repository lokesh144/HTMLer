#pragma once
#include<vector>
#include<array>
#include<SDL.h>
namespace styles {

	enum  class Display {
		BLOCK,
		INLINE,
		INLINE_BLOCK,
		NONE,
		NOT_SPECIFIED
	};

	enum class BoxSizing {
		BORDERBOX,
		CONTENTBOX,
		PADDINGBOX,
		NOT_SPECIFIED
	};
	enum class FontStyle {
		NOT_SPECIFIED,
		NORMAL,
		ITALIC,
		UNDERLINE,

	};
	enum class BorderStyle {
		SOLID,
		DOTTED,
	};
	struct Border {
		int width;
		BorderStyle borderStyle;
		SDL_Color color;
	};
}

class Style;

class Style {
public:
	styles::Display mdisplay{ NULL };
	int mfontSize{ NULL };
	SDL_Color mcolor{ NULL };
	SDL_Color mbackgroundColor{ NULL };
	styles::FontStyle mfontStyle{ NULL };
	std::array<int, 4> mmargin{ NULL };
	std::array<int, 4> mpadding{ NULL };
	std::array<styles::Border, 4> mborder{ NULL };
};

namespace SS {
	using namespace styles;
	class DivStyle :public Style {
		DivStyle() {
			mdisplay = Display::BLOCK;
		}
	};

	class HTMLStyle :public Style {
		HTMLStyle() {

		}
	};
};
