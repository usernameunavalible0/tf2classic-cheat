#pragma once
#include "../Interfaces/Interfaces.h"
#include <vector>

class CDraw
{
public:
	void Line(const int x, const int y, const int x1, const int y1, const Color& clr);
	void Rect(const int x, const int y, const int w, const int h, const Color& clr);
};

namespace G { inline CDraw Draw; }