#pragma once
#include "Hack.h"

class PlayersList : public IHack
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
	void onDrawHack(crTickLocalPlayerInfo* info) override;
	void onDrawGUI() override;
	void onDrawSettings() override;
	bool onPacketOutcoming(stRakNetHookParams* params, crTickLocalPlayerInfo* info) override;
	bool onRPCIncoming(stRakNetHookParams* params, crTickLocalPlayerInfo* info) override;
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;
};