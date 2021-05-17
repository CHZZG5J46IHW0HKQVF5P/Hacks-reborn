#pragma once
#include "Hack.h"

enum class RUN_TYPE
{
	DEFAULT, //= -1
	CJ,//= 54
	ROLLER,//= 138
	SWAT //= 128
};

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
	RUN_TYPE CurrentRunType = RUN_TYPE::DEFAULT;
	void  onDrawGUI() override;

	void onDrawHack() override;

	void switchHack() override;

	void everyTickAction() override;

	void onDrawSettings() override;

	void onWndProc(WPARAM wParam, UINT msg) override;

	bool onRPCIncoming(stRakNetHookParams *param) override;

	bool onPacketOutcoming(stRakNetHookParams *param) override;

	void save(nlohmann::json& data) override;

	void read(nlohmann::json& data) override;

};
