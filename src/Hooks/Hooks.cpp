#include "Hooks.h"
#include "../Features/Misc/Misc.h"
#include "../Features/ESP/ESP.h"

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
	C_BaseEntity* pLocal = static_cast<C_BaseEntity*>(I::ClientEntityList->GetClientEntity(g_Globals.m_nLocalIndex));

	if (pLocal && !pLocal->IsDormant() && pLocal->IsAlive())
	{
		F::Misc.Bunnyhop(pLocal, cmd);
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
			G::Draw.String(EFonts::DEBUG, 5, 5, { 204, 204, 204, 255 }, TXT_DEFAULT, L"Team Fortress 2: Classic");

			F::ESP.Paint();
		}
		FinishDrawing(I::Surface);
	}
}

void __stdcall H::PostEntityHook()
{
	PostEntityOriginal(I::Client);

	g_Globals.m_nLocalIndex = I::EngineClient->GetLocalPlayer();
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
	if (!strcmp("HudScope", I::Panel->GetName(vguiPanel)))
		return;

	PaintPanelOriginal(I::Panel, vguiPanel, force_repaint, allow_force);
}
