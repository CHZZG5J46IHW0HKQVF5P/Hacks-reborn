#pragma once
#include "Hack.h"

class Aimbot : public IHack
{
public:
	Aimbot(const char*);
private:
	bool bCanAimToSameColored;
	int getPlayerTarget( );
	void aim(int);
	void everyTickAction( ) override;
	void onDrawGUI() override;
	void onDrawSettings() override;
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;
};