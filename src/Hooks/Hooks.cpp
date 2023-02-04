#include "Hooks.h"

void H::Initialize()
{
	MH_Initialize();

	//Define Hooks Here
	MH_CreateHook(
		(*reinterpret_cast<void***>(I::ClientMode))[21],
		&CreateMoveHook,
		reinterpret_cast<void**>(&CreateMoveOriginal)
	);

	MH_CreateHook(
		(*reinterpret_cast<void***>(I::EngineVGui))[13],
		&PaintHook,
		reinterpret_cast<void**>(&PaintOriginal)
	);

	MH_EnableHook(MH_ALL_HOOKS);
}

void H::Uninitialize()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

bool __stdcall H::CreateMoveHook(float frameTime, CUserCmd* cmd)
{
	if (!cmd || !cmd->command_number)
		return CreateMoveOriginal(I::ClientMode, frameTime, cmd);

	//Do Stuff

	return false;
}

void __stdcall H::PaintHook(int mode)
{
	static auto StartDrawing = reinterpret_cast<void(__thiscall*)(void*)>(g_Pattern.Find("vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14"));
	static auto FinishDrawing = reinterpret_cast<void(__thiscall*)(void*)>(g_Pattern.Find("vguimatsurface.dll", "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00"));

	PaintOriginal(I::EngineVGui, mode);

	if (mode & PaintMode_t::PAINT_UIPANELS)
	{
		//Start Drawing
		StartDrawing(I::Surface);
		{
			//Draw Here
			G::Draw.String(EFonts::DEBUG, 5, 5, { 204, 204, 204, 255 }, TXT_DEFAULT, L"Team Fortress 2: Classic");
		}
		FinishDrawing(I::Surface);
	}
}
