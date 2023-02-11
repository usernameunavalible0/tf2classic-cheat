#pragma once
#include "RenderView.h"

//GetInterface
template <typename T>
static T* GetInterface(const char* name, const char* library)
{
	const HINSTANCE handle = GetModuleHandle(library);

	if (!handle)
		return nullptr;

	using FN = T * (*)(const char*, int*);
	const FN CreateInterface = reinterpret_cast<FN>(GetProcAddress(handle, "CreateInterface"));

	return CreateInterface(name, nullptr);
}

namespace I {
	inline IBaseClientDLL* Client = nullptr;
	inline void* ClientMode = nullptr;
	inline IEngineVGui* EngineVGui = nullptr;
	inline vgui::ISurface* Surface = nullptr;
	inline CGlobalVarsBase* GlobalVars = nullptr;
	inline IClientEntityList* ClientEntityList = nullptr;
	inline IVEngineClient* EngineClient = nullptr;
	inline vgui::IPanel* Panel = nullptr;
	inline IVModelInfoClient* ModelInfo = nullptr;
	inline C_RenderView* RenderView = nullptr;
}