#pragma once
#include "Hack.h"

class AutoShot : public IHack
{
public:
	AutoShot(const char* name);
private:
	bool autoShot = false;
	int activationKey = 0;
	void onDrawGUI() override;
	void onWndProc(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info) override;
	void everyTickAction(const crTickLocalPlayerInfo& info) override;
	void save(Json::Value& data) override;
	void read(Json::Value& data) override;
};
