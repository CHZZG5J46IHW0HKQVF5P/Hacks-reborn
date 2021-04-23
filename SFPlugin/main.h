#pragma once

#include "SAMPFUNCS_API.h"
#include "game_api.h"
extern SAMPFUNCS *SF;
#include "C:\SampSnipps.h"
using Vehicles::eVehicleType;
using Stuff::eKeyState;
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx9.h"
#include "ImGUI/imgui_impl_win32.h"
#include "ImGui/imgui_internal.h"
#include "C:\Lippets\FIles\SingleFile\Computer.h"
using Lippets::Computer::WriteMem;
#include "json\json.h"
#include "CMFont.h"
#define iScrResX *(int*)0xC9C040
#define iScrResY *(int*)0xC9C044
#define cm(x) SF->getSAMP()->getChat()->AddChatMessage(-1,(x));
#define MYID SF->getSAMP()->getPlayers()->sLocalPlayerID

enum class GuiMenu
{
	HACKS,
	MISC,
	SETTINGS,
	PLAYERS
};

namespace g
{

	bool PressedKeys[255] = { false };
	int lastPressedKey = 0;
	int keyBtnSplitter = 0;
	bool isWindowOpen = false;
	std::string settingsPath;
}

#include "Hack.h"

namespace g
{
	HackManager hacksManager;
}








