#pragma once
#include "Hack.h"



class TurboControl : public IHack
{
public:
	TurboControl(const char* name);
private:
	int activationKey = 0;
	void onDrawGUI() override;
	void onWndProc(WPARAM wParam, UINT msg) override;
	void save(nlohmann::json& data) override;
	void read(nlohmann::json& data) override;
};

