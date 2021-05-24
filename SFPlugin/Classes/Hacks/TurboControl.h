#pragma once
#include "Hack.h"



HACK_CLASS(TurboControl)
{
public:
	TurboControl(const char* name);
private:
	int activationKey = 0;
	void onDrawGUI() override;
	bool onWndProc(WPARAM wParam, UINT msg) override;
	void save(nlohmann::json& data) override;
	void read(nlohmann::json& data) override;
};

