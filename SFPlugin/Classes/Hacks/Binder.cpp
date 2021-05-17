#include "Binder.h"
#include <regex>
#define IG ImGui

Binder::Binder(const char* name)
{
	m_bEnabled = true;
	m_sHackName = name;

	replacer.addAdditionVarible("iLastTargetPlayerID", new int);

	replacer.addReplacement("myid", [&]()
	{
		return std::to_string(SF->getSAMP()->getPlayers()->sLocalPlayerID);
	})
		->addReplacement("myname", [&]()
	{
		return SF->getSAMP()->getPlayers()->szLocalPlayerName;
	})
		->addReplacement("myvehid", [&]()
	{
		if (!Players::isLocalPlayerInCar())
			return std::string("-1");
		return std::to_string(SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID);
	})
		->addReplacement("myvehname", [&]()
	{
		if (!Players::isLocalPlayerInCar())
			return std::string("");
		return Vehicles::getVehicleNameByModel(SF->getSAMP()->getVehicles()->pSAMP_Vehicle[SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID]->pGTA_Vehicle->base.model_alt_id);
	})
		->addReplacement("nvehid", [&]()
	{
		auto vehicles = Vehicles::getNearestVehicles();
		if (vehicles.empty()) return std::string("-1");
		if (Players::isLocalPlayerInCar())
		{
			if (vehicles.size() < 2)
				return std::string("-1");
			return std::to_string(vehicles[1].first);
		}
		return std::to_string(vehicles[0].first);
	})
		->addReplacement("nvehname", [&]()
	{
		auto vehicles = Vehicles::getNearestVehicles();
		if (vehicles.empty()) return std::string("");
		if (Players::isLocalPlayerInCar())
		{
			if (vehicles.size() < 2)
				return std::string("");
			return Vehicles::getVehicleNameByModel(SF->getSAMP()->getVehicles()->pSAMP_Vehicle[vehicles[1].first]->pGTA_Vehicle->base.model_alt_id);
		}
		return Vehicles::getVehicleNameByModel(SF->getSAMP()->getVehicles()->pSAMP_Vehicle[vehicles[0].first]->pGTA_Vehicle->base.model_alt_id);
	})
		->addReplacement("tid", [&]()
	{
		int* iLastTargetPlayerID = (int*)replacer.getAdditionVarible("iLastTargetPlayerID");
		if (*iLastTargetPlayerID == -1)
			return std::string("");
		return std::to_string(*iLastTargetPlayerID);
	})
		->addReplacement("tname", [&]()
	{
		int* iLastTargetPlayerID = (int*)replacer.getAdditionVarible("iLastTargetPlayerID");
		if (*iLastTargetPlayerID == -1)
			return std::string("");
		if (!SF->getSAMP()->getPlayers()->IsPlayerDefined(*iLastTargetPlayerID))
			return std::string("");
		return std::string(SF->getSAMP()->getPlayers()->GetPlayerName(*iLastTargetPlayerID));
	})
		->addReplacement("nplayerid", [&]()
	{
		auto players = Players::getNearestPlayers();
		if (players.empty()) return std::string("-1");
		return std::to_string(players[0].first);
	})
		->addReplacement("nplayername", [&]()
	{
		auto players = Players::getNearestPlayers();
		if (players.empty()) return std::string("");
		if (!SF->getSAMP()->getPlayers()->IsPlayerDefined(players[0].first))
			return std::string("");
		return std::string(SF->getSAMP()->getPlayers()->GetPlayerName(players[0].first));
	});
}

void Binder::release()
{
	replacer.~CMReplacer();
}

bool Bind::areSubKeysPressed()
{
	if (ctrl)
		if (!g::isCtrlPressed)
			return false;
	if (alt)
		if (!g::isAltPressed)
			return false;
	if (shift)
		if (!g::isShiftPressed)
			return false;
	return true;
}

bool Bind::checkKeys()
{
	if (!areSubKeysPressed()) return false;
	if (activateCheat.empty()) return false;
	if (bindTexts.empty()) return false;
	if (bindTexts[0].empty()) return false;
	return Stuff::TestCheat(activateCheat.c_str());
}

void Command::read(nlohmann::json& data)
{
	shortCmd = data["shortCmd"].get<std::string>();
	bSendOrigin = data["sendOrigin"].get<bool>();
	commandsTexts = data["commandsTexts"].get<std::vector<std::pair<std::string, bool>>>();
}

void Command::save(nlohmann::json& data)
{
	data["sendOrigin"] = bSendOrigin;
	data["commandsTexts"] = commandsTexts;
	data["shortCmd"] = shortCmd;
}

void Bind::read(nlohmann::json& data)
{
	activateCheat = data["bindCheat"].get<std::string>();
	bindTexts = data["bindsTexts"].get<std::vector<std::string>>();
	ctrl = data["ctrl"].get<bool>();
	alt = data["alt"].get<bool>();
	shift = data["shift"].get<bool>();
}

void Bind::save(nlohmann::json& data)
{
	data["bindsTexts"] = bindTexts;
	data["bindCheat"] = activateCheat;
	data["ctrl"] = ctrl;
	data["alt"] = alt;
	data["shift"] = shift;
}

void Binder::save(nlohmann::json& data)
{
	data["iBinderDelay"] = iBinderDelay;
	data["iCommandsDelay"] = iCommandsDelay;
	data["isBinderEnabled"] = isBinderEnabled;
	data["isCommandsEnabled"] = isCommandsEnabled;

	nlohmann::json bindsJson;
	for (int i = 0; i < binds.size(); i++)
		binds[i].save(bindsJson[std::to_string(i)]);
	data["BindsJson"] = bindsJson;

	nlohmann::json commandsJson;
	for (int i = 0; i < commands.size(); i++)
		commands[i].save(commandsJson[std::to_string(i)]);
	data["CommandsJson"] = commandsJson;
}

void Binder::read(nlohmann::json& data)
{
	iBinderDelay = data["iBinderDelay"].get<int>();
	iCommandsDelay = data["iCommandsDelay"].get<int>();

	isBinderEnabled = data["isBinderEnabled"].get<bool>();;
	isCommandsEnabled = data["isCommandsEnabled"].get<bool>();

	nlohmann::json bindsJson = data["BindsJson"];
	if (!bindsJson.is_null())
		for (int i = 0;; i++)
		{
			std::string istr = std::to_string(i);
			if (bindsJson[istr].is_null())
				break;
			binds.push_back(Bind());
			binds.back().read(bindsJson[istr]);
		}

	nlohmann::json commandsJson = data["CommandsJson"];
	if (!commandsJson.is_null())
		for (int i = 0;; i++)
		{
			std::string istr = std::to_string(i);
			if (commandsJson[istr].is_null())
				break;
			commands.push_back(Command());
			commands.back().read(commandsJson[istr]);
		}

	if (iCommandsDelay == 0)
		iCommandsDelay = 100;
	if (iBinderDelay == 0)
		iBinderDelay = 100;
}

void Binder::onDrawGUI()
{
	IG::Checkbox("Binder", &isBinderEnabled);
	IG::SameLine();
	IG::Checkbox("Editor###binder", &isBinderWindowOpen);
	IG::Checkbox("Commands", &isCommandsEnabled);
	IG::SameLine();
	IG::Checkbox("Editor###commands", &isCommandsWindowOpen);
	if (isBinderWindowOpen)
	{
		ImGui::Begin("Binder");
		Lippets::ImGuiSnippets::BorderedInputInt("Delay", &iBinderDelay, 10, 20000, 1, 1);
		if (IG::Button("Create Bind"))
			binds.push_back(Bind());
		for (int i = 0; i < binds.size(); i++)
		{
			char buffer[64];
			sprintf(buffer, "Bind: %s###bind%d", binds[i].activateCheat.c_str(), i);
			if (IG::CollapsingHeader(buffer))
			{

				sprintf(buffer, "Remove###removebtn%d", i);
				if (IG::Button(buffer))
				{
					binds.erase(binds.begin() + i);
					i = 0;
				}
				IG::SameLine();
				sprintf(buffer, "Ctrl###ctrl%d", i);
				IG::Checkbox(buffer, &binds[i].ctrl);
				IG::SameLine();
				sprintf(buffer, "Alt###alt%d", i);
				IG::Checkbox(buffer, &binds[i].alt);
				IG::SameLine();
				sprintf(buffer, "Shift###shift%d", i);
				IG::Checkbox(buffer, &binds[i].shift);

				sprintf(buffer, "Activation Cheat###cheatText%d", i);
				IG::SetNextItemWidth(45.f);
				IG::InputText(buffer, &binds[i].activateCheat);

				sprintf(buffer, "Add Sub###Textaddbtn%d", i);
				if (IG::Button(buffer))
					binds[i].bindTexts.push_back("");
				for (int j = 0; j < binds[i].bindTexts.size(); j++)
				{
					sprintf(buffer, "Text###Text%d%d", i, j);

					IG::InputText(buffer, &binds[i].bindTexts[j]);
					IG::SameLine();
					sprintf(buffer, "Remove###removeTextbtn%d%d", i, j);
					if (IG::Button(buffer))
						binds[i].bindTexts.erase(binds[i].bindTexts.begin() + j);
				}
			}

		}
		ImGui::End();
	}
	if (isCommandsWindowOpen)
	{
		ImGui::Begin("Commands");
		Lippets::ImGuiSnippets::BorderedInputInt("Delay", &iCommandsDelay, 10, 20000, 1, 1);
		if (IG::Button("Create command"))
			commands.push_back(Command());
		for (int i = 0; i < commands.size(); i++)
		{
			char buffer[64];
			sprintf(buffer, "Cmd: %s###cmd%d", commands[i].shortCmd.c_str(), i);
			if (IG::CollapsingHeader(buffer))
			{
				char buffer[32];
				sprintf(buffer, "Remove###removebtn%d", i);
				if (IG::Button(buffer))
				{
					commands.erase(commands.begin() + i);
					i = 0;
				}
				sprintf(buffer, "Short Command###cheatText%d", i);
				IG::SetNextItemWidth(45.f);
				IG::InputText(buffer, &commands[i].shortCmd);
				IG::SameLine();
				sprintf(buffer, "Send Origin###sendOriginCHB%d", i);
				IG::Checkbox(buffer, &commands[i].bSendOrigin);
				sprintf(buffer, "Add Sub###Textaddbtn%d", i);
				if (IG::Button(buffer))
					commands[i].commandsTexts.push_back(std::make_pair("", false));
				for (int j = 0; j < commands[i].commandsTexts.size(); j++)
				{
					sprintf(buffer, "Text###Text%d%d", i, j);
					IG::InputText(buffer, &commands[i].commandsTexts[j].first);
					IG::SameLine();
					sprintf(buffer, "Remove###removeTextbtn%d%d", i, j);
					if (IG::Button(buffer))
						commands[i].commandsTexts.erase(commands[i].commandsTexts.begin() + j);
					IG::SameLine();
					sprintf(buffer, "Add Args###AddArgsCHB%d%d", i, j);
					IG::Checkbox(buffer, &commands[i].commandsTexts[j].second);
				}
			}
		}
		ImGui::End();
	}
}

bool Binder::onRPCOutcoming(stRakNetHookParams* params)
{
	if (!isCommandsEnabled || params->packetId != RPCEnumeration::RPC_ServerCommand || commands.empty())// || commands[0].shortCmd.empty() || commands[0].commandsTexts.empty() || choosenCommandID != -1)
		return true;
	UINT32 length;
	char *buffer;
	std::string cmdText;
	params->bitStream->ResetReadPointer();
	params->bitStream->Read(length);
	buffer = new char[length];
	params->bitStream->Read(buffer, length);
	buffer[length] = '\0';
	cmdText = buffer;
	cmdText.erase(0, 1);

	delete[] buffer;

	if (cmdText.find(" ") != std::string::npos)
		sLastCmdArgs = cmdText.substr(cmdText.find(" "));

	for (int i = 0; i < commands.size(); i++)
	{
		if (commands[i].shortCmd == cmdText.substr(0, cmdText.find(" ")))
		{
			this->choosenCommandID = i;
			return commands[i].bSendOrigin;
		}
	}
	return true;
}

void Binder::sendMessageToSay(std::string message)
{
	if (message.empty())
		return;

	replacer.replace(message);

	if (message.at(0) == '/')
	{
		BitStream bitStream;
		bitStream.Write((uint32_t)message.length());
		bitStream.Write(message.c_str(), message.length());
		SF->getRakNet()->SendRPC(50, &bitStream);   // sendCmdMessage
	}
	else
		SF->getSAMP()->getPlayers()->pLocalPlayer->Say((char*)message.data());
}

void Binder::everyTickAction()
{
	
	int* iLastTargetPlayerID = (int*)replacer.getAdditionVarible("iLastTargetPlayerID");
	if (SF->getSAMP()->getPlayers()->pLocalPlayer->sAimingAtPid < 1000)
		*iLastTargetPlayerID = SF->getSAMP()->getPlayers()->pLocalPlayer->sAimingAtPid;
	if (isBinderEnabled)
	{
		static CMTimer bindTimer;
		static int choosenBindID = -1;
		static int choosenTextID = 0;
		static int bindID = 0;

		if (SF->getSAMP()->getDialog()->pDialog != nullptr && SF->getSAMP()->getDialog()->iIsActive != 1 && !binds.empty())
		{
			if (bindID >= binds.size())
				bindID = 0;
			if (binds[bindID].checkKeys())
			{

				choosenBindID = bindID;
				choosenTextID = 0;
				sendMessageToSay(binds[choosenBindID].bindTexts[choosenTextID]);
				bindTimer.setTimer(iBinderDelay);
			}
			else if (choosenBindID == -1)
			{
				bindID++;
				goto continueLabel1;
			}
			if (bindTimer.isEnded())
			{
				choosenTextID++;
				if (choosenTextID >= binds[choosenBindID].bindTexts.size())
				{
					choosenTextID = 0;
					choosenBindID = -1;
					goto continueLabel1;
				}
				sendMessageToSay(binds[choosenBindID].bindTexts[choosenTextID]);
				bindTimer.setTimer(iBinderDelay);
			}
		}

	}
continueLabel1:
	{

	}
	if (isCommandsEnabled)
	{
		static CMTimer commandTimer;
		static int choosenTextID = 0;
		if (choosenCommandID == -1)
			goto continueLabel2;
		if (commandTimer.isEnded())
		{
			if (choosenTextID >= commands[choosenCommandID].commandsTexts.size())
			{
				choosenTextID = 0;
				choosenCommandID = -1;
				goto continueLabel2;
			}

			sendMessageToSay(commands[choosenCommandID].commandsTexts[choosenTextID].first + (commands[choosenCommandID].commandsTexts[choosenTextID].second ? sLastCmdArgs : ""));
			commandTimer.setTimer(iCommandsDelay);
			choosenTextID++;
		}
	}
continueLabel2:
	{

	}
}