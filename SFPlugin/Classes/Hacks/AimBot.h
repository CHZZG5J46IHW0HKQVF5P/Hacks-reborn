#pragma once
#include "Hack.h"

HACK_CLASS(Aimbot)
{
public:
	Aimbot(const char*);
private:
	bool bCanAimToSameColored;
	actor_info* getPlayerTarget();
	void aim(actor_info*);

	OVERRIDE_EVERY_TICK;
	OVERRIDE_DRAWGUI;
	OVERRIDE_SAVE_READ;
};