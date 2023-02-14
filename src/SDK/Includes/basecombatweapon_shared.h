#pragma once
#include "c_baseentity.h"

class C_BaseCombatWeapon : public C_BaseEntity
{
public:
	M_NETVAR(m_flChargedDamage, float, "CTFSniperRifle", "m_flChargedDamage");
};