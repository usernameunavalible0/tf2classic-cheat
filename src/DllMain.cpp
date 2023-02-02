#include "Entry/Entry.h"

DWORD WINAPI MainThread(LPVOID instance)
{
	G::Entry.Load();

	while (!GetAsyncKeyState(VK_F11))
		Sleep(200);

	H::Uninitialize();

	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(instance), 0);
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(instance);

		const HANDLE hMain = CreateThread(nullptr, NULL, MainThread, instance, NULL, nullptr);

		if (hMain)
			CloseHandle(hMain);
	}

	return TRUE;
}