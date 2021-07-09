#pragma once
#include "Hack.h"

HACK_CLASS(AutoShot)
{
public:
	AutoShot(const char*);
private:
	bool autoShot = false;
	int activationKey = 0;

	OVERRIDE_DRAWGUI;
	OVERRIDE_WNDPROC;
	OVERRIDE_EVERY_TICK;
	OVERRIDE_SAVE_READ;
};
