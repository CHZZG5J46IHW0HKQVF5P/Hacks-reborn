#pragma once
#include "Hack.h"

HACK_CLASS(PlayersList)
{
public:
	PlayersList(const char*);
private:
	ImVec2 friendsListWindowPos;
	ImVec2 enemiesListWindowPos;
	std::vector<std::string> friendsList;
	std::vector<std::string> enemiesList;
	bool connectLoger;
	bool noFriendDamage;
	OVERRIDE_DRAW_HACK;
	OVERRIDE_DRAWGUI;
	
	OVERRIDE_PACKET_OUT;
	OVERRIDE_RPC_INC;
	OVERRIDE_SAVE_READ;
};