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
	bool bPressNitro = false;
	bool bNoFallDamage = false;
	bool bNoBike = false;
	bool bWaterDrive = false;
	bool bAutoBike = false;
	bool bNewDl = false;
	bool bWaterProofEngine = false;
	bool bBar160hp = false;
	bool bFastHeli = false;
	bool bDontGiveMeBat = false;		
	bool bMegaBMXJump = false;
	bool bSuperBunnyHop = false;
	void  onDrawGUI() override;

	void onDrawHack( crTickLocalPlayerInfo* info) override;

	void switchHack() override;

	void everyTickAction( crTickLocalPlayerInfo* info) override;

	void onWndProc(WPARAM wParam, UINT msg,  crTickLocalPlayerInfo* info) override;

	bool onRPCIncoming(stRakNetHookParams *param,  crTickLocalPlayerInfo* info) override;

	bool onPacketOutcoming(stRakNetHookParams *param,  crTickLocalPlayerInfo* info) override;

	void save(nlohmann::json& data) override;

	void read(nlohmann::json& data) override;

};
