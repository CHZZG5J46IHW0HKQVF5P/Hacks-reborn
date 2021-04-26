#pragma once
#include "Hack.h"

class PlayersList : public IHack
{
public:
	PlayersList(const char*);
private:
	std::vector<std::string> friendsList;
	std::vector<std::string> enemiesList;
	bool connectLoger;
	bool noFriendDamage;
	void onDrawGUI() override;
	void onDrawSettings() override;
	bool onPacketOutcoming(stRakNetHookParams* params, const crTickLocalPlayerInfo& info) override;
	bool onRPCIncoming(stRakNetHookParams* params, const crTickLocalPlayerInfo& info) override;
	void save(Json::Value&) override;
	void read(Json::Value&) override;
};