#pragma once
#include "Hack.h"
#include "CMClasses\CMReplacer.h"
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


	void sendMessageToSay(std::string);

	OVERRIDE_RELEASE;
	
	OVERRIDE_EVERY_TICK;
	OVERRIDE_RPC_OUT;
	OVERRIDE_SAVE_READ;
	OVERRIDE_DRAWGUI;

};
