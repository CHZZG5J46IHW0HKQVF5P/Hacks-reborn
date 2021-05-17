#pragma once
#include "Hack.h"


class BMXspeedhack : public IHack
{
public:
	BMXspeedhack(const char* name);
private:
	int activationKey = 0;
	int iDelay;
	bool bmxspeedHack = false;
	void onDrawSettings() override;
	void onDrawGUI() override;
	void onWndProc(WPARAM wParam, UINT msg  ) override;
	void everyTickAction( ) override;
	void save(nlohmann::json& data) override;
	void read(nlohmann::json& data) override;
};
