#pragma once
#include "Hack.h"


class SpeedControl : public IHack
{
public:
	SpeedControl(const char* name);
private:
	bool bOnlyIFOnGround;
	bool bSpeedUpOnlyIFGasPedal;
	bool bSlowDownOnlyIFBreakPedal;
	bool bNoSlowDown;
	void onDrawGUI() override;
	void save(Json::Value& data) override;
	void read(Json::Value& data)   override;
	bool onRPCIncoming(stRakNetHookParams* params, const crTickLocalPlayerInfo& info) override;
	void onDrawSettings()	override;

};

