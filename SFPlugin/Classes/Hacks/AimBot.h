#pragma once
#include "Hack.h"

class Aimbot : public IHack
{
public:
	Aimbot(const char*);
private:
	bool bCanAimToSameColored;
	int getPlayerTarget( crTickLocalPlayerInfo*);
	void aim(int);
	void everyTickAction( crTickLocalPlayerInfo*) override;
	void onDrawGUI() override;
	void onDrawSettings() override;
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;
};