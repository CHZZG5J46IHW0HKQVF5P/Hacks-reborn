#pragma once
#include "Hack.h"


HACK_CLASS(BMXspeedhack)
{
public:
	BMXspeedhack(const char* name);
private:
	int activationKey = 0;
	int iDelay;
	bool bmxspeedHack = false;

	OVERRIDE_DRAWGUI;
	OVERRIDE_WNDPROC;
	OVERRIDE_EVERY_TICK;
	OVERRIDE_SAVE_READ;
};
