#pragma once
#include <future>
#include <fstream>
using std::cout;
using std::endl;

struct GlobalHacksPresests
{
	float fVehHightLimit;
};

namespace g
{
	GlobalHacksPresests globalPresets;
};

struct crTickLocalPlayerInfo
{
	bool isExist;
	bool isInCar;
	bool isDriver;
	Vehicles::eVehicleType vehType;
	crTickLocalPlayerInfo(
		bool isExist,
		bool isInCar,
		bool isDriver,
		Vehicles::eVehicleType vehType)
	{
		this->isExist = isExist;
		this->isInCar = isInCar;
		this->isDriver = isDriver;
		this->vehType = vehType;
	}
};

class IHack
{
public:
	std::string hackName;
	bool isEnable = false;
	const GlobalHacksPresests *globalPresets = &g::globalPresets;
	virtual void save(Json::Value&) {};
	virtual void read(Json::Value&) {};
	virtual ~IHack() = default;
	virtual void switchHack() {};
	virtual bool rpcIncHook(stRakNetHookParams*, const crTickLocalPlayerInfo&) { return true; };
	virtual bool rpcOutHook(stRakNetHookParams*, const crTickLocalPlayerInfo&) { return true; };
	virtual bool packetIncHook(stRakNetHookParams*, const crTickLocalPlayerInfo&) { return true; };
	virtual bool packetOutHook(stRakNetHookParams*, const crTickLocalPlayerInfo&) { return true; };
	virtual void wndProcHook(WPARAM, UINT, const crTickLocalPlayerInfo&) {};
	virtual void everyTickAction(const crTickLocalPlayerInfo&) {};
	virtual void drawGUI() {};
	virtual void drawSettings() {};
	virtual void drawHack(const crTickLocalPlayerInfo&) {};
	virtual void release() {};
	virtual void init() {};
	void notify(const std::string& text, bool e)
	{
		Stuff::AddMessageJumpQ(text + std::string(e ? " ~g~On" : " ~r~Off"));

	}
};


#include "C:\Lippets\FIles\SingleFile\ImGuiSnippets.h"
#include "SpeedControl.h"
#include "MegaBMXJump.h"
#include "AirBrake.h"	   
#include "WallHack_NewNameTags.h"
#include "1LineHacks.h"
#include "AutoShot.h"
#include "InputHelper.h"
#include "BMXSpeedHack.h"
#include "TurboControl.h"


class HackManager
{
private:
	std::deque<IHack*> hacks;
public:
	void destroy()
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
	void drawHacks(const crTickLocalPlayerInfo& info)
	{
		for (auto &&hack : hacks)
			if (hack->isEnable)
				hack->drawHack(info);
	}
	void drawGui()
	{
		for (auto &&hack : hacks)
			hack->drawGUI();
	}
	void drawSettings()
	{
		for (auto &&hack : hacks)
			hack->drawSettings();
	}
	void read()
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
	void save()
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
	void procKeys(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info)
	{
		for (auto &&hack : hacks)
			if (hack->isEnable)
				hack->wndProcHook(wParam, msg, info);
	}
	bool procIncPRC(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
	{
		for (auto &&hack : hacks)
			if (hack->isEnable)
				if (!hack->rpcIncHook(params, info))
					return false;
		return true;
	}
	bool procOutPRC(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
	{
		for (auto &&hack : hacks)
			if (hack->isEnable)
				if (!hack->rpcOutHook(params, info))
					return false;
		return true;
	}
	bool procIncPacket(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
	{
		for (auto &&hack : hacks)
			if (hack->isEnable)
				if (!hack->packetIncHook(params, info))
					return false;
		return true;
	}
	bool procOutPacket(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
	{
		for (auto &&hack : hacks)
			if (hack->isEnable)
				if (!hack->packetOutHook(params, info))
					return false;
		return true;
	}
	void procEveryTickAction(const crTickLocalPlayerInfo& info)
	{
		for (auto &&hack : hacks)
			if (hack->isEnable)
				hack->everyTickAction(info);
	}
	void initHacksOnce()
	{
		static bool isInitialized = false;
		if (isInitialized)
			return;
		hacks.emplace_back(new OneLineHacks("OneLineHacks"));
		hacks.emplace_back(new SpeedControl("Speed Control"));
		hacks.emplace_back(new AirBrake("Air Brake"));
		hacks.emplace_back(new WallHack("Wall Hack"));
		hacks.emplace_back(new AutoShot("Auto Shot"));
		hacks.emplace_back(new InputHelper("Input Helper"));
		hacks.emplace_back(new BMXspeedhack("BMX Speedhack"));
		hacks.emplace_back(new TurboControl("Turbo Control"));
		read();
		for (auto&& hack : hacks)
			hack->init();
		for (auto&& hack : hacks)
			hack->switchHack();
		isInitialized = true;
	}
};



