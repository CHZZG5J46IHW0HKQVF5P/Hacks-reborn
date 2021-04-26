#pragma once
#include "Hack.h"

class MegaBMXJump : public IHack
{
public:
	MegaBMXJump(const char* name);
private:
	float fBMXJumpSpeed;
	void onDrawGUI() override;
	void everyTickAction(const crTickLocalPlayerInfo& info) override;
	void save(Json::Value& data) override;
	void read(Json::Value& data)   override;
};


