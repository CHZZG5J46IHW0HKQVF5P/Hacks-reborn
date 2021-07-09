#pragma once
#include "Hack.h"



HACK_CLASS(TurboControl)
{
public:
	TurboControl(const char* name);
private:
	int activationKey = 0;
	OVERRIDE_DRAWGUI;
	OVERRIDE_WNDPROC;
	OVERRIDE_SAVE_READ;
};

