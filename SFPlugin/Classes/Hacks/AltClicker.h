#pragma once
#include "Hack.h"


HACK_CLASS(AltClicker)
{
public:
	AltClicker(const char*);
private:
	bool bWorking;
	int iDelay;
	int activationKey;
	void everyTickAction( ) override;
	void onDrawGUI() override;
	
	bool onWndProc(WPARAM, UINT ) override;
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;

};
