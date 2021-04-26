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
#include "OneBulletKill.h"
#include "AltClicker.h"

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
	hacks.emplace_back(std::make_pair(Priority::DEFAULT, new Fix("Fix")));
	hacks.emplace_back(std::make_pair(Priority::DEFAULT, new OneLineHacks("OneLineHacks")));
	hacks.emplace_back(std::make_pair(Priority::DEFAULT, new SpeedControl("Speed Control")));
	hacks.emplace_back(std::make_pair(Priority::HIGH, new PlayersList("PlayersList")));
	hacks.emplace_back(std::make_pair(Priority::DEFAULT, new  AirBrake("Air Brake")));
	hacks.emplace_back(std::make_pair(Priority::DEFAULT, new WallHack("Wall Hack")));
	hacks.emplace_back(std::make_pair(Priority::DEFAULT, new AutoShot("Auto Shot")));
	hacks.emplace_back(std::make_pair(Priority::DEFAULT, new InputHelper("Input Helper")));
	hacks.emplace_back(std::make_pair(Priority::DEFAULT, new BMXspeedhack("BMX Speedhack")));
	hacks.emplace_back(std::make_pair(Priority::DEFAULT, new TurboControl("Turbo Control")));
	hacks.emplace_back(std::make_pair(Priority::DEFAULT, new OneBulletKill("One Bullet Kill")));
	hacks.emplace_back(std::make_pair(Priority::DEFAULT, new AltClicker("Alt Clicker")));
	read();
	for (auto&& hack : hacks)
		hack.second->init();
	for (auto&& hack : hacks)
		hack.second->switchHack();
	isInitialized = true;
}

void HackManager::destroy()
{
	save();
	for (auto&& hack : hacks)
	{
		hack.second->isEnable = false;
		hack.second->switchHack();
		hack.second->release();
		delete hack.second;
	}
	hacks.clear();
}
void HackManager::drawHacks(const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack.second->isEnable)
			hack.second->onDrawHack(info);
}
void HackManager::drawGui()
{
	for (auto &&hack : hacks)
		hack.second->onDrawGUI();
}
void HackManager::drawSettings()
{
	for (auto &&hack : hacks)
		hack.second->onDrawSettings();
}
void HackManager::read()
{
	for (auto&& hack : hacks)
	{
		std::ifstream in(g::settingsPath + hack.second->hackName + ".json");
		if (!in.is_open())
			continue;
		std::string rawJson((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());
		Json::Value data;
		Json::Reader reader;
		reader.parse(rawJson, data);
		hack.second->read(data);
		in.close();
	}
}
void HackManager::save()
{
	for (auto&& hack : hacks)
	{
		Json::Value data;
		hack.second->save(data);
		std::ofstream out(g::settingsPath + hack.second->hackName + ".json");
		out << data;
		out.close();
	}
}
void HackManager::procKeys(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack.second->isEnable)
			hack.second->onWndProc(wParam, msg, info);
}
bool HackManager::procIncPRC(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::HIGH)
			if (!hack.second->onRPCIncoming(params, info))
				return false;

	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::MIDDLE)
			if (!hack.second->onRPCIncoming(params, info))
				return false;

	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::LOW)
			if (!hack.second->onRPCIncoming(params, info))
				return false;

	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::DEFAULT)
			if (!hack.second->onRPCIncoming(params, info))
				return false;
	return true;
}
bool HackManager::procOutPRC(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::HIGH)
			if (!hack.second->onRPCOutcoming(params, info))
				return false;

	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::MIDDLE)
			if (!hack.second->onRPCOutcoming(params, info))
				return false;

	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::LOW)
			if (!hack.second->onRPCOutcoming(params, info))
				return false;

	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::DEFAULT)
			if (!hack.second->onRPCOutcoming(params, info))
				return false;
	return true;
}
bool HackManager::procIncPacket(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::HIGH)
			if (!hack.second->onPacketIncoming(params, info))
				return false;

	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::MIDDLE)
			if (!hack.second->onPacketIncoming(params, info))
				return false;

	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::LOW)
			if (!hack.second->onPacketIncoming(params, info))
				return false;

	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::DEFAULT)
			if (!hack.second->onPacketIncoming(params, info))
				return false;
	return true;
}
bool HackManager::procOutPacket(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::HIGH)
			if (!hack.second->onPacketOutcoming(params, info))
				return false;

	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::MIDDLE)
			if (!hack.second->onPacketOutcoming(params, info))
				return false;

	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::LOW)
			if (!hack.second->onPacketOutcoming(params, info))
				return false;

	for (auto &&hack : hacks)
		if (hack.second->isEnable && hack.first == Priority::DEFAULT)
			if (!hack.second->onPacketOutcoming(params, info))
				return false;
	return true;
}
void HackManager::procEveryTickAction(const crTickLocalPlayerInfo& info)
{
	for (auto &&hack : hacks)
		if (hack.second->isEnable)
			hack.second->everyTickAction(info);
}
