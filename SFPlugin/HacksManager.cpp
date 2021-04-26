#include "HacksManager.h"

#include "SpeedControl.h"
#include "MegaBMXJump.h"
#include "AirBrake.h"	   
#include "WallHack_NewNameTags.h"
#include "1LineHacks.h"
#include "AutoShot.h"
#include "InputHelper.h"
#include "BMXSpeedHack.h"
#include "TurboControl.h"
#include "Fix.h"
#include "PlayersList.h"

namespace g
{
	extern bool PressedKeys[255];
	extern int lastPressedKey;
	extern bool isWindowOpen;
	extern std::string settingsPath;
};


void HackManager::initHacksOnce()
{
	static bool isInitialized = false;
	if (isInitialized)
		return;
	hacks.emplace_back(new Fix("Fix"));
	hacks.emplace_back(new OneLineHacks("OneLineHacks"));
	hacks.emplace_back(new SpeedControl("Speed Control"));
	hacks.emplace_back(new AirBrake("Air Brake"));
	hacks.emplace_back(new WallHack("Wall Hack"));
	hacks.emplace_back(new AutoShot("Auto Shot"));
	hacks.emplace_back(new InputHelper("Input Helper"));
	hacks.emplace_back(new BMXspeedhack("BMX Speedhack"));
	hacks.emplace_back(new TurboControl("Turbo Control"));
	hacks.emplace_back(new PlayersList("PlayersList"));
	read();
	for (auto&& hack : hacks)
		hack->init();
	for (auto&& hack : hacks)
		hack->switchHack();
	isInitialized = true;
}

void HackManager::destroy()
{
	save();
	for (int i = 0; i < hacks.size(); i++)
	{
		hacks[i]->isEnable = false;
		hacks[i]->switchHack();
		hacks[i]->release();
		delete hacks[i];
	}
	hacks.clear();
}
void HackManager::drawHacks(const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack->isEnable)
			hack->onDrawHack(info);
}
void HackManager::drawGui()
{
	for (auto &&hack : hacks)
		hack->onDrawGUI();
}
void HackManager::drawSettings()
{
	for (auto &&hack : hacks)
		hack->onDrawSettings();
}
void HackManager::read()
{
	for (auto&& hack : hacks)
	{
		std::ifstream in(g::settingsPath + hack->hackName + ".json");
		if (!in.is_open())
			continue;
		std::string rawJson((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());
		Json::Value data;
		Json::Reader reader;
		reader.parse(rawJson, data);
		hack->read(data);
		in.close();
	}
}
void HackManager::save()
{
	for (auto&& hack : hacks)
	{
		Json::Value data;
		hack->save(data);
		std::ofstream out(g::settingsPath + hack->hackName + ".json");
		out << data;
		out.close();
	}
}
void HackManager::procKeys(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack->isEnable)
			hack->onWndProc(wParam, msg, info);
}
bool HackManager::procIncPRC(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack->isEnable)
			if (!hack->onRPCIncoming(params, info))
				return false;
	return true;
}
bool HackManager::procOutPRC(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack->isEnable)
			if (!hack->onRPCOutcoming(params, info))
				return false;
	return true;
}
bool HackManager::procIncPacket(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack->isEnable)
			if (!hack->onPacketIncoming(params, info))
				return false;
	return true;
}
bool HackManager::procOutPacket(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack->isEnable)
			if (!hack->onPackerOutcoming(params, info))
				return false;
	return true;
}
void HackManager::procEveryTickAction(const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack->isEnable)
			hack->everyTickAction(info);
}
