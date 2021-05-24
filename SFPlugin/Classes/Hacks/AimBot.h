#pragma once
#include "Hack.h"

HACK_CLASS(Aimbot)
{
public:
	Aimbot(const char*);
private:
	bool bCanAimToSameColored;
	float m_fFov = 90.f;
	actor_info* getPlayerTarget( );
	void aim(actor_info*);
	void everyTickAction( ) override;
	void onDrawGUI() override;
	
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;
};