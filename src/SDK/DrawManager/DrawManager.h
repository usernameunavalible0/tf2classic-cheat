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
	void OutlinedRect(const int x, const int y, const int w, const int h, const Color& clr);
	void CornerRect(const int x, const int y, const int w, const int h, const int _x, const int _y, const Color color);

	void ReloadScreenSize();
	void ReloadMatrix();
};

namespace G { inline CDraw Draw; }

#define TXT_DEFAULT		(1 << 0)
#define TXT_LEFT		(1 << 1)
#define TXT_TOP			(1 << 2)
#define TXT_CENTERX		(1 << 3)
#define TXT_CENTERY		(1 << 4)
#define TXT_CENTERXY	TXT_CENTERX | TXT_CENTERY

#pragma warning (disable:4244)

inline bool W2S(const Vector& vOrigin, Vector2D& vScreen)
{
	const matrix3x4_t& worldToScreen = g_Globals.WorldToProjection.As3x4();

	float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3];

	if (w > 0.001)
	{
		float fl1DBw = 1 / w;
		vScreen.x = (g_Globals.m_nScreenWidht / 2) + (0.5 * ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * fl1DBw) * g_Globals.m_nScreenWidht + 0.5);
		vScreen.y = (g_Globals.m_nScreenHeight / 2) - (0.5 * ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * fl1DBw) * g_Globals.m_nScreenHeight + 0.5);
		return true;
	}

	return false;
}