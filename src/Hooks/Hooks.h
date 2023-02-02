#pragma once
#include "../SDK/SDK.h"


namespace H
{
	void Initialize();
	void Uninitialize();

	using CreateMove = bool(__thiscall*)(void*, float, CUserCmd*);
	static CreateMove CreateMoveOriginal = nullptr;
	bool __stdcall CreateMoveHook(float frameTime, CUserCmd* cmd);
}