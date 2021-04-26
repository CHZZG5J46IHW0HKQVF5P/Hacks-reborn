#pragma once
#include "Hack.h"


class OneLineHacks : public IHack
{
public:
	OneLineHacks(const char*);
private:
	bool bNoReload = false;
	bool bAntiStun = false;
	bool bDriveWalkUnderWater = false;
	bool bFireProtection = false;
	bool bFastCrosshair = false;
	bool bInfOxygenAndStamina = false;
	bool bMegaJump = false;
	bool bNoSpread = false;
	bool bNoFreeze = false;
	bool bNoAnims = false;
	bool bNoCamrestore = false;
	bool bNoFall = false;
	bool bSurfOnVehicles = false;
	bool bWallShot = false;
	bool bPressNitro = false;
	bool bNoFallDamage = false;
	bool bNoBike = false;
	bool bWaterDrive = false;
	bool bAutoBike = false;
	bool bNewDl = false;
	bool bWaterProofEngine = false;
	bool bBar160hp = false;
	bool bDontGiveMeBat;
	void  onDrawGUI() override;

	void onDrawHack(const crTickLocalPlayerInfo& info) override;

	void switchHack() override;

	void everyTickAction(const crTickLocalPlayerInfo& info) override;

	void onWndProc(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info) override;

	bool onRPCIncoming(stRakNetHookParams *param, const crTickLocalPlayerInfo& info) override;

	bool onPacketOutcoming(stRakNetHookParams *param, const crTickLocalPlayerInfo& info) override;

	void save(Json::Value& data) override;

	void read(Json::Value& data) override;

};
