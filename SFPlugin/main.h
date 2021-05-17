#pragma once
#include "SAMPFUNCS_API.h"
#include "game_api.h"
#include "plog\Log.h"
#include "plog\Initializers\RollingFileInitializer.h"
extern SAMPFUNCS *SF;


namespace g
{
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
   
namespace g
{
	crTickLocalPlayerInfo* pInfo = new crTickLocalPlayerInfo();
}

bool CALLBACK WndProcHandler(HWND, UINT, WPARAM, LPARAM);
HRESULT CALLBACK Reset(D3DPRESENT_PARAMETERS*);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK PluginFree();


