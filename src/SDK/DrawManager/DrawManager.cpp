#include "DrawManager.h"

void CDraw::String(const size_t& font, int x, int y, const Color& clr, const short align, const char* const str, ...)
{
}

void CDraw::String(const size_t& font, int x, int y, const Color& clr, const short align, const wchar_t* const str, ...)
{

}

void CDraw::Line(const int x, const int y, const int x1, const int y1, const Color& clr)
{
	I::Surface->DrawSetColor(clr);
	I::Surface->DrawLine(x, y, x1, y1);
}

void CDraw::Rect(const int x, const int y, const int w, const int h, const Color& clr)
{
	I::Surface->DrawSetColor(clr);
	I::Surface->DrawFilledRect(x, y, x + w, y + h);
}
