#include "DrawManager.h"

inline int	V_wcslen(const wchar_t* pwch) { return (int)wcslen(pwch); }

void CDraw::Initialize(const std::vector<CFont>& fonts)
{
	for (const auto& Font : fonts)
		m_Fonts.push_back(Font);

	if (!m_Fonts.empty())
		ReloadFonts();
}

void CDraw::ReloadFonts()
{
	for (auto& v : m_Fonts)
	{
		v.m_hFont = I::Surface->CreateFontA();
		I::Surface->SetFontGlyphSet(v.m_hFont, v.m_szName, v.m_nTall, v.m_nWeight, 0, 0, v.m_nFlags);
	}
}

void CDraw::String(const size_t& font, int x, int y, const Color& clr, const short align, const char* const str, ...)
{
	va_list va_alist;
	char cbuffer[1024] = { '\0' };
	wchar_t wstr[1024] = { '\0' };

	va_start(va_alist, str);
	vsprintf_s(cbuffer, str, va_alist);
	va_end(va_alist);

	wsprintfW(wstr, L"%hs", cbuffer);

	const vgui::HFont fnt = m_Fonts.at(font).m_hFont;

	if (align)
	{
		int w = 0, h = 0;
		I::Surface->GetTextSize(fnt, wstr, w, h);

		if (align & TXT_LEFT)
			x -= w;

		if (align & TXT_TOP)
			y -= h;

		if (align & TXT_CENTERX)
			x -= (w / 2);

		if (align & TXT_CENTERY)
			y -= (h / 2);
	}

	I::Surface->DrawSetTextPos(x, y);
	I::Surface->DrawSetTextFont(fnt);
	I::Surface->DrawSetTextColor(clr);
	I::Surface->DrawPrintText(wstr, V_wcslen(wstr));
}

void CDraw::String(const size_t& font, int x, int y, const Color& clr, const short align, const wchar_t* const str, ...)
{
	va_list va_alist;
	wchar_t wstr[1024] = { '\0' };

	va_start(va_alist, str);
	vswprintf_s(wstr, str, va_alist);
	va_end(va_alist);

	const vgui::HFont fnt = m_Fonts.at(font).m_hFont;

	if (align)
	{
		int w = 0, h = 0;
		I::Surface->GetTextSize(fnt, wstr, w, h);

		if (align & TXT_LEFT)
			x -= w;

		if (align & TXT_TOP)
			y -= h;

		if (align & TXT_CENTERX)
			x -= (w / 2);

		if (align & TXT_CENTERY)
			y -= (h / 2);
	}

	I::Surface->DrawSetTextPos(x, y);
	I::Surface->DrawSetTextFont(fnt);
	I::Surface->DrawSetTextColor(clr);
	I::Surface->DrawPrintText(wstr, V_wcslen(wstr));
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
