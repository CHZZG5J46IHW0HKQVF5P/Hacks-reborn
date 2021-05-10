#pragma once
#include "Hack.h"


class InputHelper : public IHack
{
public:
	InputHelper(const char* name);
private:
	CMFont font = CMFont("Chat Helper");
	int offsetY = 0;
	int offsetX = 0;
	void init() override;
	void onDrawGUI() override;
	void onDrawHack( crTickLocalPlayerInfo* info) override;
	void onDrawSettings() override;
	void save(nlohmann::json& data) override;
	void read(nlohmann::json& data) override;

};