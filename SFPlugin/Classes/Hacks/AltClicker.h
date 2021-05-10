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
	void everyTickAction( crTickLocalPlayerInfo*) override;
	void onDrawGUI() override;
	void onDrawSettings() override;
	void onWndProc(WPARAM, UINT, crTickLocalPlayerInfo*) override;
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;

};
