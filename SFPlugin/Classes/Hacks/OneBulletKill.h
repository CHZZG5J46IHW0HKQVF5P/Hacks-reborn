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

class OneBulletKill : public IHack
{
public:
	OneBulletKill(const char*);
private:
	DamageInfo dInfo;
	int iDelay;
	int sendDamageDeuqeLength = 0;
	void everyTickAction(const crTickLocalPlayerInfo&) override;
	bool onRPCOutcoming(stRakNetHookParams*, const crTickLocalPlayerInfo&) override;
	void onDrawGUI() override;
	void onDrawSettings() override;
	void save(Json::Value&) override;
	void read(Json::Value&) override;
};