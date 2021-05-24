#pragma once
#include "Hack.h"

enum class RUN_TYPE
{
	DEFAULT, //= -1
	CJ,//= 54
	ROLLER,//= 138
	SWAT //= 128
};

enum class FIGHT_STYLE
{
	DEFAULT,//= 4,
	BOXING,//= 5,
	KUNG_FU,//= 6,
	KNEE_HEAD,//= 7,
	GRABKICK,//= 15,
	ELBOWS//= 16
};


HACK_CLASS(OneLineHacks)
{
public:
	OneLineHacks(const char*);
private:
	static inline bool bFastHelper = false;
	static inline bool bFakeAfk = false;
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
	RUN_TYPE CurrentRunType = RUN_TYPE::DEFAULT;
	FIGHT_STYLE CurrentFightStyle = FIGHT_STYLE::DEFAULT;
	void  onDrawGUI() override;

	void onDrawHack() override;

	void switchHack() override;

	void everyTickAction() override;

	

	bool onWndProc(WPARAM wParam, UINT msg) override;

	bool onRPCIncoming(stRakNetHookParams *param) override;

	bool onPacketOutcoming(stRakNetHookParams *param) override;

	void save(nlohmann::json& data) override;

	void read(nlohmann::json& data) override;

};
