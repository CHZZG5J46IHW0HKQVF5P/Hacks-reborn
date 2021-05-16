#pragma once
#include <deque>

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
	std::deque<std::tuple<Priority, HACK_TYPE, IHack*>> m_hacks;
public:

	HacksManager(HacksManager &other) = delete;
	void operator=(const HacksManager &) = delete;
	static HacksManager *getInstance();
	std::deque<std::tuple<Priority, HACK_TYPE, IHack*>>* getHacks();
	void destroy();
	bool drawHacks(crTickLocalPlayerInfo* info);
	void drawGui();
	void drawSettings();
	void read();
	void save();
	bool procRakNetHook(stRakNetHookParams* params, crTickLocalPlayerInfo* info, RakNetScriptHookType procFunc);
	bool procKeys(WPARAM wParam, UINT msg, crTickLocalPlayerInfo* info);
	void procEveryTickAction(crTickLocalPlayerInfo* info);
	void initHacksOnce();
};
