#pragma once
#include "Hack.h"

struct DamageInfo
{
	UINT16 wPlayerID;
	float damage_amount;
	UINT32 dWeaponID;
	UINT32 dBodypart;

	DamageInfo();
	DamageInfo(UINT16, float, UINT32, UINT32);
};

HACK_CLASS(OneBulletKill)
{
public:
	OneBulletKill(const char*);
private:
	DamageInfo dInfo;
	int iDelay = 0;
	int sendDamageDeuqeLength = 0;

	OVERRIDE_EVERY_TICK;
	OVERRIDE_RPC_OUT;
	OVERRIDE_DRAWGUI;
	
	OVERRIDE_SAVE_READ;
};