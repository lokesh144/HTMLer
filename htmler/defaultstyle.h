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
		NOT_SPECIFIED,
		LIST_ITEM;
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
	enum class ListStyleType {
		DECIMAL,
		DISC,
	};
	enum class FontWeight {
		NORMAL,
		BOLD,
		LIGHT,
		LIGHTER,
	};
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
	styles::FontWeight mFontWeight{ NULL };
	styles::ListStyleType mliststyletype{ NULL };
	int mfontSize{ NULL };
	int mborderWidth{};
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
	
	class HTMLLiStyle {
		HTMLLiStyle() {
			mdisplay = Display::LIST_ITEM;
		}
	};
	class HTMLOlStyle :public Style {
		HTMLOlStyle() {
			mdisplay = Display::BLOCK;
			mliststyletype = ListStyleType::DECIMAL;
			mmargin = { 1,0,1,0 };
			mpadding = { 0,0,0,40 };
		}
	};
	class HTMLUlStyle :public Style {
		HTMLUlStyle() {
			mdisplay = Display::BLOCK;
			mliststyletype = ListStyleType::DISC;
			mmargin = { 1,0,1,0 };
			mpadding = { 0,0,0,40 };
		}
	};
	class HTMLArticleStyle :public Style {
		HTMLArticleStyle() {
			mdisplay = Display::BLOCK;
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
			mmargin = { 1,0,1,0 }; // auto {0.5 em ,auto ,0.5em ,auto }
			//border style = inset;
			// Border to add
			mborderWidth = 1;
		}
	};


};

	class HTMLEmStyle :public Style {
		HTMLArticleStyle() {
			mfontStyle = FontStyle::ITALIC;
		}
	};
	class HTMLEmStyle :public Style {
		HTMLArticleStyle() {
			mfontStyle = FontStyle::ITALIC;
		}
	};
	class HTMLH1Style :public Style {
		HTMLH1Style() {
			mdisplay = Display::BLOCK;
			mfontSize = 2;
			mmargin = { 0.67,0,0.67,0 };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH2Style :public Style {
		HTMLH2Style() {
			mdisplay = Display::BLOCK;
			mfontSize = 1.5;
			mmargin = { 0.83,0,0.83,0 };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH3Style :public Style {
		HTMLH3Style() {
			mdisplay = Display::BLOCK;
			mfontSize = 1,17;
			mmargin = { 1,0,1,0 };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH4Style :public Style {
		HTMLH4Style() {
			mdisplay = Display::BLOCK;
			mmargin = { 1.33,0,1.33,0 };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH5Style :public Style {
		HTMLH5Style() {
			mdisplay = Display::BLOCK;
			mfontSize = 0.83;
			mmargin = { 1.67,0,1.67,0 };
			mFontWeight = FontWeight::BOLD;

		}
	}; 
	class HTMLH6Style :public Style {
		HTMLH6Style() {
			mdisplay = Display::BLOCK;
			mfontSize = 0.67;
			mmargin = { 2.33,0,2.33,0 };
			mFontWeight = FontWeight::BOLD;

		}

	};

	
	
	

};
