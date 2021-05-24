#pragma once
#include "Hack.h"

HACK_CLASS(AutoShot)
{
public:
	AutoShot(const char*);
private:
	bool autoShot = false;
	int activationKey = 0;
	void onDrawGUI() override;
	bool onWndProc(WPARAM wParam, UINT msg  ) override;
	void everyTickAction( ) override;
	void save(nlohmann::json& data) override;
	void read(nlohmann::json& data) override;
};
