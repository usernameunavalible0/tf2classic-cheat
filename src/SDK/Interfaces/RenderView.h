#pragma once
#include "../Globals/Globals.h"

class C_RenderView
{
public:
	void GetMatricesForView(const CViewSetup& view, VMatrix* pWorldToView, VMatrix* pViewToProjection, VMatrix* pWorldToProjection, VMatrix* pWorldToPixels) {
		typedef void(__thiscall* FN)(PVOID, const CViewSetup&, VMatrix*, VMatrix*, VMatrix*, VMatrix*);
		VFunc_Get<FN>(this, 50)(this, view, pWorldToView, pViewToProjection, pWorldToProjection, pWorldToPixels);
	}
};