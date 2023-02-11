//===========================================================================//
// 
// 
//		A base class for the client-side representation of entities.
//	
//
//===========================================================================//

#ifndef C_BASEENTITY_H
#define C_BASEENTITY_H
#ifdef _WIN32
#pragma once
#endif

#include "../NetVarManager/NetVarManager.h"

// WARNING: Although this class extends from IClientEntity like other classes copy/pasted from SSDK, this class calls things by VFunc Indexes instead of using direct virtual calls.

//-----------------------------------------------------------------------------
// Purpose: Base client side entity object
//-----------------------------------------------------------------------------
class C_BaseEntity : public IClientEntity
{
public:
	inline bool GetTeamNumber()
	{
		return VFunc_Get<int(__thiscall*)(void*)>(this, 74u)(this);
	}

	inline bool InLocalTeam()
	{
		return VFunc_Get<bool(__thiscall*)(void*)>(this, 78u)(this);
	}

	inline int GetHealth()
	{
		return VFunc_Get<int(__thiscall*)(void*)>(this, 106u)(this);
	}

	inline int GetMaxHealth()
	{
		return VFunc_Get<int(__thiscall*)(void*)>(this, 107u)(this);
	}

	inline bool IsAlive()
	{
		return VFunc_Get<bool(__thiscall*)(void*)>(this, 130u)(this);
	}

	inline bool IsPlayer()
	{
		return VFunc_Get<bool(__thiscall*)(void*)>(this, 131u)(this);
	}

	inline bool IsNPC()
	{
		return VFunc_Get<bool(__thiscall*)(void*)>(this, 134u)(this);
	}

	inline bool IsNextBot()
	{
		return VFunc_Get<bool(__thiscall*)(void*)>(this, 135u)(this);
	}

	M_NETVAR(GetFlags, int, "CBasePlayer", "m_fFlags");
	M_NETVAR(GetCollideableMins, Vector, "CBaseEntity", "m_vecMins");
	M_NETVAR(GetCollideableMaxs, Vector, "CBaseEntity", "m_vecMaxs");

	inline bool IsOnGround()
	{
		return (this->GetFlags() & FL_ONGROUND);
	}

	/*inline Vector EyePosition()
	{
		DYNVAR_RETURN(Vector, this, "DT_BasePlayer", "localdata", "m_vecViewOffset[0]") + GetAbsOrigin();
	}

	int GetFlags()
	{
		DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_fFlags");
	}

	inline Vector GetCollideableMins()
	{
		DYNVAR_RETURN(Vector, this, "DT_BaseEntity", "m_Collision", "m_vecMins");
	}

	inline Vector GetCollideableMaxs()
	{
		DYNVAR_RETURN(Vector, this, "DT_BaseEntity", "m_Collision", "m_vecMaxs");
	}

	inline int GetHealth()
	{
		DYNVAR_RETURN(int, this, "DT_BaseObject", "m_iHealth");
	}

	inline int GetMaxHealth()
	{
		DYNVAR_RETURN(int, this, "DT_BaseObject", "m_iMaxHealth");
	}*/
};

#endif