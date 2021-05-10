#include "HacksManager.h"

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
#include "Binder.h"
#include "AimBot.h"
#include "WallShot.h"
#include "ArizonaLEmulator.h"
#include "CustomRun.h"

#include "C:\Lippets\CMClasses\CMLogger.h"
#include "nameof/nameof.hpp"
namespace g
{
	extern CMLogger* loggerPtr;
	extern std::string settingsPath;
};



void HackManager::initHacksOnce()
{
	static bool isInitialized = false;
	if (isInitialized)
		return;

	m_hacks.push_back(std::make_tuple(Priority::HIGH, HACK_TYPE::MISC, new ArizonaLEmulator("Arizona Launcher Emulator")));
	m_hacks.push_back(std::make_tuple(Priority::HIGH, HACK_TYPE::OTHER, new PlayersList("Players List")));
	m_hacks.push_back(std::make_tuple(Priority::HIGH, HACK_TYPE::SHOOTING, new OneBulletKill("One Bullet Kill")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::SHOOTING, new WallShot("Wall Shot")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::SHOOTING, new Aimbot("Aimbot")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::VISUAL, new WallHack("Wall Hack")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::SHOOTING, new AutoShot("Auto Shot")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new  AirBrake("Air Brake")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::OTHER, new InputHelper("Input Helper")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::OTHER, new BMXspeedhack("BMX Speedhack")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::OTHER, new TurboControl("Turbo Control")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::OTHER, new AltClicker("Alt Clicker")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::OTHER, new Binder("Binder")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::OTHER, new Fix("Fix")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::OTHER, new OneLineHacks("OneLineHacks")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::OTHER, new CustomRun("CustomRun")));
	std::sort(m_hacks.begin(), m_hacks.end(), [](const std::tuple<Priority, HACK_TYPE, IHack*> pair1, const std::tuple<Priority, HACK_TYPE, IHack*>  pair2)
	{
		return std::get<Priority>(pair1) < std::get<Priority>(pair2);
	});

	read();
	for (auto&& hack : m_hacks)
		std::get<IHack*>(hack)->init();
	for (auto&& hack : m_hacks)
		std::get<IHack*>(hack)->switchHack();

	isInitialized = true;
}

std::deque<std::tuple<Priority, HACK_TYPE, IHack*>>* HackManager::getHacks()
{
	return &m_hacks;
}

void HackManager::destroy()
{
	save();
	for (auto&& hack : m_hacks)
	{
		std::get<IHack*>(hack);
		std::get<IHack*>(hack)->m_bEnabled = false;
		std::get<IHack*>(hack)->switchHack();
		std::get<IHack*>(hack)->release();
		delete std::get<IHack*>(hack);
	}
	m_hacks.clear();
}

void HackManager::read()
{

	for (auto&& hack : m_hacks)
	{
		try
		{
			std::ifstream in(g::settingsPath + std::get<IHack*>(hack)->m_sHackName + ".json");
			if (!in.is_open())
				continue;

			std::string str;
			getline(in, str);
			in.close();
			nlohmann::json data;

			data = nlohmann::json::parse(str);

			std::get<IHack*>(hack)->read(data);
		}
		catch (...)
		{
			g::loggerPtr->log("Reading error " + std::get<IHack*>(hack)->m_sHackName);
		}
	}

}
void HackManager::save()
{
	for (auto&& hack : m_hacks)
	{
		nlohmann::json data;
		data.clear();
		std::get<IHack*>(hack)->save(data);
		std::ofstream out(g::settingsPath + std::get<IHack*>(hack)->m_sHackName + ".json");
		out << data.dump();
		out.close();
	}
}
bool HackManager::drawHacks(crTickLocalPlayerInfo* info)
{
	bool bImGuiNewFrameWasCalled = false;
	for (auto &&hack : m_hacks)
		if (std::get<IHack*>(hack)->m_bEnabled)
		{
			g::loggerPtr->log("[DRAW HACK]" + std::get<IHack*>(hack)->m_sHackName);
			if (!bImGuiNewFrameWasCalled && std::get<IHack*>(hack)->m_bDrawHackNeedImGui)
			{
				bImGuiNewFrameWasCalled = true;
				ImGui_ImplDX9_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();
			}
			std::get<IHack*>(hack)->onDrawHack(info);
		}

	return bImGuiNewFrameWasCalled;
}
void HackManager::drawGui()
{
	static HACK_TYPE choosedHackType = HACK_TYPE::OTHER;
	for (byte i = (byte)HACK_TYPE::VISUAL; i <= (byte)HACK_TYPE::OTHER; i++)
	{
		if (ImGui::Button(nameof::nameof_enum((HACK_TYPE)i).data()))
			choosedHackType = (HACK_TYPE)i;
		if (i != (byte)HACK_TYPE::OTHER)
			ImGui::SameLine();
	}
	for (auto &&hack : m_hacks)
		if (std::get<HACK_TYPE>(hack) == choosedHackType)
			std::get<IHack*>(hack)->onDrawGUI();
}
void HackManager::drawSettings()
{
	for (auto &&hack : m_hacks)
		std::get<IHack*>(hack)->onDrawSettings();
}

bool HackManager::procKeys(WPARAM wParam, UINT msg, crTickLocalPlayerInfo* info)
{
	bool bNeedImGuiProcKeys = false;
	for (auto &&hack : m_hacks)
		if (std::get<IHack*>(hack)->m_bEnabled)
		{
			g::loggerPtr->log("[PROC KEYS]" + std::get<IHack*>(hack)->m_sHackName);
			if (std::get<IHack*>(hack)->m_bDrawHackNeedImGui)
				bNeedImGuiProcKeys = true;
			std::get<IHack*>(hack)->onWndProc(wParam, msg, info);
		}
	return bNeedImGuiProcKeys;
}

bool HackManager::procRakNetHook(stRakNetHookParams* params, crTickLocalPlayerInfo* info, Proc_Func procFunc)
{
	switch (procFunc)
	{
	case Proc_Func::INC_RPC:
	{
		for (auto &&hack : m_hacks)
			if (std::get<IHack*>(hack)->m_bEnabled)
			{
				g::loggerPtr->log("[INC RPC]" + std::get<IHack*>(hack)->m_sHackName);
				if (!std::get<IHack*>(hack)->onRPCIncoming(params, info))
					return false;
			}
		return true;
	}
	case Proc_Func::OUT_RPC:
	{
		for (auto &&hack : m_hacks)
			if (std::get<IHack*>(hack)->m_bEnabled)
			{
				g::loggerPtr->log("[OUT RPC]" + std::get<IHack*>(hack)->m_sHackName);
				if (!std::get<IHack*>(hack)->onRPCOutcoming(params, info))
					return false;
			}
		return true;
	}
	case Proc_Func::INC_PACKET:
	{
		for (auto &&hack : m_hacks)
			if (std::get<IHack*>(hack)->m_bEnabled)
			{
				g::loggerPtr->log("[INC PACKET]" + std::get<IHack*>(hack)->m_sHackName);
				if (!std::get<IHack*>(hack)->onPacketIncoming(params, info))
					return false;
			}
		return true;
	}
	case Proc_Func::OUT_PACKET:
	{
		for (auto &&hack : m_hacks)
			if (std::get<IHack*>(hack)->m_bEnabled)
			{
				g::loggerPtr->log("[OUT PACKET]" + std::get<IHack*>(hack)->m_sHackName);
				if (!std::get<IHack*>(hack)->onPacketOutcoming(params, info))
					return false;
			}
		return true;
	}
	default: break;
	}

	return true;
}
void HackManager::procEveryTickAction(crTickLocalPlayerInfo* info)
{
	for (auto &&hack : m_hacks)
		if (std::get<IHack*>(hack)->m_bEnabled)
		{
			g::loggerPtr->log("[EVERY TICK ACTION]" + std::get<IHack*>(hack)->m_sHackName);
			std::get<IHack*>(hack)->everyTickAction(info);
		}

}
