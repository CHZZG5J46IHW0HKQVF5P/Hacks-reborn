#pragma once
#define _MATH_DEFINES_DEFINED
#include "SAMPFUNCS_API.h"
#include "game_api.h"
extern SAMPFUNCS *SF;
#include "C:\Lippets\SampSnipps\SampSnipps.h"
#include "imgui_single.h"
#include "C:\Lippets\FIles\Computer.h"
#include "C:\Lippets\FIles\Conditions.h"
#include "C:\Lippets\FIles\ImGuiSnippets.h"
#include "C:\Lippets\FIles\Strings.h"
#include "C:\Lippets\FIles\Numbers.h"
#include "nlohmann/json.hpp"
#include "C:\Lippets\CMClasses\CMFont.h"
#include "C:\Lippets\CMClasses\CMTimer.h"
#include "C:\Lippets\FIles\LUtils.h"
#include <bitset>
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





struct crTickLocalPlayerInfo
{
	bool isExist;
	bool isInCar;
	bool isDriver;
	int iCurrentVehicleID;
	Vehicles::eVehicleType vehType;
	std::vector<std::pair<int, float>> nearestPlayers;
	std::vector<std::pair<int, float>> nearestVehicles;
	inline crTickLocalPlayerInfo() {}
};

namespace g
{
	extern bool isCtrlPressed;
	extern bool isAltPressed;
	extern bool isShiftPressed;
	extern int keyButtonSplitter;
	extern crTickLocalPlayerInfo* pInfo;
};

inline void notify(const std::string& text, bool e)
{
	Stuff::AddMessageJumpQ(text + (e ? " ~g~On" : " ~r~Off"));
}

enum HackFunction
{
	RPC_INC,
	RPC_OUT,
	PACKET_INC,
	PACKET_OUT,
	EVERY_TICK,
	WND_PROC,
	DRAW_HACK
};

class IHack	: Lippets::LUtils::NonCopyable
{

public:
	std::bitset<8> m_bitsDontCall__;
	std::string m_sHackName;
	bool m_bDrawHackNeedImGui = false;
	bool m_bEnabled = false;
	virtual bool isHackWorking() { return m_bEnabled; };
	virtual void save(nlohmann::json&) {};
	virtual void read(nlohmann::json&) {};
	virtual ~IHack() = default;
	virtual void switchHack() {};
	virtual bool onRPCIncoming(stRakNetHookParams*) { m_bitsDontCall__.set(RPC_INC); return true; };
	virtual bool onRPCOutcoming(stRakNetHookParams*) { m_bitsDontCall__.set(RPC_OUT); return true; };
	virtual bool onPacketIncoming(stRakNetHookParams*) { m_bitsDontCall__.set(PACKET_INC);  return true; };
	virtual bool onPacketOutcoming(stRakNetHookParams*) { m_bitsDontCall__.set(PACKET_OUT);  return true; };
	virtual void onWndProc(WPARAM, UINT) { m_bitsDontCall__.set(WND_PROC); };
	virtual void everyTickAction() { m_bitsDontCall__.set(EVERY_TICK); };
	virtual void onDrawGUI() {};
	virtual void onDrawSettings() {};
	virtual void onDrawHack() { m_bitsDontCall__.set(DRAW_HACK); };
	virtual void release() {};
	virtual void init() {};
};






