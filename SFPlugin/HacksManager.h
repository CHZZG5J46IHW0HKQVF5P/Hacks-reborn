#pragma once
#include <deque>

#include "SAMPFUNCS_API.h"
#include "game_api.h"
#include "Hack.h"

#include <future>
#include <fstream>


class HackManager
{
private:
	std::deque<IHack*> hacks;
public:
	void destroy();
	void drawHacks(const crTickLocalPlayerInfo& info);
	void drawGui();
	void drawSettings();
	void read();
	void save();
	void procKeys(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info);
	bool procIncPRC(stRakNetHookParams* params, const crTickLocalPlayerInfo& info);
	bool procOutPRC(stRakNetHookParams* params, const crTickLocalPlayerInfo& info);
	bool procIncPacket(stRakNetHookParams* params, const crTickLocalPlayerInfo& info);
	bool procOutPacket(stRakNetHookParams* params, const crTickLocalPlayerInfo& info);
	void procEveryTickAction(const crTickLocalPlayerInfo& info);
	void initHacksOnce();
};
