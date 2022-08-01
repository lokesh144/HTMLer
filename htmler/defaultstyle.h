#pragma once
#include<vector>
#include<array>
#include<SDL.h>
namespace styles {
	enum class LengthType {
		PIXEL,
		EM,
		REM,
		AUTO,
		INHERIT,
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
		inline 	double toPixel()const {
			switch (this->mlengthType)
			{
			case styles::LengthType::PIXEL:
				return mvalue;
				break;
			case styles::LengthType::EM:
				return mvalue * 16;//TODO: change
				break;
			case styles::LengthType::REM:
				return mvalue * 16;
				break;
			case styles::LengthType::AUTO:
				//TODO: later if css implemented
				break;
			case styles::LengthType::INHERIT:
				//TODO
				break;
			case styles::LengthType::NOT_SPECIFIED:
				return 0;
				break;
			}

		}
		friend double operator+(const styles::Length& l1, const styles::Length& l2) {
			return l1.toPixel() + l2.toPixel();
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
		CONTENTBOX,
		BORDERBOX,
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
		INSET
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
	class Border {
		Length borderWidth;
		BorderStyle borderStyle;
		SDL_Color color;
	public:
		friend inline  double operator+(const Border& b1, const Border& b2) {
			return b1.borderWidth + b2.borderWidth;
		}
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
			mmargin.at(0) = Length{ 2,LengthType::EM };
			mmargin.at(1) = Length{ 4,LengthType::REM };

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
			mmargin = { Length(1,LengthType::EM),Length(0,LengthType::EM),Length(1,LengthType::EM),Length(0,LengthType::EM) };
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
			mmargin = { Length(1,LengthType::EM),Length(),Length(1,LengthType::EM),Length() };//pixel
			mpadding = { Length(),Length(),Length(),Length(40,LengthType::PIXEL) };//pixel
		}
	};
	class HTMLUlStyle :public Style {
	public:
		HTMLUlStyle() {
			mdisplay = Display::BLOCK;
			mliststyletype = ListStyleType::DISC;
			mmargin = { Length(1,LengthType::EM),Length(0,LengthType::EM),Length(1,LengthType::EM),Length(0,LengthType::EM) };
			mpadding = { Length(),Length(),Length(),Length(40,LengthType::PIXEL) };
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
			mmargin = { Length(0.5,LengthType::EM),Length(0,LengthType::AUTO),Length(0.5,LengthType::EM),Length(0,LengthType::AUTO) }; // auto {0.5 em ,auto ,0.5em ,auto }
			//border style = inset;
			// Border to add
			//mborder={Length(1,LengthType::PIXEL),INSET}
			//TODO MANDIP
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
			mfontSize = Length(2, LengthType::EM);
			mmargin = { Length(0.67,LengthType::EM),Length(),Length(0.67,LengthType::EM),Length() };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH2Style :public Style {
	public:
		HTMLH2Style() {
			mdisplay = Display::BLOCK;
			mfontSize = Length(1.5, LengthType::EM);
			mmargin = { Length(0.83,LengthType::EM),Length(),Length(0.83,LengthType::EM),Length() };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH3Style :public Style {
	public:
		HTMLH3Style() {
			mdisplay = Display::BLOCK;
			mfontSize = Length(1.17, LengthType::EM);
			mmargin = { Length(1,LengthType::EM),Length(),Length(1,LengthType::EM),Length() };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH4Style :public Style {
	public:
		HTMLH4Style() {
			mdisplay = Display::BLOCK;
			mmargin = { Length(1.33,LengthType::EM),Length(),Length(1.33,LengthType::EM),Length() };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH5Style :public Style {
	public:
		HTMLH5Style() {
			mdisplay = Display::BLOCK;
			mfontSize = Length(0.83, LengthType::EM);
			mmargin = { Length(1.67,LengthType::EM),Length(),Length(1.67,LengthType::EM),Length() };
			mFontWeight = FontWeight::BOLD;

		}
	};
	class HTMLH6Style :public Style {
	public:
		HTMLH6Style() {
			mdisplay = Display::BLOCK;
			mfontSize = Length(0.67, LengthType::EM);
			mmargin = { Length(2.33,LengthType::EM),Length(),Length(2.33,LengthType::EM),Length() };
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
			//mdisplay = Display::NONE;
		}
	};
};
//Elements with no default style 
//SPAN, META, MAIN, BUTTON, BR
