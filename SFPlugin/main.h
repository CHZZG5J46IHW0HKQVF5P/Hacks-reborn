#pragma once
#include "SAMPFUNCS_API.h"
#include "game_api.h"
#include <cmath>
extern SAMPFUNCS *SF;
#include "C:\Lippets\CMClasses\CMLogger.h"


namespace g
{
	CMLogger* loggerPtr;
	std::string settingsPath;
	int keyButtonSplitter;
	bool isWindowOpen;
	bool isCtrlPressed, isAltPressed, isShiftPressed;
};


namespace hacksSettings
{
	bool bFakeAfk;
	bool bFastHelper;
	SLineOfSightFlags LineOfSightFlags;
};

#include "HacksManager.h"


bool CALLBACK WndProcHandler(HWND, UINT, WPARAM, LPARAM);
HRESULT CALLBACK Reset(D3DPRESENT_PARAMETERS*);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK PluginFree();


