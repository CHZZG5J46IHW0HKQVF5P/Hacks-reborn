#pragma once
#include "Hack.h"



class TurboControl : public IHack
{
public:
	TurboControl(const char* name);
private:
	int activationKey = 0;
	void onDrawGUI() override;
	void onWndProc(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info) override;
	void save(Json::Value& data) override;
	void read(Json::Value& data) override;
};

