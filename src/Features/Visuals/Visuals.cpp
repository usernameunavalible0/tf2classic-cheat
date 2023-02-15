#include "Visuals.h"

void CVisuals::FOV(CViewSetup* pView)
{
	C_BaseEntity* pLocal = static_cast<C_BaseEntity*>(I::ClientEntityList->GetClientEntity(g_Globals.m_nLocalIndex));

	if (pLocal && !pLocal->IsDormant() && pView)
	{
		if (pLocal->GetObserverMode() == OBS_MODE_FIRSTPERSON || (pLocal->IsScoped() && !Vars::Visuals::RemoveScope.m_Var))
			return;

		pView->fov = Vars::Visuals::FieldOfView.m_Var;

		if (pLocal->IsAlive())
			pLocal->m_iFOV() = Vars::Visuals::FieldOfView.m_Var;
	}
}
