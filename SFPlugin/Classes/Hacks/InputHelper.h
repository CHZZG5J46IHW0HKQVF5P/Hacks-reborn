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
	void onDrawHack(const crTickLocalPlayerInfo& info) override;
	void onDrawSettings() override;
	void save(Json::Value& data) override;
	void read(Json::Value& data) override;

};