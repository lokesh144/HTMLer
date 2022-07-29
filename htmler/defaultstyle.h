#pragma once
#include<vector>
#include<array>
#include<SDL.h>
namespace styles {
	enum class LengthType {
		PIXEL,
		EM,
		REM,
		NOT_SPECIFIED
	};
	class Length {
		LengthType mlengthType;
		double mvalue;
	public:
		Length() :
			mvalue{ 0 }, mlengthType{ LengthType::NOT_SPECIFIED }{}
		Length(double val, LengthType lt = LengthType::PIXEL) :
			mvalue{ val },
			mlengthType{ lt }
		{
		}
	};
	enum  class Display {
		BLOCK,
		INLINE,
		INLINE_BLOCK,
		NONE,
		NOT_SPECIFIED,
		LIST_ITEM
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
	enum class TextDecoration { // Conflict
		OVERLINE,
		LINETHROUGH,
		UNDERLINE,
		NOT_SPECIFIED
	};
	enum class FontWeight {
		NORMAL,
		BOLD,
		LIGHT,
		LIGHTER,
		NOT_SPECIFIED
	};
	enum class ListStyleType {
		DECIMAL,
		DISC,
		NOT_SPECIFIED
	};
	struct Border {
		Length borderWidth;
		BorderStyle borderStyle;
		SDL_Color color;
	};
}

using namespace styles;
class Style {
public:
	styles::TextDecoration mTextDecoration{ TextDecoration::NOT_SPECIFIED };
	styles::FontWeight mFontWeight{ FontWeight::NOT_SPECIFIED };
	styles::Display mdisplay{ Display::NOT_SPECIFIED };
	styles::ListStyleType mliststyletype{ ListStyleType::NOT_SPECIFIED };
	styles::Length mfontSize;
	SDL_Color mcolor;
	SDL_Color mbackgroundColor;
	styles::FontStyle mfontStyle{ FontStyle::NOT_SPECIFIED };
	std::array<styles::Length, 4> mmargin;
	std::array<styles::Length, 4> mpadding;
	std::array<styles::Border, 4> mborder;
	styles::Display getDisplay() {
		return mdisplay;
	}
};

namespace SS {
	using namespace styles;
	class HTMLDivStyle :public Style {
	public:
		HTMLDivStyle() {
			mdisplay = Display::BLOCK;
		}
	};
	class  HTMLHtmlStyle :public Style {
	public:
		HTMLHtmlStyle() {

		}
	};
	class HTMLPStyle :public Style {
	public:
		HTMLPStyle() {
			mdisplay = Display::BLOCK;
			mmargin = { 1,0,1,0 };
			//OR 
		}
	};
	class HTMLLiStyle :public Style {
	public:
		HTMLLiStyle() {
			mdisplay = Display::LIST_ITEM;
		}
	};
	class HTMLOlStyle :public Style {
	public:
		HTMLOlStyle() {
			mdisplay = Display::BLOCK;
			mliststyletype = ListStyleType::DECIMAL;
			mmargin = { 1,0,1,0 };//pixel
			mpadding = { 0,0,0,40 };//pixel
		}
	};
	class HTMLUlStyle :public Style {
	public:
		HTMLUlStyle() {
			mdisplay = Display::BLOCK;
			mliststyletype = ListStyleType::DISC;
			mmargin = { 1,0,1,0 };
			mpadding = { 0,0,0,40 };
		}
	};
	class HTMLArticleStyle :public Style {
	public:
		HTMLArticleStyle() {
			mdisplay = Display::BLOCK;
		}
	};
	class HTMLUStyle :public Style {
	public:
		HTMLUStyle() {
			mTextDecoration = TextDecoration::UNDERLINE;
		}
	};
	class HTMLStyleStyle :public Style {
	public:
		HTMLStyleStyle() {
			mdisplay = Display::NONE;
		}
	};
	class HTMLStrongStyle :public Style {
	public:
		HTMLStrongStyle() {
			mFontWeight = FontWeight::BOLD;
		}
	};
	class HTMLStrikeStyle :public Style {
	public:
		HTMLStrikeStyle() {
			mTextDecoration = TextDecoration::LINETHROUGH;
		}
	};
	class HTMLNavStyle :public Style {
	public:
		HTMLNavStyle() {
			mdisplay = Display::BLOCK;
		}
	};
	class HTMLHrStyle :public Style {
	public:
		HTMLHrStyle() {
			mdisplay = Display::BLOCK;
			mmargin = { 1,0,1,0 }; // auto {0.5 em ,auto ,0.5em ,auto }
			//border style = inset;
			// Border to add
			//mborderWidth = 1;
		}
	};
	class HTMLEmStyle :public Style {
	public:
		HTMLEmStyle() {
			mfontStyle = FontStyle::ITALIC;
		}
	};
	class HTMLH1Style :public Style {
	public:
		HTMLH1Style() {
			mdisplay = Display::BLOCK;
			mfontSize = 2;
			mmargin = { 0.67,0,0.67,0 };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH2Style :public Style {
	public:
		HTMLH2Style() {
			mdisplay = Display::BLOCK;
			mfontSize = 1.5;
			mmargin = { 0.83,0,0.83,0 };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH3Style :public Style {
	public:
		HTMLH3Style() {
			mdisplay = Display::BLOCK;
			mfontSize = 1, 17;
			mmargin = { 1,0,1,0 };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH4Style :public Style {
	public:
		HTMLH4Style() {
			mdisplay = Display::BLOCK;
			mmargin = { 1.33,0,1.33,0 };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH5Style :public Style {
	public:
		HTMLH5Style() {
			mdisplay = Display::BLOCK;
			mfontSize = 0.83;
			mmargin = { 1.67,0,1.67,0 };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH6Style :public Style {
	public:
		HTMLH6Style() {
			mdisplay = Display::BLOCK;
			mfontSize = 0.67;
			mmargin = { 2.33,0,2.33,0 };
			mFontWeight = FontWeight::BOLD;
		}
	};

	//TODO: assign member
	class HTMLTitleStyle :public Style {
	public:
		HTMLTitleStyle() {
			mdisplay = Display::NONE;
		}
	};
	class HTMLMetaStyle :public Style {
	public:
		HTMLMetaStyle() {
			mdisplay = Display::NONE;
		}
	};
	class HTMLHeadStyle :public Style {
	public:
		HTMLHeadStyle() {
			mdisplay = Display::NONE;
		}
	};
	class HTMLBodyStyle :public Style {
	public:
		HTMLBodyStyle() {
			mdisplay = Display::NONE;
		}
	};

};
