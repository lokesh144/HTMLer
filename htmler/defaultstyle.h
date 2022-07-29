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
	/// 
	/// ///
	/// 
	enum class TextDecoration { // Conflict
		OVERLINE,
		LINETHROUGH,
		UNDERLINE
	};
	enum class FontWeight {
		NORMAL,
		BOLD,
		LIGHT,
		LIGHTER,
	};
	/// 
	/// /
	/// 
	struct Border {
		int width;
		BorderStyle borderStyle;
		SDL_Color color;
	};
	
}


class Style {
public:
	//
	styles::TextDecoration mTextDecoration{NULL};
	styles::FontWeight mFontWeight{ NULL };
	//
	styles::Display mdisplay{ NULL };
	int mfontSize{ NULL };
	SDL_Color mcolor{ NULL };
	SDL_Color mbackgroundColor{ NULL };
	styles::FontStyle mfontStyle{ NULL };
	std::array<int, 4> mmargin{ NULL };//top right bottom left
	std::array<int, 4> mpadding{ NULL };//top right bottom left
	std::array<styles::Border, 4> mborder{ NULL };//top right bottom left
};

namespace SS {
	using namespace styles;
	class HTMLDivStyle :public Style {
		HTMLDivStyle() {
			mdisplay = Display::BLOCK;
		}
	};

	class  HTMLHtmlStyle :public Style {
		HTMLHtmlStyle() {

		}
	};
	class HTMLPStyle :public Style {
		HTMLPStyle() {
		mdisplay=Display::BLOCK;
		mmargin = { 1,0,1,0 };
		//OR 
		mmargin.at(0) = 1;
		mmargin.at(1) = 0;
		mmargin.at(2) = 1;
		mmargin.at(3) = 0;
		

		}
	};
	class HTMLUStyle :public Style {
		HTMLUStyle() {
			mTextDecoration = TextDecoration::UNDERLINE;
		}
	};
	class HTMLStyleStyle :public Style {
		HTMLStyleStyle() {
			mdisplay = Display::NONE;
		}
	};
	class HTMLStrongStyle :public Style {
		HTMLStrongStyle() {
			mFontWeight = FontWeight::BOLD;
		}
	};
	class HTMLStrikeStyle :public Style {
		HTMLStrikeStyle() {
			mTextDecoration = TextDecoration::LINETHROUGH;
		}
	};
	class HTMLNavStyle :public Style {
		HTMLNavStyle() {
			mdisplay = Display::BLOCK;
		}
	};
	class HTMLHrStyle :public Style {
		HTMLHrStyle() {
			mdisplay = Display::BLOCK;
			mmargin = { 1,0,1,0 };
			// Border to add
		}
	};


};

