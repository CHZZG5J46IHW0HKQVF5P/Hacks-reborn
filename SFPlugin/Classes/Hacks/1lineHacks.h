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
	bool bGodMode = false;
	bool bAutoVehicleOnWheels = false;
	RUN_TYPE CurrentRunType = RUN_TYPE::DEFAULT;
	FIGHT_STYLE CurrentFightStyle = FIGHT_STYLE::DEFAULT;
	OVERRIDE_DRAWGUI;
	OVERRIDE_DRAW_HACK;
	OVERRIDE_SWITCH_HACK;
	OVERRIDE_EVERY_TICK;
	OVERRIDE_WNDPROC;
	OVERRIDE_RPC_INC;
	OVERRIDE_PACKET_OUT;
	OVERRIDE_SAVE_READ;
};
