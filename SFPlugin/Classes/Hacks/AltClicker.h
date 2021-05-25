#pragma once
#include "Hack.h"


HACK_CLASS(AltClicker)
{
public:
	AltClicker(const char*);
private:
	bool bWorking;
	int iDelay;
	int activationKey;
	OVERRIDE_EVERY_TICK;
	OVERRIDE_DRAWGUI;

	OVERRIDE_WNDPROC;
	OVERRIDE_SAVE_READ;

};
