#pragma once
#include "SAMPFUNCS_API.h"
#include "game_api.h"
extern SAMPFUNCS *SF;
#include "C:\SampSnipps.h"
#include "ImGui\imgui_single_file.h"
#include "C:\Lippets\FIles\SingleFile\Computer.h"
#include "C:\Lippets\FIles\SingleFile\Conditions.h"
#include "C:\Lippets\FIles\SingleFile\ImGuiSnippets.h"
#include "json\json.h"
#include "CMFont.h"
#define iScrResX *(int*)0xC9C040
#define iScrResY *(int*)0xC9C044
#define cm(x) SF->getSAMP()->getChat()->AddChatMessage(-1,(x));
#define MYID SF->getSAMP()->getPlayers()->sLocalPlayerID
#pragma warning( disable : 4996 )


namespace hacksSettings
{
	extern bool bFakeAfk;
	extern bool bFastHelper;
};

struct crTickLocalPlayerInfo
{
	bool isExist;
	bool isInCar;
	bool isDriver;
	Vehicles::eVehicleType vehType;
	inline crTickLocalPlayerInfo(
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

inline void notify(const std::string& text, bool e)
{
	Stuff::AddMessageJumpQ(text + std::string(e ? " ~g~On" : " ~r~Off"));
}

class IHack
{
public:
	std::string hackName;
	bool isEnable = false;
	virtual void save(Json::Value&) {};
	virtual void read(Json::Value&) {};
	virtual ~IHack() = default;
	virtual void switchHack() {};
	virtual bool onRPCIncoming(stRakNetHookParams*, const crTickLocalPlayerInfo&) { return true; };
	virtual bool onRPCOutcoming(stRakNetHookParams*, const crTickLocalPlayerInfo&) { return true; };
	virtual bool onPacketIncoming(stRakNetHookParams*, const crTickLocalPlayerInfo&) { return true; };
	virtual bool onPackerOutcoming(stRakNetHookParams*, const crTickLocalPlayerInfo&) { return true; };
	virtual void onWndProc(WPARAM, UINT, const crTickLocalPlayerInfo&) {};
	virtual void everyTickAction(const crTickLocalPlayerInfo&) {};
	virtual void onDrawGUI() {};
	virtual void onDrawSettings() {};
	virtual void onDrawHack(const crTickLocalPlayerInfo&) {};
	virtual void release() {};
	virtual void init() {};

};






