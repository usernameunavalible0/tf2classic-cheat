#include "Hooks.h"

void H::Initialize()
{
	MH_Initialize();

	//Define Hooks Here
	MH_CreateHook(
		(*static_cast<void***>(I::ClientMode))[21],
		&CreateMoveHook,
		reinterpret_cast<void**>(&CreateMoveOriginal)
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
