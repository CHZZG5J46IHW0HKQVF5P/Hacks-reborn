#pragma once
#include "Hack.h"
#include "C:\Lippets\CMClasses\CMReplacer.h"
#include <utility>


class Bind
{
public:
	bool ctrl, alt, shift;
	std::string activateCheat;
	std::vector<std::string> bindTexts;
	bool checkKeys();
	bool areSubKeysPressed();
	void save(nlohmann::json&);
	void read(nlohmann::json&);
};

class Command
{
public:													
	std::string shortCmd;
	bool bSendOrigin;
	std::vector<std::pair<std::string, bool>> commandsTexts;
	void save(nlohmann::json&);
	void read(nlohmann::json&);
};



class Binder : public IHack
{
public:
	Binder(const char*name);
private:
	bool isBinderEnabled;
	bool isCommandsEnabled;
	int iBinderDelay;
	int iCommandsDelay;
	CMReplacer replacer;
	std::vector<Bind> binds;
	std::vector<Command> commands;
	int choosenCommandID = -1;
	std::string sLastCmdArgs;


	void sendMessageToSay(std::string);
	void everyTickAction( crTickLocalPlayerInfo*) override;
	bool onRPCOutcoming(stRakNetHookParams*,  crTickLocalPlayerInfo*) override;
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;
	void onDrawGUI() override;

};
