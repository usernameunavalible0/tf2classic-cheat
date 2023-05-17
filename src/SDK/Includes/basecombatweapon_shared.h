#pragma once
#include "c_baseentity.h"

class C_BaseCombatWeapon : public C_BaseEntity
{
public:
	M_NETVAR(m_iClip1, int, "CBaseCombatWapon", "m_iClip1");
	M_NETVAR(m_flChargedDamage, float, "CTFSniperRifle", "m_flChargedDamage");

public:
	inline int GetWeaponID()
	{
		return VFunc_Get<int(__thiscall*)(void*)>(this, 372u)(this);
	}

	inline float GetWeaponSpread()
	{
		return VFunc_Get<float(__thiscall*)(void*)>(this, 424u)(this);
	}
};