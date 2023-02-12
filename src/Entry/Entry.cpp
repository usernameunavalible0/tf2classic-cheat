#include "Entry.h"

void CGlobal_Entry::Load()
{
	//Put this here so cheat can be injected on game startup
	while (!GetModuleHandleW(L"mss32.dll"))
		Sleep(100);

	//Interfaces
	{
		I::Client = GetInterface<IBaseClientDLL>("VClient017", "client.dll");
		I::ClientMode = **reinterpret_cast<void***>((*reinterpret_cast<unsigned int**>(I::Client))[10] + 5);
		I::ClientEntityList = GetInterface<IClientEntityList>("VClientEntityList003", "client.dll");
		I::EngineClient = GetInterface<IVEngineClient>("VEngineClient013", "engine.dll");
		I::EngineVGui = GetInterface<IEngineVGui>("VEngineVGui001", "engine.dll");
		I::EngineTrace = GetInterface<IEngineTrace>("EngineTraceClient003", "engine.dll");
		I::Surface = GetInterface<vgui::ISurface>("VGUI_Surface030", "vguimatsurface.dll");
		I::Panel = GetInterface<vgui::IPanel>("VGUI_Panel009", "vgui2.dll");
		I::ModelInfo = GetInterface<IVModelInfoClient>("VModelInfoClient006", "engine.dll");
		I::RenderView = GetInterface<C_RenderView>("VEngineRenderView014", "engine.dll");
		I::GlobalVars = *reinterpret_cast<CGlobalVarsBase**>(g_Pattern.Find("engine.dll", "A1 ? ? ? ? 8B 11 68") + 0x8);
	}

	//Init Draw
	G::Draw.Initialize
	({
		{ "Consolas", 16, FW_DONTCARE, vgui::ISurface::EFontFlags::FONTFLAG_OUTLINE },
		{ "Tahoma", 11, FW_DONTCARE, vgui::ISurface::EFontFlags::FONTFLAG_OUTLINE },
		{ "Arial", 14, FW_DONTCARE, vgui::ISurface::EFontFlags::FONTFLAG_OUTLINE },
		{ "Verdana", 12, FW_DONTCARE, vgui::ISurface::EFontFlags::FONTFLAG_OUTLINE },
		{ "Tahoma", 12, FW_DONTCARE, vgui::ISurface::EFontFlags::FONTFLAG_OUTLINE },
		{ "Consolas", 12, FW_DONTCARE, vgui::ISurface::EFontFlags::FONTFLAG_OUTLINE },
		{ "Verdana", 12, FW_DONTCARE, vgui::ISurface::EFontFlags::FONTFLAG_OUTLINE },
		{ "Arial", 12, FW_DONTCARE, vgui::ISurface::EFontFlags::FONTFLAG_OUTLINE },
		{ "Verdana", 30, FW_HEAVY, vgui::ISurface::EFontFlags::FONTFLAG_OUTLINE | vgui::ISurface::EFontFlags::FONTFLAG_ANTIALIAS }
	});	
	G::Draw.ReloadScreenSize();
	
	//Put this here so cheat can be injected while already in game
	if (I::EngineClient->IsInGame())
		g_Globals.m_nLocalIndex = I::EngineClient->GetLocalPlayer();

	H::Initialize();
}