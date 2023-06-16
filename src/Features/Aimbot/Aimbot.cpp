#include "Aimbot.h"

void CAimbot::Run(C_BaseEntity* pLocal, CUserCmd* pCommand)
{
	//gCvars.iAimbotIndex = -1;

	if (!Vars::Aimbot::Enabled.m_Var)
		return;

	if (!GetAsyncKeyState(Vars::Aimbot::AimKey.m_Var))
		return;

	if (!pLocal->GetActiveWeapon())
		return;

	C_BaseEntity* pEntity = static_cast<C_BaseEntity*>(I::ClientEntityList->GetClientEntity(GetBestTarget(pLocal, pLocal->GetActiveWeapon())));

	if (!pEntity)
		return;

	Vector vEntity = {};

	if (pEntity->IsPlayer())
	{
		int iBestHitbox = GetBestHitbox(pLocal, pEntity);

		if (iBestHitbox == -1)
			return;

		vEntity; pEntity->GetHitboxPosition(iBestHitbox, vEntity);
	}
	else
	{
		vEntity = pEntity->WorldSpaceCenter();
	}

	Vector vLocal = pLocal->EyePosition();

	Vector vAngs;
	VectorAngles((vEntity - vLocal), vAngs);

	ClampAngle(vAngs);
	//gCvars.iAimbotIndex = pEntity->GetIndex();

	if (Vars::Aimbot::SilentAim.m_Var)
	{
		FixMovement(vAngs, pCommand);
		pCommand->viewangles = vAngs;
	}
	else
	{
		pCommand->viewangles = vAngs;
		I::EngineClient->SetViewAngles(pCommand->viewangles);
	}

	if (Vars::Aimbot::Autoshoot.m_Var)
		pCommand->buttons |= IN_ATTACK;
}

int CAimbot::GetBestTarget(C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon)
{
	int iBestTarget = -1;
	//this num could be smaller 
	float flDistToBest = 99999.f;

	Vector vEntity = {};
	Vector vLocal = pLocal->EyePosition();

	for (int n = 1; n <= g_Globals.m_nMaxEntities; n++)
	{
		if (n == g_Globals.m_nLocalIndex)
			continue;

		IClientEntity* pEntity = I::ClientEntityList->GetClientEntity(n);

		if (!pEntity || pEntity->IsDormant())
			continue;

		ClientClass* pCC = pEntity->GetClientClass();

		if (!pCC)
			continue;

		switch (pCC->GetClassID())
		{
			case ETFClassIds::CTFPlayer:
			{
				if (!Vars::Aimbot::AimPlayer.m_Var)
					continue;
					
				C_BaseEntity* pPlayer = static_cast<C_BaseEntity*>(pEntity);
	
				if (!pPlayer->IsAlive() || pPlayer->InLocalTeam())
					continue;
	
				int iBestHitbox = GetBestHitbox(pLocal, pPlayer);
	
				if (iBestHitbox == -1)
					continue;

				pPlayer->GetHitboxPosition(iBestHitbox, vEntity); //pEntity->GetWorldSpaceCenter(vEntity);

				if (Vars::Aimbot::IgnoreInvulnerable.m_Var && pPlayer->IsInvulnerable())
					continue;

				if (Vars::Aimbot::IgnoreCloaked.m_Var && pPlayer->IsCloaked())
					continue;

				break;
			}

			case ETFClassIds::CObjectTeleporter:
			case ETFClassIds::CObjectDispenser:
			case ETFClassIds::CObjectSentrygun:
			{
				if (!Vars::Aimbot::AimBuildings.m_Var)
					continue;

				C_BaseEntity* pBuilding = static_cast<C_BaseEntity*>(pEntity);

				if (!pBuilding->IsAlive() || pBuilding->InLocalTeam())
					continue;

				if (!VisPosPlayer(pLocal, pBuilding, pLocal->EyePosition(), pBuilding->WorldSpaceCenter()))
					continue;

				vEntity = pBuilding->WorldSpaceCenter();

				break;
			}

			default: continue;
		}

		Vector vAngles; I::EngineClient->GetViewAngles(vAngles);
		Vector vAngleTo; VectorAngles((vEntity - vLocal), vAngleTo);
		ClampAngle(vAngleTo); //Do we even have to do this?

		float flDistToTarget = (vLocal - vEntity).Lenght();
		float flFOVTo = CalcFov(vAngles, vAngleTo);

		if (Vars::Aimbot::UseFOVRestrict.m_Var && flFOVTo > Vars::Aimbot::AimFov.m_Var)
			continue;

		if (flDistToTarget < flDistToBest)
		{
			flDistToBest = flDistToTarget;
			iBestTarget = n;
		}
	}

	return iBestTarget;
}

int CAimbot::GetBestHitbox(C_BaseEntity* pLocal, C_BaseEntity* pEntity)
{
	int iBestHitbox = -1;

	if (!Vars::Aimbot::Hitbox.m_Var)
	{
		if (pLocal->m_iClass() == TF_CLASS_SNIPER)
			iBestHitbox = 0;
		else
			iBestHitbox = 4;
	}
	else
	{
		iBestHitbox = Vars::Aimbot::Hitbox.m_Var - 1;
	}

	if (Vars::Aimbot::Enabled.m_Var)
	{
		for (int i = 0; i < 17; i++)
		{
			Vector iBox;
			if (pEntity->GetHitboxPosition(i, iBox))
			{
				if (VisPosPlayer(pLocal, pEntity, pLocal->EyePosition(), iBox))
					return i;
			}
		}
	}

	Vector vBestHitbox;
	if (!pEntity->GetHitboxPosition(iBestHitbox, vBestHitbox))
		return -1;

	if (vBestHitbox.IsZero())
		return -1;

	Vector vBestHitbox2;
	if (!pEntity->GetHitboxPosition(iBestHitbox, vBestHitbox2))
		return -1;
	
	if (vBestHitbox2.IsZero())
		return -1;

	if (!VisPosPlayer(pLocal, pEntity, pLocal->EyePosition(), vBestHitbox2))
		return -1;

	return iBestHitbox;
}
