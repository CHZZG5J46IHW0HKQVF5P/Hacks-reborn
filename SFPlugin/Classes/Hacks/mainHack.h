#pragma once
#include "Hack.h"

HACK_CLASS(MainHack)
{
public:
	MainHack(const char*);
	bool onRPCOutcoming(stRakNetHookParams* params) override;
	bool onRPCIncoming(stRakNetHookParams* params) override;
	bool onWndProc(WPARAM, UINT) override;
	void everyTickAction() override;
};
