#pragma once
#include "Hack.h"

class AirBrake : public IHack
{
public:
	AirBrake(const char* name);
private:
	bool isAirBrakeShouldWork = false;
	int activationKey = 0;
	float fAirBrakeForce = 0.f;
	void onDrawGUI() override;
	void onWndProc(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info) override;
	void onDrawSettings() override;
	void save(Json::Value& data) override;
	void read(Json::Value& data) override;

};

