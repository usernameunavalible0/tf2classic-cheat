#pragma once
#include "../SDK/SDK.h"

template <class T>
class CVar
{
public:
	T m_Var;
	const wchar_t* m_szDisplayName;
};

namespace Vars
{
	namespace Menu
	{
		inline Rect_t Position = { 100, 100, 800, 420 };
		inline const auto Title = L"Team Fortress 2";
		inline int TitleBarH = 16;

		inline int SpacingX = 8;
		inline int SpacingY = 4;
		inline int SpacingText = 4;

		inline int CheckBoxW = 14;
		inline int CheckBoxH = 14;
		inline int CheckBoxFillSize = 3;

		inline int ButtonW = 90;
		inline int ButtonH = 20;

		inline int ButtonWSmall = 70;
		inline int ButtonHSmall = 16;

		inline int ComboBoxW = 90;
		inline int ComboBoxH = 14;

		inline int InputBoxW = 90;
		inline int InputBoxH = 14;
		inline int InputColorBoxW = 30;

		namespace Colors
		{
			inline Color WindowBackground = { 20, 20, 20, 255 };
			inline Color TitleBar = { 139, 0, 0, 255 };
			inline Color Text = { 255, 255, 255, 190 };
			inline Color Widget = { 20, 20, 20, 255 };
			inline Color WidgetActive = { 70, 70, 70, 255 };
			inline Color OutlineMenu = { 139, 0, 0, 20 };
		}
	}

	namespace Aimbot
	{
		inline CVar<bool> Enabled{ true, L"Enabled" };
		inline CVar<int> Hitbox{ 0, L"Hitbox Num" };
		inline CVar<bool> Autoshoot{ true, L"Autoshoot" };
		inline CVar<int> AimKey{ VK_SHIFT, L"Aim Key" };
		inline CVar<bool> SilentAim{ true, L"Silent Aim" };
		inline CVar<bool> IgnoreInvulnerable{ true, L"Ignore Invulnerable" };
		inline CVar<bool> IgnoreCloaked{ true, L"Ignore Cloaked" };
	}

	namespace ESP
	{
		inline CVar<bool> Enabled{ true, L"Enabled" };
		inline CVar<bool> Outline{ false, L"Outline" };

		namespace Players
		{
			inline CVar<bool> Enabled{ true, L"Enabled" };
			inline CVar<bool> Teammates{ true, L"Draw Teammates" };
			inline CVar<bool> Name{ true, L"Name Text" };
			//inline CVar<bool> Class{ true, L"Class" };
			inline CVar<bool> Health{ false, L"Health Text" };
			inline CVar<bool> HealthBar{ true, L"Health Bar" };
			inline CVar<int> Box{ 2, L"Box" };
		}
	}

	namespace Visuals
	{
		inline CVar<bool> ToolTips{ false, L"Menu tooltips" };
		inline CVar<bool> RemoveScope{ true, L"Remove Scope" };
		inline CVar<bool> RemoveZoom{ true, L"Remove Zoom" };
		inline CVar<int> FieldOfView{ 110, L"Field Of View" };
	}

	namespace Misc
	{
		inline CVar<bool> Bunnyhop{ true, L"Bunnyhop" };
	}
}