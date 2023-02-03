#include "Entry.h"

void CGlobal_Entry::Load()
{
	//Interfaces
	{
		I::Client = GetInterface<void>("VClient017", "client.dll");
		I::ClientMode = **reinterpret_cast<void***>((*reinterpret_cast<unsigned int**>(I::Client))[10] + 5);
		I::EngineVGui = GetInterface<void>("VEngineVGui001", "engine.dll");
	}

	H::Initialize();
}