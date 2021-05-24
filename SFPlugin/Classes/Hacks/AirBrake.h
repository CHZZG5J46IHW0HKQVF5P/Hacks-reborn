#pragma once
#include "Hack.h"



HACK_CLASS(AirBrake)
{
public:
	AirBrake(const char* name);
private:
	bool isAirBrakeShouldWork = false;
	int activationKey = 0;
	float fAirBrakeForce = 0.f;
	void onDrawGUI() override;
	bool onWndProc(WPARAM wParam, UINT msg  ) override;
	
	void save(nlohmann::json& data) override;
	void read(nlohmann::json& data) override;

};

