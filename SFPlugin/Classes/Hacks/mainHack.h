#pragma once
#include "Hack.h"

HACK_CLASS(MainHack)
{
public:
	MainHack(const char*);
	bool onRPCOutcoming(stRakNetHookParams* params) override;
	bool onRPCIncoming(stRakNetHookParams* params) override;
	OVERRIDE_WNDPROC;
	OVERRIDE_EVERY_TICK;
};
