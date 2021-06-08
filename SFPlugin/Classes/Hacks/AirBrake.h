#pragma once
#include "Hack.h"

void AirBrakeForward(float);

HACK_CLASS(AirBrake)
{
public:
	AirBrake(const char* name);
private:
	bool isAirBrakeShouldWork = false;
	int activationKey = 0;
	float fAirBrakeForce = 0.f;
	OVERRIDE_DRAWGUI;
	OVERRIDE_WNDPROC;
	OVERRIDE_SAVE_READ;

};

