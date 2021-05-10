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
	void everyTickAction( crTickLocalPlayerInfo*) override;
	bool onRPCOutcoming(stRakNetHookParams*,  crTickLocalPlayerInfo*) override;
	void onDrawGUI() override;
	void onDrawSettings() override;
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;
};