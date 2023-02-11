#include "ESP.h"

Color OutlineColor = { 0, 0, 0, 180 };
Color CondColor = { 254, 202, 87, 255 };
Color TargetColor = { 153, 128, 250, 255 };
Color InvulnColor = { 59, 59, 152, 255 };
Color CloakColor = { 165, 177, 194, 255 };
Color FriendColor = { 152, 255, 152, 255 };
Color OverhealColor = { 84, 160, 255, 255 };

Color HealthColor = { 0, 230, 64, 255 };
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
	if (!bActive)
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

		if (bPlayers)
		{
			for (int n = 1; n < I::ClientEntityList->GetHighestEntityIndex(); n++)
			{
				C_BaseEntity* Player = static_cast<C_BaseEntity*>(I::ClientEntityList->GetClientEntity(n));

				if (!Player || Player->IsDormant())
					continue;

				if (!Player->IsPlayer() && !Player->IsNextBot() && !Player->IsNPC())
					continue;

				if (Player == pLocal)
					continue;

				if (!Player->IsAlive())
					continue;

				bool bIsFriend = false;

				switch (nNoTeammatePlayers)
				{
				case 0: { break; }
				case 1: { if (Player->InLocalTeam()) { continue; } break; }
				case 2: { if (Player->InLocalTeam() && !bIsFriend) { continue; } break; }
				}

				int x = 0, y = 0, w = 0, h = 0;

				if (GetDrawBounds(Player, x, y, w, h))
				{
					Color DrawColor = GetDrawColor(pLocal, Player);
					Color HealthColor = GetHealthColor(Player->GetHealth(), Player->GetMaxHealth());

					int nTextX = ((x + w) + 3);
					int nTextOffset = 0;

					if (bPlayerName)
					{
						PlayerInfo_t PlayerInfo = {};

						if (I::EngineClient->GetPlayerInfo(Player->entindex(), &PlayerInfo))
						{
							auto str = ConvertUtf8ToWide(PlayerInfo.name);

							int offset = G::Draw.m_Fonts.at(EFonts::ESP).m_nTall;
							G::Draw.String(EFonts::ESP_NAME, (x + (w / 2)), (y - offset), DrawColor, TXT_CENTERXY, str.c_str());
						}
					}

					if (bPlayerHealth)
					{
						G::Draw.String(EFonts::ESP, nTextX, (y + nTextOffset), HealthColor, TXT_DEFAULT, "%d/%d", Player->GetHealth(), Player->GetMaxHealth());
						nTextOffset += G::Draw.m_Fonts.at(EFonts::ESP).m_nTall;
					}

					if (bPlayerHealthBar)
					{
						float nHealth = static_cast<float>(Player->GetHealth());
						float nMaxHealth = 100.0f; //Entity's max health
						float overheal = 0.0f;

						if (nHealth > nMaxHealth) {
							overheal = fmod(nHealth, nMaxHealth);
							nHealth = nMaxHealth;
						}

						static const int nWidth = 2;
						int nHeight = (h + (nHealth < nMaxHealth ? 2 : 1));
						int nHeight2 = (h + 1);

						float ratio = (nHealth / nMaxHealth);

						G::Draw.Rect(((x - nWidth) - 2), y, nWidth, nHeight2, OutlineColor);
						G::Draw.Rect(((x - nWidth) - 2), (y + nHeight - (nHeight * ratio)), nWidth, (nHeight * ratio), HealthColor);

						if (bOutline)
							G::Draw.OutlinedRect(((x - nWidth) - 3), (y - 1), (nWidth + 2), (nHeight2 + 2), OutlineColor);

						if (overheal > 0.0f) {
							ratio = (overheal / nMaxHealth);
							G::Draw.Rect(((x - nWidth) - 2), (y + (nHeight + 1) - (nHeight * ratio)), nWidth, (nHeight * ratio), OverhealColor);
						}
					}

					if (nPlayerBox)
					{
						if (nPlayerBox == 1)
						{
							int height = (h + 1); //don't ask me /shrug

							G::Draw.OutlinedRect(x, y, w, height, DrawColor);
							if (bOutline)
								G::Draw.OutlinedRect((x - 1), (y - 1), (w + 2), (height + 2), OutlineColor);
						}

						else if (nPlayerBox == 2)
						{
							G::Draw.CornerRect(x, y, w, h, 3, 5, DrawColor);
							if (bOutline)
								G::Draw.CornerRect((x - 1), (y - 1), (w + 2), (h + 2), 3, 5, OutlineColor);
						}
					}
				}
			}
		}
	}
}