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
	void everyTickAction(const crTickLocalPlayerInfo&) override;
	void onDrawGUI() override;
	void onDrawSettings() override;
	void onWndProc(WPARAM, UINT,const crTickLocalPlayerInfo&) override;
	void save(Json::Value&) override;
	void read(Json::Value&) override;

};
