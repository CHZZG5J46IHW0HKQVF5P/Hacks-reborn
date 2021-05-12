#pragma once
#include "SAMPFUNCS_API.h"
#include "game_api.h"
extern SAMPFUNCS *SF;
#include "C:\SampSnipps.h"
#include "imgui_single.h"
#include "C:\Lippets\FIles\Computer.h"
#include "C:\Lippets\FIles\Conditions.h"
#include "C:\Lippets\FIles\ImGuiSnippets.h"
#include "C:\Lippets\FIles\Strings.h"
#include "C:\Lippets\FIles\Numbers.h"
#include "nlohmann/json.hpp"
#include "C:\Lippets\CMClasses\CMFont.h"
#include "C:\Lippets\CMClasses\CMTimer.h"

#define iScrResX *(int*)0xC9C040
#define iScrResY *(int*)0xC9C044
#define cshX iScrResX * 0.5299999714f
#define cshY iScrResY * 0.4f
#define cm(x) SF->getSAMP()->getChat()->AddChatMessage(-1,(x));
#define cm_ SF->getSAMP()->getChat()->AddChatMessage
#define MYID SF->getSAMP()->getPlayers()->sLocalPlayerID
#pragma warning( disable : 4996 )


namespace hacksSettings
{
	extern bool bFakeAfk;
	extern bool bFastHelper;
	extern SLineOfSightFlags LineOfSightFlags;
};

namespace g
{
	extern bool isCtrlPressed;
	extern bool isAltPressed;
	extern bool isShiftPressed;
	extern int keyButtonSplitter;
};



struct crTickLocalPlayerInfo
{
	bool isExist;
	bool isInCar;
	bool isDriver;
	Vehicles::eVehicleType vehType;
	std::deque<std::pair<int, float>> nearestPlayers;
	std::deque<std::pair<int, float>> nearestVehicles;
	inline crTickLocalPlayerInfo() {}
	inline crTickLocalPlayerInfo(
		bool isExist,
		bool isInCar,
		bool isDriver,
		Vehicles::eVehicleType vehType,
		const std::deque<std::pair<int, float>>& nearestPlayers,
		const std::deque<std::pair<int, float>>& nearestVehicles)
	{
		this->isExist = isExist;
		this->isInCar = isInCar;
		this->isDriver = isDriver;
		this->vehType = vehType;
		this->nearestPlayers = nearestPlayers;
		this->nearestVehicles = nearestVehicles;
	}
};

inline void notify(const std::string& text, bool e)
{
	Stuff::AddMessageJumpQ(text + (e ? " ~g~On" : " ~r~Off"));
}

enum HackFunctions : char
{
	RPC_INC,
	RPC_OUT,
	PACKET_INC,
	PACKET_OUT,
	EVERY_TICK,
	WND_PROC,
	DRAW_HACK
};

class IHack
{

public:
	DWORD m_dwDontCall__ = 0;
	std::string m_sHackName;
	bool m_bDrawHackNeedImGui = false;
	bool m_bEnabled = false;
	virtual bool isHackWorking() { return m_bEnabled; };
	virtual void save(nlohmann::json&) {};
	virtual void read(nlohmann::json&) {};
	virtual ~IHack() = default;
	virtual void switchHack() {};
	virtual bool onRPCIncoming(stRakNetHookParams*, crTickLocalPlayerInfo*) { m_dwDontCall__ |= RPC_INC; return true; };
	virtual bool onRPCOutcoming(stRakNetHookParams*, crTickLocalPlayerInfo*) { m_dwDontCall__ |= RPC_OUT; return true; };
	virtual bool onPacketIncoming(stRakNetHookParams*, crTickLocalPlayerInfo*) { m_dwDontCall__ |= PACKET_INC; return true; };
	virtual bool onPacketOutcoming(stRakNetHookParams*, crTickLocalPlayerInfo*) { m_dwDontCall__ |= PACKET_OUT; return true; };
	virtual void onWndProc(WPARAM, UINT, crTickLocalPlayerInfo*) { m_dwDontCall__ |= WND_PROC; };
	virtual void everyTickAction(crTickLocalPlayerInfo*) { m_dwDontCall__ |= EVERY_TICK; };
	virtual void onDrawGUI() {};
	virtual void onDrawSettings() {};
	virtual void onDrawHack(crTickLocalPlayerInfo*) { m_dwDontCall__ |= DRAW_HACK; };
	virtual void release() {};
	virtual void init() {};
};






