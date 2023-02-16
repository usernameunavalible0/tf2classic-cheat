#include "ESP.h"

Color OutlineColor = { 0, 0, 0, 180 };
Color CondColor = { 254, 202, 87, 255 };
Color TargetColor = { 153, 128, 250, 255 };
Color InvulnColor = { 59, 59, 152, 255 };
Color CloakColor = { 165, 177, 194, 255 };
Color FriendColor = { 152, 255, 152, 255 };
Color OverhealColor = { 84, 160, 255, 255 };

Color AmmoColor = { 191, 191, 191, 255 };

std::wstring CESP::ConvertUtf8ToWide(const std::string& str)
{
	int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
	std::wstring wstr(count, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], count);
	return wstr;
}

bool CESP::ShouldRun()
{
	if (!Vars::ESP::Enabled.m_Var)
		return false;

	if (!I::EngineClient->IsInGame() || !I::EngineClient->IsConnected() || I::EngineClient->Con_IsVisible())
		return false;

	if (I::EngineVGui->IsGameUIVisible())
		return false;

	return true;
}

bool CESP::GetDrawBounds(C_BaseEntity* pEntity, int& x, int& y, int& w, int& h)
{
	if (/*!gInts.GameMovement || */!pEntity)
		return false;

	const matrix3x4_t& transform = pEntity->RenderableToWorldTransform();

	Vector mins = pEntity->GetCollideableMins();
	Vector maxs = pEntity->GetCollideableMaxs();

	Vector points[] = {
		Vector(mins.x, mins.y, mins.z),
		Vector(mins.x, maxs.y, mins.z),
		Vector(maxs.x, maxs.y, mins.z),
		Vector(maxs.x, mins.y, mins.z),
		Vector(maxs.x, maxs.y, maxs.z),
		Vector(mins.x, maxs.y, maxs.z),
		Vector(mins.x, mins.y, maxs.z),
		Vector(maxs.x, mins.y, maxs.z)
	};

	Vector transformed_points[8];

	for (int i = 0; i < 8; i++)
		VectorTransform(points[i], transform, transformed_points[i]);

	Vector2D flb, brt, blb, frt, frb, brb, blt, flt;

	if (W2S(transformed_points[3], flb) && W2S(transformed_points[5], brt)
		&& W2S(transformed_points[0], blb) && W2S(transformed_points[4], frt)
		&& W2S(transformed_points[2], frb) && W2S(transformed_points[1], brb)
		&& W2S(transformed_points[6], blt) && W2S(transformed_points[7], flt)
		&& W2S(transformed_points[6], blt) && W2S(transformed_points[7], flt))
	{
		Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

		float left = flb.x;
		float top = flb.y;
		float righ = flb.x;
		float bottom = flb.y;

		for (int n = 1; n < 8; n++) {
			if (left > arr[n].x)
				left = arr[n].x;

			if (top < arr[n].y)
				top = arr[n].y;

			if (righ < arr[n].x)
				righ = arr[n].x;

			if (bottom > arr[n].y)
				bottom = arr[n].y;
		}

		float x_ = left;
		float y_ = bottom;
		float w_ = (righ - left);
		float h_ = (top - bottom);

		if (pEntity->IsPlayer()) {
			x_ += ((righ - left) / 8.0f);
			w_ -= (((righ - left) / 8.0f) * 2.0f);
		}

		x = static_cast<int>(x_);
		y = static_cast<int>(y_);
		w = static_cast<int>(w_);
		h = static_cast<int>(h_);

		if (x > g_Globals.m_nScreenWidht || (x + w) < 0 || y > g_Globals.m_nScreenHeight || (y + h) < 0)
			return false;

		return true;
	}

	return false;
}

Color CESP::GetDrawColor(C_BaseEntity* pLocal, C_BaseEntity* pEntity)
{
	Color out = GetTeamColor(pEntity->GetTeamNumber());

	//instead of the team color let's give it the friend's color, let's keep all the other overrides
	//if (pLocal->IsPlayerOnSteamFriendList(pEntity))
	//	out = FriendColor;

	//target color should override all others
	//if (pEntity->GetIndex() == gGlobalInfo.nCurrentTargetIdx)
	//	out = TargetColor;

	return out;
}

void CESP::Paint()
{
	C_BaseEntity* pLocal = static_cast<C_BaseEntity*>(I::ClientEntityList->GetClientEntity(g_Globals.m_nLocalIndex));
	if (pLocal)
	{
		if (!ShouldRun())
			return;

		int x, y, w, h;
		if (Vars::ESP::Players::Enabled.m_Var)
		{
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
					if (!Vars::ESP::Players::Enabled.m_Var)
						break;

					C_BaseEntity* pPlayer = static_cast<C_BaseEntity*>(pEntity);

					if (!pPlayer->IsAlive() || (!Vars::ESP::Players::Teammates.m_Var && pPlayer->InLocalTeam()))
						break;

					if (!GetDrawBounds(pPlayer, x, y, w, h))
						break;

					const int nHealth = pPlayer->GetHealth();
					const int nMaxHealth = pPlayer->GetMaxHealth();

					const Color clrHealth = GetHealthColor(nHealth, nMaxHealth);
					const Color clrTeam = GetTeamColor(pPlayer->GetTeamNumber());

					const int nDrawX = (x + w) + 3;
					int nDrawY = y;

					if (Vars::ESP::Players::Name.m_Var)
					{
						PlayerInfo_t PlayerInfo = {};

						if (I::EngineClient->GetPlayerInfo(pPlayer->entindex(), &PlayerInfo))
						{
							auto str = ConvertUtf8ToWide(PlayerInfo.name);

							int offset = G::Draw.m_Fonts.at(EFonts::ESP_NAME).m_nTall;
							G::Draw.String(EFonts::ESP_NAME, (x + (w / 2)), (y - offset), clrTeam, TXT_CENTERX, str.c_str());
						}
					}

					if (Vars::ESP::Players::Health.m_Var)
					{
						G::Draw.String(EFonts::ESP, nDrawX, nDrawY, clrHealth, TXT_DEFAULT, "%d/%d", pPlayer->GetHealth(), pPlayer->GetMaxHealth());
						nDrawY += G::Draw.m_Fonts.at(EFonts::ESP).m_nTall;
					}

					if (Vars::ESP::Players::HealthBar.m_Var)
					{
						x -= 1;

						const float flMaxHealth = static_cast<float>(nMaxHealth);
						const float flHealth = std::clamp<float>(static_cast<float>(nHealth), 1.0f, flMaxHealth);

						static const int nWidth = 2;
						const int nHeight = (h + (flHealth < flMaxHealth ? 2 : 1));
						const int nHeight2 = (h + 1);

						const float ratio = (flHealth / flMaxHealth);
						G::Draw.Rect(static_cast<int>(((x - nWidth) - 2)), static_cast<int>((y + nHeight - (nHeight * ratio))), nWidth, static_cast<int>((nHeight * ratio)), clrHealth);

						if (Vars::ESP::Outline.m_Var)
							G::Draw.OutlinedRect(static_cast<int>(((x - nWidth) - 2) - 1), static_cast<int>((y + nHeight - (nHeight * ratio)) - 1), nWidth + 2, static_cast<int>((nHeight * ratio) + 1), OutlineColor);

						x += 1;
					}

					if (Vars::ESP::Players::Box.m_Var)
					{
						if (Vars::ESP::Players::Box.m_Var == 1)
						{
							int height = (h + 1); //don't ask me /shrug

							G::Draw.OutlinedRect(x, y, w, height, clrTeam);
							if (Vars::ESP::Outline.m_Var)
								G::Draw.OutlinedRect((x - 1), (y - 1), (w + 2), (height + 2), OutlineColor);
						}

						else if (Vars::ESP::Players::Box.m_Var == 2)
						{
							G::Draw.CornerRect(x, y, w, h, 3, 5, clrTeam);
							if (Vars::ESP::Outline.m_Var)
								G::Draw.CornerRect((x - 1), (y - 1), (w + 2), (h + 2), 3, 5, OutlineColor);
						}
					}

					break;
				}

				case ETFClassIds::CObjectTeleporter:
				case ETFClassIds::CObjectDispenser:
				case ETFClassIds::CObjectSentrygun:
				{
					if (!Vars::ESP::Buildings::Enabled.m_Var)
						break;

					C_BaseEntity* pBuilding = static_cast<C_BaseEntity*>(pEntity);

					if (!pBuilding->IsAlive() || (!Vars::ESP::Buildings::LocalTeam.m_Var && pBuilding->InLocalTeam()))
						break;

					if (!GetDrawBounds(pBuilding, x, y, w, h))
						break;

					const int nHealth = pBuilding->GetHealth();
					const int nMaxHealth = pBuilding->GetMaxHealth();

					const Color clrHealth = GetHealthColor(nHealth, nMaxHealth);
					const Color clrTeam = GetTeamColor(pBuilding->GetTeamNumber());

					const int nDrawX = x + (w / 2);
					int nDrawY = y + (h / 2);

					if (Vars::ESP::Buildings::Type.m_Var)
					{
						// this is probably bad method
						if (pCC->m_ClassID == ETFClassIds::CObjectTeleporter)
							G::Draw.String(EFonts::ESP_NAME, nDrawX, nDrawY, clrTeam, TXT_CENTERXY, L"teleporter");
						else if (pCC->m_ClassID == ETFClassIds::CObjectDispenser)
							G::Draw.String(EFonts::ESP_NAME, nDrawX, nDrawY, clrTeam, TXT_CENTERXY, L"dispenser");
						else if (pCC->m_ClassID == ETFClassIds::CObjectSentrygun)
							G::Draw.String(EFonts::ESP_NAME, nDrawX, nDrawY, clrTeam, TXT_CENTERXY, L"sentrygun");

						nDrawY += G::Draw.m_Fonts.at(EFonts::ESP_NAME).m_nTall;
					}

					if (Vars::ESP::Buildings::Health.m_Var)
					{
						G::Draw.String(EFonts::ESP, nDrawX, nDrawY, clrHealth, TXT_CENTERXY, L"%i / %ihp", nHealth, nMaxHealth);
						nDrawY += G::Draw.m_Fonts.at(EFonts::ESP).m_nTall;
					}

					if (Vars::ESP::Buildings::HealthBar.m_Var)
					{
						x -= 1;

						const float flMaxHealth = static_cast<float>(nMaxHealth);
						const float flHealth = std::clamp<float>(static_cast<float>(nHealth), 1.0f, flMaxHealth);

						static const int nWidth = 2;
						const int nHeight = (h + (flHealth < flMaxHealth ? 2 : 1));
						const int nHeight2 = (h + 1);

						const float ratio = (flHealth / flMaxHealth);
						G::Draw.Rect(static_cast<int>(((x - nWidth) - 2)), static_cast<int>((y + nHeight - (nHeight * ratio))), nWidth, static_cast<int>((nHeight* ratio)), clrHealth);
						if (Vars::ESP::Outline.m_Var)
							G::Draw.OutlinedRect(static_cast<int>(((x - nWidth) - 2) - 1), static_cast<int>((y + nHeight - (nHeight * ratio)) - 1), nWidth + 2, static_cast<int>((nHeight* ratio) + 1), OutlineColor);

						x += 1;
					}

					if (Vars::ESP::Buildings::Box.m_Var)
					{
						if (Vars::ESP::Buildings::Box.m_Var == 1)
						{
							int height = (h + 1); //don't ask me /shrug

							G::Draw.OutlinedRect(x, y, w, height, clrTeam);
							if (Vars::ESP::Outline.m_Var)
								G::Draw.OutlinedRect((x - 1), (y - 1), (w + 2), (height + 2), OutlineColor);
						}

						else if (Vars::ESP::Buildings::Box.m_Var == 2)
						{
							G::Draw.CornerRect(x, y, w, h, 3, 5, clrTeam);
							if (Vars::ESP::Outline.m_Var)
								G::Draw.CornerRect((x - 1), (y - 1), (w + 2), (h + 2), 3, 5, OutlineColor);
						}
					}

					break;
				}

				case ETFClassIds::CTFAmmoPack:
				{
					if (!Vars::ESP::DrawHealthAndAmmo.m_Var)
						break;

					C_BaseEntity* pAmmoPack = static_cast<C_BaseEntity*>(pEntity);

					Vector2D sPos;
					if (!W2S(pAmmoPack->WorldSpaceCenter(), sPos))
						break;

					G::Draw.String(EFonts::ESP, sPos.x, sPos.y, { 204, 204, 204, 255 }, TXT_CENTERXY, L"ammo");

					break;
				}

				case ETFClassIds::CBaseAnimating:
				{
					if (!Vars::ESP::DrawHealthAndAmmo.m_Var)
						break;

					C_BaseEntity* pAnimated = static_cast<C_BaseEntity*>(pEntity);

					const int nModelIndex = pAnimated->m_nModelIndex();

					Vector2D sPos;
					if (IsAmmo(nModelIndex) && W2S(pAnimated->WorldSpaceCenter(), sPos))
					{
						G::Draw.String(EFonts::ESP, sPos.x, sPos.y, { 204, 204, 204, 255 }, TXT_CENTERXY, L"ammo");
						break;
					}

					if (IsHealth(nModelIndex) && W2S(pAnimated->WorldSpaceCenter(), sPos))
					{
						G::Draw.String(EFonts::ESP, sPos.x, sPos.y, { 204, 204, 204, 255 }, TXT_CENTERXY, L"health");
						break;
					}

					break;
				}

				default: break;
				}
			}
		}
	}
}

bool CESP::IsAmmo(const int nModelIndex)
{
	size_t n; const size_t nMax = m_vecAmmo.size();
	for (n = 0; n < nMax; n++)
	{
		if (m_vecAmmo[n] == nModelIndex)
			return true;
	}

	return false;
}

bool CESP::IsHealth(const int nModelIndex)
{
	size_t n; const size_t nMax = m_vecHealth.size();
	for (n = 0; n < nMax; n++)
	{
		if (m_vecHealth[n] == nModelIndex)
			return true;
	}

	return false;
}