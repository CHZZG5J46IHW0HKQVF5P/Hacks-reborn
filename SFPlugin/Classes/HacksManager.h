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
	MISC,
	OTHER
};

enum class Proc_Func
{
	INC_RPC,
	OUT_RPC,
	INC_PACKET,
	OUT_PACKET
};

class HackManager
{
private:
	std::deque<std::tuple<Priority, HACK_TYPE, IHack*>> m_hacks;
public:
	std::deque<std::tuple<Priority, HACK_TYPE, IHack*>>* getHacks();
	void destroy();
	bool drawHacks(crTickLocalPlayerInfo* info);
	void drawGui();
	void drawSettings();
	void read();
	void save();

	bool procRakNetHook(stRakNetHookParams* params, crTickLocalPlayerInfo* info, Proc_Func procFunc);

	bool procKeys(WPARAM wParam, UINT msg, crTickLocalPlayerInfo* info);

	void procEveryTickAction(crTickLocalPlayerInfo* info);
	void initHacksOnce();
};
