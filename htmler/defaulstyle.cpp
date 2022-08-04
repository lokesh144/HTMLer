#include"defaultstyle.h"
#include"states.h"
inline 	int styles::Length::toPixel(int size)const {
	switch (this->mlengthType)
	{
	case styles::LengthType::PIXEL:
		return mvalue;
		break;
	case styles::LengthType::EM:
		return mvalue * size;//TODO: change
		break;
	case styles::LengthType::REM:
		return mvalue * size;
		break;
	case styles::LengthType::AUTO:
		//TODO: later if css implemented
		break;
		//case styles::LengthType::INHERIT:
			//TODO
			//break;
	case styles::LengthType::NOT_SPECIFIED:
		return 0;
		break;
	}

}
inline  int operator+(const Border& b1, const Border& b2) {
	return b1.borderWidth + b2.borderWidth;
}

styles::Length::Length(int val, LengthType lt) :
	mvalue{ val },
	mlengthType{ lt }
{
}
styles::Length::Length() :
	mvalue{ 0 }, mlengthType{ LengthType::NOT_SPECIFIED }{}
int operator+(const styles::Length& l1, const styles::Length& l2) {
	return l1.toPixel() + l2.toPixel();
}

static int styles::getLength(const std::string& str) {
	try
	{
		const int i{ std::stoi(str) };
		return i;
	}
	catch (std::invalid_argument const& ex)
	{
		cout << "Invalid Length" << endl;
		cout << ex.what() << endl;
		exit(EXIT_FAILURE);
	}
	catch (std::out_of_range const& ex)
	{
		cout << "Invalid Length" << endl;
		cout << ex.what() << endl;
		exit(EXIT_FAILURE);
	}
}

LengthType styles::getLengthType(const std::string& str) {
	if (str.ends_with("px"))
		return LengthType::PIXEL;
	else if (str.ends_with("rem"))//should be above em 
		return LengthType::REM;
	else if (str.ends_with("em"))
		return LengthType::EM;
}
Length styles::parseLength(const std::string& length) {
	//MUST : validate length
	int value{ getLength(length) };
	LengthType ltype = value == 0 ? LengthType::PIXEL : getLengthType(length);
	return Length{ value,ltype };
}
struct styles::Dimension styles::parseLengthList(std::string lengths) {
	trim(lengths);
	std::vector<std::string >lengthList;
	lengthList.push_back("");
	for (char c : lengths) {
		if (c == ' ') {

		}
		lengthList.back() += c;
	}

	if (lengthList.size() == 1) {
		Length length = parseLength(lengthList[0]);
		return Dimension{
		length,
		length,
		length,
		length
		};
	};

	if (lengthList.size() == 2) {
		Length ylength = parseLength(lengthList[0]);
		Length xlength = parseLength(lengthList[1]);
		return Dimension{
			.top = ylength,
			.right = xlength,
			.bottom = ylength,
			.left = xlength
		};
	};

	if (lengthList.size() == 3) {
		Length ytlength = parseLength(lengthList[0]);
		Length xlength = parseLength(lengthList[1]);
		Length yblength = parseLength(lengthList[2]);
		return Dimension{
			.top = ytlength,
			.right = xlength,
			.bottom = yblength,
			.left = xlength
		};
	};

	if (!(lengthList.size() == 4)) {
		cout << "Invlaud Length Value";
		exit(EXIT_FAILURE);
	}
	//if size==4;
	Dimension dimension;
	for (int i{}; i < 4; i++) {
		Length length = parseLength(lengthList[i]);
		switch (i) {
		case 0:dimension.top = length; break;
		case 1:dimension.right = length; break;
		case 2:dimension.bottom = length; break;
		case 3:dimension.left = length; break;
		}
	}
}
