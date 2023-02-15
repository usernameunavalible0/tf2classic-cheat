#pragma once
#include "../SDK/SDK.h"


namespace H
{
	void Initialize();
	void Uninitialize();

	using CreateMove = bool(__thiscall*)(void*, float, CUserCmd*);
	static CreateMove CreateMoveOriginal = nullptr;
	bool __stdcall CreateMoveHook(float frameTime, CUserCmd* cmd);

	using Paint = void(__thiscall*)(void*, int);
	static Paint PaintOriginal = nullptr;
	void __stdcall PaintHook(int mode);

	using LevelInitPostEntity = void(__thiscall*)(void*);
	static LevelInitPostEntity PostEntityOriginal = nullptr;
	void __stdcall PostEntityHook();

	using LevelShutdown = void(__thiscall*)(void*);
	static LevelShutdown LevelShutdownOriginal = nullptr;
	void __stdcall LevelShutdownHook();

	using FrameStageNotify = void(__thiscall*)(void*, ClientFrameStage_t);
	static FrameStageNotify FrameStageNotifyOriginal = nullptr;
	void __stdcall FrameStageNotifyHook(ClientFrameStage_t frameStage);

	using PaintPanel = void(__thiscall*)(void*, VPANEL, bool, bool);
	static PaintPanel PaintPanelOriginal = nullptr;
	void __stdcall PaintPanelHook(VPANEL vguiPanel, bool force_repaint, bool allow_force);

	using OnScreenSizeChanged = void(__thiscall*)(void*, int, int);
	static OnScreenSizeChanged OSSC_Original = nullptr;
	void __stdcall OSSC_Hook(int oldWidth, int oldHeight);

	using LockCursor = void(__thiscall*)(void*);
	static LockCursor LockCursorOriginal = nullptr;
	void __stdcall LockCursorHook();

	using ShouldDrawViewModel = bool(__thiscall*)(void*);
	static ShouldDrawViewModel SDVM_Original = nullptr;
	bool __stdcall SDVM_Hook();

	using OverrideView = void(__thiscall*)(void*, CViewSetup*);
	static OverrideView OverrideViewOriginal = nullptr;
	void __stdcall OverrideViewHook(CViewSetup* pSetup);

	namespace WndProc
	{
		inline WNDPROC oWndProc = nullptr;
		inline HWND	   hwGame = nullptr;
		LRESULT CALLBACK Detour(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	}
}