#pragma once
#define _MATH_DEFINES_DEFINED
#include "SAMPFUNCS_API.h"
#include "game_api.h"
extern SAMPFUNCS *SF;

#include "nlohmanSingle/json.hpp"
#include "C:\Lippets\SampSnipps\SampSnipps.h"
#include "imgui_single.h"
#include "C:\Lippets\FIles\Computer.h"
#include "C:\Lippets\FIles\Conditions.h"
#include "C:\Lippets\FIles\ImGuiSnippets.h"
#include "C:\Lippets\FIles\Strings.h"
#include "C:\Lippets\FIles\Numbers.h"
#include "C:\Lippets\CMClasses\CMFont.h"
#include "C:\Lippets\CMClasses\CMTimer.h"
#include "C:\Lippets\FIles\LUtils.h"
#include "C:\Lippets\SampSnipps\GTAfuncs.h"
#include <bitset>

#define SERIALIZE_FIELD_JSON_(name,value) data[name] = value
#define SERIALIZE_FIELD_JSON(x) data[#x] = x

#define DESERIALIZE_FIELD_JSON_(name,var) data.at(name).get_to(var)
#define DESERIALIZE_FIELD_JSON(var) data.at(#var).get_to(var)

#define ASSIGN_VAR_VALUE_IF_NOT_IN_BOUNDS(var,minV,maxV,newVal) if (var < minV || var > maxV) var = newVal; 
#define ASSIGN_VAR_VALUE_IF_EQUALS_ZERO(var,newVal) if (var == 0) var = newVal;
#define ASSIGN_VAR_VALUE_IF_EQUALS_ZEROF(var,newVal) if (var == 0.f) var = newVal;

#define HACK_CLASS(name) class name : public IHack
#define DEFAULT_HACK_CONSTRUCTOR(name) name::name(const char* szHackName) { m_sHackName = szHackName;}

#define cm(x) SF->getSAMP()->getChat()->AddChatMessage(-1,(x));
#define cm_ SF->getSAMP()->getChat()->AddChatMessage
#define MYID SF->getSAMP()->getPlayers()->sLocalPlayerID
#pragma warning( disable : 4996 )



struct crTickLocalPlayerInfo
{
	bool isExist;
	bool isInCar;
	bool isDriver;
	int iCurrentVehicleID;
	Vehicles::eVehicleType vehType;
	std::vector<NearPlayer> nearestPlayers;
	std::vector<NearVehicle> nearestVehicles;
	inline crTickLocalPlayerInfo() {}
};

namespace g
{
	extern bool isWindowOpen;
	extern bool isCtrlPressed;
	extern bool isAltPressed;
	extern bool isShiftPressed;
	extern int keyButtonSplitter;
	extern crTickLocalPlayerInfo* const pInfo;
	extern SLineOfSightFlags LineOfSightFlags;
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

class IHack : Lippets::LUtils::NonCopyable
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
	virtual bool onWndProc(WPARAM, UINT) { m_bitsDontCall__.set(WND_PROC); return true; };
	virtual void everyTickAction() { m_bitsDontCall__.set(EVERY_TICK); };
	virtual void onDrawGUI() {};
	virtual void onDrawHack() { m_bitsDontCall__.set(DRAW_HACK); };
	virtual void release() {};
	virtual void init() {};
};






