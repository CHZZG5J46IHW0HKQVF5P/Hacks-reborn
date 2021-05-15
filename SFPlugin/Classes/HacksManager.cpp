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


HackManager::HackManager()
{

}

HackManager* HackManager::getInstance()
{
	static HackManager instance;
	return &instance;
}

void HackManager::initHacksOnce()
{
	static bool isInitialized = false;
	if (isInitialized)
		return;

	m_hacks.clear();
	m_hacks.push_back(std::make_tuple(Priority::HIGH, HACK_TYPE::MISC, new PlayersList("Players List")));
	m_hacks.push_back(std::make_tuple(Priority::HIGH, HACK_TYPE::SHOOTING, new OneBulletKill("One Bullet Kill")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::SHOOTING, new WallShot("Wall Shot")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::SHOOTING, new Aimbot("Aimbot")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::VISUAL, new WallHack("Wall Hack")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::SHOOTING, new AutoShot("Auto Shot")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new  AirBrake("Air Brake")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new InputHelper("Input Helper")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new BMXspeedhack("BMX Speedhack")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new TurboControl("Turbo Control")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new AltClicker("Alt Clicker")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new Binder("Binder")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new Fix("Fix")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new OneLineHacks("OneLineHacks")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new CustomRun("CustomRun")));
	m_hacks.push_back(std::make_tuple(Priority::DEFAULT, HACK_TYPE::MISC, new ArizonaLEmulator("Arizona Launcher Emulator")));
	std::sort(m_hacks.begin(), m_hacks.end(), [](const std::tuple<Priority, HACK_TYPE, IHack*> pair1, const std::tuple<Priority, HACK_TYPE, IHack*>  pair2)
	{
		return std::get<Priority>(pair1) < std::get<Priority>(pair2);
	});

	read();
	for (auto&& hack : m_hacks)
	{
		std::get<IHack*>(hack)->init();
		std::get<IHack*>(hack)->switchHack();
	}

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
			if (!Lippets::Computer::isFileExits(g::settingsPath + std::get<IHack*>(hack)->m_sHackName + ".json"))
				continue;
			std::ifstream in(g::settingsPath + std::get<IHack*>(hack)->m_sHackName + ".json");

			if (!in.is_open())
				continue;

			std::string str;
			getline(in, str);
			in.close();
			nlohmann::json data;

			data = nlohmann::json::parse(str);
			if (!data.is_null())
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
	{
		auto&& pHack = std::get<IHack*>(hack);
		if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(DRAW_HACK))
		{
			g::loggerPtr->log("[DRAW HACK]" + pHack->m_sHackName);
			if (!bImGuiNewFrameWasCalled && pHack->m_bDrawHackNeedImGui)
			{
				bImGuiNewFrameWasCalled = true;
				ImGui_ImplDX9_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();
			}
			pHack->onDrawHack(info);
		}
	}
	return bImGuiNewFrameWasCalled;
}
void HackManager::drawGui()
{
	static HACK_TYPE choosedHackType = HACK_TYPE::MISC;
	for (byte i = (byte)HACK_TYPE::VISUAL; i <= (byte)HACK_TYPE::MISC; i++)
	{
		if (ImGui::Button(nameof::nameof_enum((HACK_TYPE)i).data()))
			choosedHackType = (HACK_TYPE)i;
		if (i != (byte)HACK_TYPE::MISC)
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
	{
		auto&& pHack = std::get<IHack*>(hack);
		if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(WND_PROC))
		{
			g::loggerPtr->log("[PROC KEYS]" + pHack->m_sHackName);
			if (pHack->m_bDrawHackNeedImGui)
				bNeedImGuiProcKeys = true;
			pHack->onWndProc(wParam, msg, info);
		}
	}
	return bNeedImGuiProcKeys;
}

bool HackManager::procRakNetHook(stRakNetHookParams* params, crTickLocalPlayerInfo* info, RakNetScriptHookType procFunc)
{
	switch (procFunc)
	{
	case RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_RPC:
	{
		for (auto &&hack : m_hacks)
		{
			auto&& pHack = std::get<IHack*>(hack);
			if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(RPC_INC))
			{
				g::loggerPtr->log("[INC RPC]" + pHack->m_sHackName);
				if (!pHack->onRPCIncoming(params, info))
					return false;
			}
		}
		return true;
	}
	case RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_RPC:
	{
		for (auto &&hack : m_hacks)
		{
			auto&& pHack = std::get<IHack*>(hack);
			if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(RPC_OUT))
			{
				g::loggerPtr->log("[OUT RPC]" + pHack->m_sHackName);
				if (!pHack->onRPCOutcoming(params, info))
					return false;
			}
		}
		return true;
	}
	case RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_PACKET:
	{
		for (auto &&hack : m_hacks)
		{
			auto&& pHack = std::get<IHack*>(hack);
			if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(PACKET_INC))
			{
				g::loggerPtr->log("[INC PACKET]" + pHack->m_sHackName);
				if (!pHack->onPacketIncoming(params, info))
					return false;
			}
		}
		return true;
	}
	case RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_PACKET:
	{
		for (auto &&hack : m_hacks)
		{
			auto&& pHack = std::get<IHack*>(hack);
			if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(PACKET_OUT))
			{
				g::loggerPtr->log("[OUT PACKET]" + pHack->m_sHackName);
				if (!pHack->onPacketOutcoming(params, info))
					return false;
			}
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
	{
		auto&& pHack = std::get<IHack*>(hack);
		if (pHack->m_bEnabled && !pHack->m_bitsDontCall__.test(EVERY_TICK))
		{
			g::loggerPtr->log("[EVERY TICK ACTION]" + pHack->m_sHackName);
			pHack->everyTickAction(info);
		}
	}
}
