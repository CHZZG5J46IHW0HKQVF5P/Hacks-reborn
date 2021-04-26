#pragma once
#include "SAMPFUNCS_API.h"
#include "game_api.h"
extern SAMPFUNCS *SF;


namespace g
{
	bool PressedKeys[255];
	int lastPressedKey;
	bool isWindowOpen;
	std::string settingsPath;
};



namespace hacksSettings
{
	bool bFakeAfk;
	bool bFastHelper;
};

#include "HacksManager.h"

namespace g
{
	HackManager hacksManager;
};



