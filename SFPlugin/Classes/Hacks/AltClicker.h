#pragma once
#include "Hack.h"


class AltClicker : public IHack
{
public:
	AltClicker(const char*);
private:
	bool bWorking;
	int iDelay;
	int activationKey;
	void everyTickAction( ) override;
	void onDrawGUI() override;
	void onDrawSettings() override;
	void onWndProc(WPARAM, UINT ) override;
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;

};
