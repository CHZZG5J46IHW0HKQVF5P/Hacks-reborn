#pragma once
#include "Hack.h"



HACK_CLASS(TurboControl)
{
public:
	TurboControl(const char* name);
private:
	int activationKey = 0;
	void onDrawGUI() override;
	bool  onWndProc() override;
	OVERRIDE_SAVE_READ;
};

