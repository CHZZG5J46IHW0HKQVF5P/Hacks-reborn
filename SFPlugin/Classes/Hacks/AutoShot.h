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
	void onWndProc(WPARAM wParam, UINT msg  ) override;
	void everyTickAction( ) override;
	void save(nlohmann::json& data) override;
	void read(nlohmann::json& data) override;
};
