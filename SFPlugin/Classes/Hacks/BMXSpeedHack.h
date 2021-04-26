#pragma once

#include "Hack.h"

class BMXspeedhack : public IHack
{
public:
	BMXspeedhack(const char* name);
private:
	int activationKey = 0;
	bool bmxspeedHack = false;
	void onDrawGUI() override;
	void onWndProc(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info) override;
	void everyTickAction(const crTickLocalPlayerInfo& info) override;
	void save(Json::Value& data) override;
	void read(Json::Value& data) override;
};
