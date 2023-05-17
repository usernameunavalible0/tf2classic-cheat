#include "NoSpread.h"

void CFeatures_Nospread::Think(CUserCmd* pCommand)
{
    static const auto s_pfSharedRandomInt = reinterpret_cast<int(*)(const char*, int, int, int)>(g_Pattern.Find("client.dll", "55 8B EC 83 EC 08 8B 45 14"));
    static const auto s_pfRandomSeed = reinterpret_cast<void(_cdecl*)(unsigned)>(GetProcAddress(GetModuleHandleW(L"vstdlib.dll"), "RandomSeed"));
    static const auto s_pfRandomFloat = reinterpret_cast<float(_cdecl*)(float, float)>(GetProcAddress(GetModuleHandleW(L"vstdlib.dll"), "RandomFloat"));

    C_BaseEntity* pLocal = static_cast<C_BaseEntity*>(I::ClientEntityList->GetClientEntity(g_Globals.m_nLocalIndex));

    if (!pLocal || !pLocal->IsAlive())
        return;

    C_BaseCombatWeapon* pWeapon = pLocal->GetActiveWeapon();

    if (!pWeapon /*|| !pWeapon->HasAnyAmmo()*/)
        return;

    const int nWeaponID = pWeapon->GetWeaponID();

    if (IsNeedleGun(nWeaponID))
    {
        s_pfSharedRandomInt("SelectWeightedSequence", 0, 0, 0);

        int n;
        for (n = 0; n < 6; n++)
            s_pfRandomFloat(-1, 1);

        Vector vSpread =
        {
            (pCommand->viewangles.x - s_pfRandomFloat(-1.5f, 1.5f)),
            (pCommand->viewangles.y - s_pfRandomFloat(-1.5f, 1.5f)),
            0.0f
        };
        ClampAngle(vSpread);

        pCommand->viewangles = vSpread;
    }
    else if (CanWeaponNospread(nWeaponID))
    {
        Vector vForward, vRight, vUp, vFinal;

        ClampAngle(pCommand->viewangles);

        s_pfRandomSeed((pCommand->random_seed & 255));

        const float flX = (s_pfRandomFloat(-0.5f, 0.5f) + s_pfRandomFloat(-0.5f, 0.5f));
        const float flY = (s_pfRandomFloat(-0.5f, 0.5f) + s_pfRandomFloat(-0.5f, 0.5f));
        const float flSpread = (pWeapon->GetWeaponSpread());

        AngleVectors(pCommand->viewangles, &vForward, &vRight, &vUp);

        Vector vNewAngles = vForward + (vRight * (flX * flSpread)) + (vUp * (flY * flSpread));
        vNewAngles.Normalize();

        VectorAngles(vNewAngles, vFinal);
        ClampAngle(vFinal);

        Vector vSpreadAngles = (pCommand->viewangles + (pCommand->viewangles - vFinal));
        ClampAngle(vSpreadAngles);

        pCommand->viewangles = vSpreadAngles;
    }
}

bool CFeatures_Nospread::CanWeaponNospread(const int nWeaponID)
{
    switch (nWeaponID)
    {
    case TF_WEAPON_ASSAULTRIFLE:
    case TF_WEAPON_SMG:
    case TF_WEAPON_PISTOL:
    case TF_WEAPON_PISTOL_SCOUT:
    case TF_WEAPON_REVOLVER:
    case TF_WEAPON_MINIGUN:
    {
        return true;
    }

    default: break;
    }

    return false;
}

bool CFeatures_Nospread::IsNeedleGun(const int nWeaponID)
{
    switch (nWeaponID)
    {
    case TF_WEAPON_NAILGUN:
    case TF_WEAPON_SYRINGEGUN_MEDIC:
    {
        return true;
    }

    default: break;
    }

    return false;
}
