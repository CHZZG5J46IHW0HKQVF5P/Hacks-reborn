#pragma once
#include "Hack.h"

class Fix : public IHack
{
public:
	Fix(const char* name);
private:
	bool onRPCIncoming(stRakNetHookParams* params, const crTickLocalPlayerInfo& info) override;
};
