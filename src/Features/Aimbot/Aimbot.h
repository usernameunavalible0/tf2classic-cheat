#pragma once
#include "../Vars.h"

class CAimbot
{
public:

	void Run(C_BaseEntity* pLocal, CUserCmd* pCommand);

private:

	int GetBestTarget(C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon);

	int GetBestHitbox(C_BaseEntity* pLocal, C_BaseEntity* pEntity);
};

namespace F { inline CAimbot Aimbot; }