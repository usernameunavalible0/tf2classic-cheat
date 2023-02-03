#pragma once
#include "../Interfaces/Interfaces.h"
#include <vector>

class CDraw
{
public:
	void String(const size_t& font, int x, int y, const Color& clr, const short align, const char* const str, ...);
	void String(const size_t& font, int x, int y, const Color& clr, const short align, const wchar_t* const str, ...);

	void Line(const int x, const int y, const int x1, const int y1, const Color& clr);
	void Rect(const int x, const int y, const int w, const int h, const Color& clr);
};

namespace G { inline CDraw Draw; }