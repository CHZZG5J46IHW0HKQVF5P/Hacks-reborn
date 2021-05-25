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



HACK_CLASS(Binder)
{
public:
	Binder(const char*name);
private:
	bool isBinderEnabled, isBinderWindowOpen;
	bool isCommandsEnabled, isCommandsWindowOpen;
	int iBinderDelay;
	int iCommandsDelay;
	CMReplacer replacer;
	std::vector<Bind> binds;
	std::vector<Command> commands;
	int choosenCommandID = -1;
	std::string sLastCmdArgs;


	OVERRIDE_RELEASE;
	void sendMessageToSay(std::string);
	OVERRIDE_EVERY_TICK;
	bool onRPCOutcoming(stRakNetHookParams* ) override;
	OVERRIDE_SAVE_READ;
	void onDrawGUI() override;

};
