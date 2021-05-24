#pragma once

#include "SAMPFUNCS_API.h"
#include "game_api.h"
#include "Hack.h"

#include <future>
#include <fstream>

enum class Priority
{
	HIGH,
	MIDDLE,
	LOW,
	DEFAULT
};

enum class HACK_TYPE
{
	VISUAL,
	SHOOTING,
	MISC
};


class HacksManager
{
private:
	HacksManager();
	std::vector<std::tuple<Priority, HACK_TYPE, IHack*>> m_hacks;
public:

	HacksManager(HacksManager &other) = delete;
	void operator=(const HacksManager &) = delete;
	static HacksManager *getInstance();
	std::vector<std::tuple<Priority, HACK_TYPE, IHack*>>* getHacks();
	void destroy();
	bool drawHacks();
	void drawInterface();
	void drawMenu();
	void read();
	void save();
	bool procRakNetHook(stRakNetHookParams* params,  RakNetScriptHookType procFunc);
	bool procKeys(WPARAM wParam, UINT msg);
	void procEveryTickAction();
	void initHacksOnce();
};
