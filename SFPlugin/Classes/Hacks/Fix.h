#pragma once
#include "Hack.h"

class Fix : public IHack
{
public:
	Fix(const char* name);
private:
	bool onRPCOutcoming(stRakNetHookParams* params, const crTickLocalPlayerInfo& info) override;
	bool onRPCIncoming(stRakNetHookParams* params, const crTickLocalPlayerInfo& info) override;
};
