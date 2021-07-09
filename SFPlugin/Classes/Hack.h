#pragma once
#define _MATH_DEFINES_DEFINED
#include "SAMPFUNCS_API.h"
#include "game_api.h"
extern SAMPFUNCS* SF;

#include "nlohmanSingle/json.hpp"
#include "SampSnipps\SampSnipps.h"
#include "imgui_single.h"
#include "Files\KeyboardMouse.h"
#include "Files\Computer.h"
#include "Files\Conditions.h"
#include "Files\ImGuiSnippets.h"
#include "Files\Strings.h"
#include "Files\Numbers.h"
#include "CMClasses\CMFont.h"
#include "CMClasses\CMTimer.h"
#include "Files\LUtils.h"
#include "SampSnipps\GTAfuncs.h"
#include <bitset>
#include <ranges>
#include <algorithm>
class IHack;
#include "GlobalFuncs.h"
#define SERIALIZE_FIELD_JSON_(name,value) data[name] = value
#define SERIALIZE_FIELD_JSON(x) data[#x] = x

#define DESERIALIZE_FIELD_JSON_(name,var) data.at(name).get_to(var)
#define DESERIALIZE_FIELD_JSON(var) data.at(#var).get_to(var)

#define ASSIGN_VAR_VALUE_IF_NOT_IN_BOUNDS(var,minV,maxV,newVal) if (var < minV || var > maxV) var = newVal; 
#define ASSIGN_VAR_VALUE_IF_EQUALS_ZERO(var,newVal) if (var == 0) var = newVal;
#define ASSIGN_VAR_VALUE_IF_EQUALS_ZEROF(var,newVal) if (var == 0.f) var = newVal;

#define HACK_CLASS(name) class name : public IHack
#define DEFAULT_HACK_CONSTRUCTOR(name) name::name(const char* szHackName) { m_sHackName = #name;}
#define DEFAULT_HACK_CONSTRUCTOR_WITH_IMGUI(name) name::name(const char* szHackName) { m_sHackName = #name; m_bDrawHackNeedImGui = true;}
#define cm(x) SF->getSAMP()->getChat()->AddChatMessage(-1,(x));
#define cm_ SF->getSAMP()->getChat()->AddChatMessage
#define MYID SF->getSAMP()->getPlayers()->sLocalPlayerID
#pragma warning( disable : 4996 )



struct crTickLocalPlayerInfo
{
	inline bool isInCar()
	{
		return _isInCar && pLocalVeh;
	}
	inline bool isDriver()
	{
		return _isDriver && pLocalVeh;
	}
	vehicle_info* pLocalVeh;
	bool _isInCar;
	bool _isDriver;
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
	extern Lippets::KeyEvenByWndProc* const pKeyEventInfo;
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


class IHack : Lippets::LUtils::Classes::NonCopyable
{

public:
	std::bitset<8> m_bitsDontCall__;
	std::string m_sHackName;
	bool m_bDrawHackNeedImGui = false;
	bool m_bEnabled = false;
	inline virtual bool isHackWorking() { return m_bEnabled; };
	virtual void save(nlohmann::json&) {};
	virtual void read(nlohmann::json&) {};
	virtual ~IHack() = default;
	virtual void switchHack() {};
	template<typename T>
	inline static T* getInstance()
	{
		static T* pInst = GFuncs::template getHackPtr<T>();
		return pInst;
	}
	virtual bool onRPCIncoming(stRakNetHookParams*) { m_bitsDontCall__.set(RPC_INC); return true; };
	virtual bool onRPCOutcoming(stRakNetHookParams*) { m_bitsDontCall__.set(RPC_OUT); return true; };
	virtual bool onPacketIncoming(stRakNetHookParams*) { m_bitsDontCall__.set(PACKET_INC);  return true; };
	virtual bool onPacketOutcoming(stRakNetHookParams*) { m_bitsDontCall__.set(PACKET_OUT);  return true; };
	virtual bool onWndProc() { m_bitsDontCall__.set(WND_PROC); return true; };
	virtual void everyTickAction() { m_bitsDontCall__.set(EVERY_TICK); };
	virtual void onDrawGUI() {};
	virtual void onDrawHack() { m_bitsDontCall__.set(DRAW_HACK); };
	virtual void release() {};
	virtual void init() {};
};


#define GET_HACK_INST(className) className::getInstance<className>()
#define OVERRIDE_DRAWGUI void onDrawGUI() override;
#define OVERRIDE_SAVE_READ void save(nlohmann::json&) override; \
					void read(nlohmann::json&) override;
#define OVERRIDE_SWITCH_HACK void switchHack() override;
#define OVERRIDE_RPC_INC  bool onRPCIncoming(stRakNetHookParams*) override;
#define OVERRIDE_RPC_OUT  bool onRPCOutcoming(stRakNetHookParams*) override;
#define OVERRIDE_PACKET_INC  bool onPacketIncoming(stRakNetHookParams*) override;
#define OVERRIDE_PACKET_OUT  bool onPacketOutcoming(stRakNetHookParams*) override;
#define OVERRIDE_WNDPROC bool onWndProc() override; 
#define OVERRIDE_EVERY_TICK void everyTickAction() override;
#define OVERRIDE_DRAW_HACK void onDrawHack() override;
#define OVERRIDE_RELEASE void release() override;
#define OVERRIDE_INIT void init() override;
#define OVERRIDE_IS_HACK_WORKING bool isHackWorking() override;




