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
	
	void onDrawGUI() override;
	bool onWndProc(WPARAM wParam, UINT msg  ) override;
	void everyTickAction( ) override;
	void save(nlohmann::json& data) override;
	void read(nlohmann::json& data) override;
};
