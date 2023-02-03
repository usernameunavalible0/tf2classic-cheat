//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#ifndef ISURFACE_H
#define ISURFACE_H

#ifdef _WIN32
#pragma once
#endif

#include "Color.h"

class ITexture;

namespace vgui
{

	class IImage;
	class Image;
	class Point;

	// handles
	typedef unsigned long HCursor;
	typedef unsigned long HTexture;
	typedef unsigned long HFont;


	enum FontDrawType_t
	{
		// Use the "additive" value from the scheme file
		FONT_DRAW_DEFAULT = 0,

		// Overrides
		FONT_DRAW_NONADDITIVE,
		FONT_DRAW_ADDITIVE,

		FONT_DRAW_TYPE_COUNT = 2,
	};

	struct IntRect
	{
		int x0;
		int y0;
		int x1;
		int y1;
	};

	//-----------------------------------------------------------------------------
	// Purpose: Wraps contextless windows system functions
	//-----------------------------------------------------------------------------
	class ISurface
	{
	public:
		//VFuncs from AppFramework
		virtual void Unused_1() = 0;
		virtual void Unused_2() = 0;
		virtual void Unused_3() = 0;
		virtual void Unused_4() = 0;;

		// call to Shutdown surface; surface can no longer be used after this is called
		virtual void Shutdown() = 0;

		// frame
		virtual void RunFrame() = 0;

		// hierarchy root
		virtual unsigned int GetEmbeddedPanel() = 0;
		virtual void SetEmbeddedPanel(unsigned int pPanel) = 0;

		// drawing context
		virtual void PushMakeCurrent(unsigned int panel, bool useInsets) = 0;
		virtual void PopMakeCurrent(unsigned int panel) = 0;

		// rendering functions
		virtual void DrawSetColor(int r, int g, int b, int a) = 0;
		virtual void DrawSetColor(Color col) = 0;

		virtual void DrawFilledRect(int x0, int y0, int x1, int y1) = 0;
		virtual void DrawFilledRectArray(IntRect* pRects, int numRects) = 0;
		virtual void DrawOutlinedRect(int x0, int y0, int x1, int y1) = 0;

		virtual void DrawLine(int x0, int y0, int x1, int y1) = 0;
		virtual void DrawPolyLine(int* px, int* py, int numPoints) = 0;

		virtual void DrawSetTextFont(HFont font) = 0;
		virtual void DrawSetTextColor(int r, int g, int b, int a) = 0;
		virtual void DrawSetTextColor(Color col) = 0;
		virtual void DrawSetTextPos(int x, int y) = 0;
		virtual void DrawGetTextPos(int& x, int& y) = 0;
		virtual void DrawPrintText(const wchar_t* text, int textLen, FontDrawType_t drawType = FONT_DRAW_DEFAULT) = 0;
		virtual void DrawUnicodeChar(wchar_t wch, FontDrawType_t drawType = FONT_DRAW_DEFAULT) = 0;

	};

}
#endif // ISURFACE_H