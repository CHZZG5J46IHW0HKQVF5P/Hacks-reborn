#pragma once
#include "Hack.h"

HACK_CLASS(MainHack)
{
public:
	MainHack(const char*);
	OVERRIDE_RPC_INC;
	OVERRIDE_RPC_OUT;
	OVERRIDE_WNDPROC;
	OVERRIDE_EVERY_TICK;
	OVERRIDE_INIT;
};
