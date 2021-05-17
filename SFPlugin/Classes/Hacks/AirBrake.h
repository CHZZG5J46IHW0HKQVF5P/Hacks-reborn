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
	void onWndProc(WPARAM wParam, UINT msg  ) override;
	void onDrawSettings() override;
	void save(nlohmann::json& data) override;
	void read(nlohmann::json& data) override;

};

