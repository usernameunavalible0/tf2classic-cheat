#include "Entry.h"

void CGlobal_Entry::Load()
{
	//Interfaces
	{
		I::Client = GetInterface<void>("VClient017", "client.dll");
		I::ClientMode = **reinterpret_cast<void***>((*reinterpret_cast<unsigned int**>(I::Client))[10] + 5);
		I::ClientEntityList = GetInterface<IClientEntityList>("VClientEntityList003", "client.dll");
		I::EngineClient = GetInterface<IVEngineClient>("VEngineClient013", "engine.dll");
		I::EngineVGui = GetInterface<IEngineVGui>("VEngineVGui001", "engine.dll");
		I::Surface = GetInterface<vgui::ISurface>("VGUI_Surface030", "vguimatsurface.dll");
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

	H::Initialize();
}