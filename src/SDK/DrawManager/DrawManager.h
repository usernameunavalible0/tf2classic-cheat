#pragma once
#include "../Interfaces/Interfaces.h"
#include <vector>

enum EFonts
{
	DEBUG,
	ESP,
	ESP_NAME,
	ESP_WEAPON,
	MENU_TAHOMA,
	MENU_CONSOLAS,
	MENU_VERDANA,
	MENU_ARIAL,
	MENU_TAB,

	FONT_LAST
};

class CFont
{
public:
	const char* m_szName;
	int m_nTall;
	int m_nWeight;
	int m_nFlags;
	vgui::HFont m_hFont;
};

class CDraw
{
public:
	std::vector<CFont> m_Fonts;
public:
	void Initialize(const std::vector<CFont>& fonts);
	void ReloadFonts();

public:
	void String(const size_t& font, int x, int y, const Color& clr, const short align, const char* const str, ...);
	void String(const size_t& font, int x, int y, const Color& clr, const short align, const wchar_t* const str, ...);

	void Line(const int x, const int y, const int x1, const int y1, const Color& clr);
	void Rect(const int x, const int y, const int w, const int h, const Color& clr);

	void ReloadMatrix();
};

namespace G { inline CDraw Draw; }

#define TXT_DEFAULT		(1 << 0)
#define TXT_LEFT		(1 << 1)
#define TXT_TOP			(1 << 2)
#define TXT_CENTERX		(1 << 3)
#define TXT_CENTERY		(1 << 4)
#define TXT_CENTERXY	TXT_CENTERX | TXT_CENTERY