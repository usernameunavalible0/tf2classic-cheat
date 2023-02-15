#include "Aimbot.h"

void CAimbot::Run(C_BaseEntity* pLocal, CUserCmd* pCommand)
{
	//gCvars.iAimbotIndex = -1;

	if (!Vars::Aimbot::Enabled.m_Var)
		return;

	if (!GetAsyncKeyState(Vars::Aimbot::AimKey.m_Var))
		return;

	C_BaseCombatWeapon* pWeapon = pLocal->GetActiveWeapon();

	if (!pWeapon)
		return;

	C_BaseEntity* pEntity = static_cast<C_BaseEntity*>(I::ClientEntityList->GetClientEntity(GetBestTarget(pLocal, pWeapon)));

	if (!pEntity)
		return;

	int iBestHitbox = GetBestHitbox(pLocal, pEntity);

	if (iBestHitbox == -1)
		return;

	Vector vEntity; pEntity->GetHitboxPosition(iBestHitbox, vEntity);

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

	Vector vLocal = pLocal->EyePosition();

	for (int i = 1; i <= I::EngineClient->GetMaxClients(); i++)
	{
		if (i == pLocal->entindex())
			continue;

		C_BaseEntity* pEntity = static_cast<C_BaseEntity*>(I::ClientEntityList->GetClientEntity(i));

		if (!pEntity)
			continue;

		if (pEntity->IsDormant())
			continue;

		if (!pEntity->IsAlive() ||
			pEntity->InLocalTeam())
			continue;

		int iBestHitbox = GetBestHitbox(pLocal, pEntity);

		if (iBestHitbox == -1)
			continue;

		Vector vEntity; pEntity->GetHitboxPosition(iBestHitbox, vEntity); //pEntity->GetWorldSpaceCenter(vEntity);

		//if (!gCvars.PlayerMode[i])
		//	continue;

		if (Vars::Aimbot::IgnoreInvulnerable.m_Var && pEntity->IsInvulnerable())
			continue;

		if (Vars::Aimbot::IgnoreCloaked.m_Var && pEntity->IsCloaked())
			continue;

		float flDistToTarget = (vLocal - vEntity).Lenght();

		if (flDistToTarget < flDistToBest)
		{
			flDistToBest = flDistToTarget;
			iBestTarget = i;
		}

		//if (gCvars.PlayerMode[i] == 2) //always aim at rage targets first
		//	return i;
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
	
	if (!VisPosPlayer(pLocal, pEntity, pLocal->EyePosition(), vBestHitbox2))
		return -1;

	return iBestHitbox;
}
