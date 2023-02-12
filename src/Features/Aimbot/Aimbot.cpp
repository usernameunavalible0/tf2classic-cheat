#include "Aimbot.h"

void CAimbot::Run(C_BaseEntity* pLocal, CUserCmd* pCommand)
{
	//gCvars.iAimbotIndex = -1;

	if (!Vars::Aimbot::Enabled)
		return;

	if (!GetAsyncKeyState(Vars::Aimbot::AimKey))
		return;

	//if (!pLocal->GetActiveWeapon())
	//	return;

	C_BaseEntity* pEntity = static_cast<C_BaseEntity*>(I::ClientEntityList->GetClientEntity(GetBestTarget(pLocal)));

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

	if (Vars::Aimbot::SilentAim)
	{
		FixMovement(vAngs, pCommand);
		pCommand->viewangles = vAngs;
	}
	else
	{
		pCommand->viewangles = vAngs;
		I::EngineClient->SetViewAngles(pCommand->viewangles);
	}

	if (Vars::Aimbot::Autoshoot)
		pCommand->buttons |= IN_ATTACK;
}

int CAimbot::GetBestTarget(C_BaseEntity* pLocal)
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

		if (pEntity->IsInvulnerable() || pEntity->IsCloaked())
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

	if (!Vars::Aimbot::Hitbox)
	{
		if (pLocal->m_iClass() == TF_CLASS_SNIPER)
			iBestHitbox = 0;
		else
			iBestHitbox = 4;
	}
	else
	{
		iBestHitbox = Vars::Aimbot::Hitbox - 1;
	}

	if (Vars::Aimbot::Enabled)
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
