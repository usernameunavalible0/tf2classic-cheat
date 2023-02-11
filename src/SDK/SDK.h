#pragma once
#include "DrawManager/DrawManager.h"
#include "../../ext/MinHook/MinHook.h"
#include "Includes/c_baseentity.h"

inline Color GetTeamColor(const int nTeam)
{
	if (nTeam == 2)
		return { 175, 73, 73, 255 };
	else if (nTeam == 3)
		return { 79, 117, 143, 255 };
	else
		return { 245, 229, 196, 255 };
}

inline Color GetHealthColor(const int nHealth, const int nMaxHealth)
{
	if (nHealth > nMaxHealth)
		return { 153, 204, 255, 255 };

	const int nHP = max(0, min(nHealth, nMaxHealth));

	const unsigned __int32 nR = static_cast<unsigned __int32>(min((510 * (nMaxHealth - nHP)) / nMaxHealth, 200));
	const unsigned __int32 nG = static_cast<unsigned __int32>(min((510 * nHP) / nMaxHealth, 200));

	return { static_cast<byte>(nR), static_cast<byte>(nG), 0u, 255u };
}