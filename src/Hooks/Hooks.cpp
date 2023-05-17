#include "Hooks.h"
#include "../Features/Misc/Misc.h"
#include "../Features/ESP/ESP.h"
#include "../Features/Aimbot/Aimbot.h"
#include "../Features/Menu/Menu.h"
#include "../Features/Visuals/Visuals.h"
#include "../Features/NoSpread/NoSpread.h"

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

	MH_CreateHook(
		(*reinterpret_cast<void***>(I::Client))[6],
		&PostEntityHook,
		reinterpret_cast<void**>(&PostEntityOriginal)
	);

	MH_CreateHook(
		(*reinterpret_cast<void***>(I::Client))[7],
		&LevelShutdownHook,
		reinterpret_cast<void**>(&LevelShutdownOriginal)
	);

	MH_CreateHook(
		(*reinterpret_cast<void***>(I::Client))[35],
		&FrameStageNotifyHook,
		reinterpret_cast<void**>(&FrameStageNotifyOriginal)
	);

	MH_CreateHook(
		(*reinterpret_cast<void***>(I::Panel))[41],
		&PaintPanelHook,
		reinterpret_cast<void**>(&PaintPanelOriginal)
	);

	MH_CreateHook(
		(*reinterpret_cast<void***>(I::Surface))[111],
		&OSSC_Hook,
		reinterpret_cast<void**>(&OSSC_Original)
	);

	MH_CreateHook(
		(*reinterpret_cast<void***>(I::Surface))[62],
		&LockCursorHook,
		reinterpret_cast<void**>(&LockCursorOriginal)
	);

	MH_CreateHook(
		(*reinterpret_cast<void***>(I::ClientMode))[24],
		&SDVM_Hook,
		reinterpret_cast<void**>(&SDVM_Original)
	);

	MH_CreateHook(
		(*reinterpret_cast<void***>(I::ClientMode))[16],
		&OverrideViewHook,
		reinterpret_cast<void**>(&OverrideViewOriginal)
	);

	MH_EnableHook(MH_ALL_HOOKS);

	//WndProc
	while (!WndProc::hwGame)
	{
		WndProc::hwGame = FindWindowW(nullptr, L"Team Fortress 2 Classic");
		Sleep(100);
	}

	WndProc::oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongW(WndProc::hwGame, GWL_WNDPROC, reinterpret_cast<LONG>(WndProc::Detour)));
}

void H::Uninitialize()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	//WndProc
	if (WndProc::oWndProc)
		SetWindowLongW(WndProc::hwGame, GWL_WNDPROC, reinterpret_cast<LONG>(WndProc::oWndProc));
}

bool __stdcall H::CreateMoveHook(float frameTime, CUserCmd* cmd)
{
	if (!cmd || !cmd->command_number)
		return CreateMoveOriginal(I::ClientMode, frameTime, cmd);

	//Do Stuff
	C_BaseEntity* pLocal = static_cast<C_BaseEntity*>(I::ClientEntityList->GetClientEntity(g_Globals.m_nLocalIndex));

	if (pLocal && !pLocal->IsDormant() && pLocal->IsAlive())
	{
		if (Vars::Misc::Bunnyhop.m_Var)
			F::Misc.Bunnyhop(pLocal, cmd);

		F::Aimbot.Run(pLocal, cmd);

		// NoSpread patched :(
		//F::Nospread.Think(cmd);
	}

	return false;
}

void __stdcall H::PaintHook(int mode)
{
	static auto StartDrawing = reinterpret_cast<void(__thiscall*)(void*)>(g_Pattern.Find("vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14"));
	static auto FinishDrawing = reinterpret_cast<void(__thiscall*)(void*)>(g_Pattern.Find("vguimatsurface.dll", "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00"));

	PaintOriginal(I::EngineVGui, mode);

	if (mode & PaintMode_t::PAINT_UIPANELS)
	{
		G::Draw.ReloadMatrix();

		//Start Drawing
		StartDrawing(I::Surface);
		{
			//Draw Here
			if (!F::Menu.m_bOpen)
				G::Draw.String(EFonts::DEBUG, 5, 5, { 204, 204, 204, 255 }, TXT_DEFAULT, L"Team Fortress 2: Classic");

			F::ESP.Paint();
			F::Menu.Run();
		}
		FinishDrawing(I::Surface);
	}
}

void __stdcall H::PostEntityHook()
{
	PostEntityOriginal(I::Client);

	g_Globals.m_nLocalIndex = I::EngineClient->GetLocalPlayer();

	F::ESP.m_vecAmmo.clear();
	{
		F::ESP.m_vecAmmo.push_back(I::ModelInfo->GetModelIndex("models/items/ammopack_large.mdl"));
		F::ESP.m_vecAmmo.push_back(I::ModelInfo->GetModelIndex("models/items/ammopack_large_bday.mdl"));
		F::ESP.m_vecAmmo.push_back(I::ModelInfo->GetModelIndex("models/items/ammopack_medium.mdl"));
		F::ESP.m_vecAmmo.push_back(I::ModelInfo->GetModelIndex("models/items/ammopack_medium_bday.mdl"));
		F::ESP.m_vecAmmo.push_back(I::ModelInfo->GetModelIndex("models/items/ammopack_small.mdl"));
		F::ESP.m_vecAmmo.push_back(I::ModelInfo->GetModelIndex("models/items/ammopack_small_bday.mdl"));
	}

	F::ESP.m_vecHealth.clear();
	{
		F::ESP.m_vecHealth.push_back(I::ModelInfo->GetModelIndex("models/items/medkit_large.mdl"));
		F::ESP.m_vecHealth.push_back(I::ModelInfo->GetModelIndex("models/items/medkit_large_bday.mdl"));
		F::ESP.m_vecHealth.push_back(I::ModelInfo->GetModelIndex("models/items/medkit_medium.mdl"));
		F::ESP.m_vecHealth.push_back(I::ModelInfo->GetModelIndex("models/items/medkit_medium_bday.mdl"));
		F::ESP.m_vecHealth.push_back(I::ModelInfo->GetModelIndex("models/items/medkit_small.mdl"));
		F::ESP.m_vecHealth.push_back(I::ModelInfo->GetModelIndex("models/items/medkit_small_bday.mdl"));
	}
}

void __stdcall H::LevelShutdownHook()
{
	g_Globals.m_bIsInGame = false;
	g_Globals.m_bIsGameUIVisible = true;

	g_Globals.m_nLocalIndex = -1;
	g_Globals.m_nMaxClients = -1;
	g_Globals.m_nMaxEntities = -1;

	LevelShutdownOriginal(I::Client);
}

void __stdcall H::FrameStageNotifyHook(ClientFrameStage_t frameStage)
{
	FrameStageNotifyOriginal(I::Client, frameStage);

	switch (frameStage)
	{
		case ClientFrameStage_t::FRAME_NET_UPDATE_START:
		{
			g_Globals.m_bIsInGame = I::EngineClient->IsInGame();
			g_Globals.m_bIsGameUIVisible = I::EngineVGui->IsGameUIVisible();

			if (g_Globals.m_bIsInGame)
			{
				g_Globals.m_nMaxClients = I::EngineClient->GetMaxClients();
				g_Globals.m_nMaxEntities = I::ClientEntityList->GetMaxEntities();
			}

			break;
		}
	}
}

void __stdcall H::PaintPanelHook(VPANEL vguiPanel, bool force_repaint, bool allow_force)
{
	if (Vars::Visuals::RemoveScope.m_Var && !strcmp("HudScope", I::Panel->GetName(vguiPanel)))
		return;

	PaintPanelOriginal(I::Panel, vguiPanel, force_repaint, allow_force);
}

void __stdcall H::OSSC_Hook(int oldWidth, int oldHeight)
{
	OSSC_Original(I::Surface, oldWidth, oldHeight);

	G::Draw.ReloadScreenSize();
	G::Draw.ReloadFonts();
}

void __stdcall H::LockCursorHook()
{
	F::Menu.m_bOpen ? I::Surface->UnlockCursor() : LockCursorOriginal(I::Surface);
}

bool __stdcall H::SDVM_Hook()
{
	C_BaseEntity* pLocal = static_cast<C_BaseEntity*>(I::ClientEntityList->GetClientEntity(g_Globals.m_nLocalIndex));
	if (pLocal && !pLocal->IsDormant() && pLocal->IsAlive())
	{
		if (pLocal->IsScoped() && Vars::Visuals::RemoveScope.m_Var && Vars::Visuals::RemoveZoom.m_Var)
			return true;
	}

	return SDVM_Original(I::ClientMode);
}

void __stdcall H::OverrideViewHook(CViewSetup* pSetup)
{
	OverrideViewOriginal(I::ClientMode, pSetup);
	F::Visuals.FOV(pSetup);
}

LRESULT CALLBACK H::WndProc::Detour(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return (F::Menu.m_bOpen && (I::EngineVGui->IsGameUIVisible() || F::Menu.m_bTyping)) ? 1u : CallWindowProcW(oWndProc, hwnd, uMsg, wParam, lParam);
}
