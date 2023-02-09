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

#include "../NetVar/NetVar.h"

// WARNING: Although this class extends from IClientEntity like other classes copy/pasted from SSDK, this class calls things by VFunc Indexes instead of using direct virtual calls.

//-----------------------------------------------------------------------------
// Purpose: Base client side entity object
//-----------------------------------------------------------------------------
class C_BaseEntity : public IClientEntity
{
public:
	inline bool InLocalTeam()
	{
		return VFunc_Get<bool(__thiscall*)(void*)>(this, 78u)(this);
	}

	inline bool IsAlive()
	{
		return VFunc_Get<bool(__thiscall*)(void*)>(this, 130u)(this);
	}

	inline bool IsPlayer()
	{
		return VFunc_Get<bool(__thiscall*)(void*)>(this, 131u)(this);
	}

	inline Vector EyePosition()
	{
		return VFunc_Get<Vector(__thiscall*)(void*)>(this, 141u)(this);
	}

	int GetFlags()
	{
		DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_fFlags");
	}

	inline bool IsOnGround()
	{
		return (this->GetFlags() & FL_ONGROUND);
	}
};

#endif