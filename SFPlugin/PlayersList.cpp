#include "PlayersList.h"

PlayersList::PlayersList(const char* name)
{
	this->hackName = name;
	this->isEnable = true;
}

void PlayersList::onDrawGUI()
{
	ImGui::Checkbox("Connect Logger", &connectLoger);
	ImGui::Checkbox("No Friends Damage", &noFriendDamage);
}

void PlayersList::save(Json::Value &data)
{
	data["noFriendDamage"] = noFriendDamage;
	data["Connect_logger"] = connectLoger;
	Json::Value friendsListJson;
	for (int i = 0; i < friendsList.size(); i++)
		friendsListJson[std::to_string(i)] = friendsList[i];
	data["FriendsList"] = friendsListJson;

	Json::Value enemiesListJson;
	for (int i = 0; i < enemiesList.size(); i++)
		enemiesListJson[std::to_string(i)] = enemiesList[i];
	data["EnemiesList"] = enemiesListJson;
}

void PlayersList::read(Json::Value &data)
{
	noFriendDamage = data["noFriendDamage"].asBool();
	connectLoger = data["Connect_logger"].asBool();
	Json::Value friendsListJson = data["FriendsList"];
	for (int i = 0;; i++)
	{
		std::string istr = std::to_string(i);
		if (friendsListJson[istr].isNull())
			break;
		friendsList.push_back(friendsListJson[istr].asString());
	}

	Json::Value enemiesListJson = data["EnemiesList"];
	for (int i = 0;; i++)
	{
		std::string istr = std::to_string(i);
		if (enemiesListJson[istr].isNull())
			break;
		enemiesList.push_back(enemiesListJson[istr].asString());
	}

}

void PlayersList::onDrawSettings()
{
	if (ImGui::BeginMenu("Players List"))
	{
		ImGui::BeginChild("Friends", ImVec2(330.f, 260.f), true);
		{
			static int playerID = 0;
			Lippets::ImGuiSnippets::BorderedInputInt("ID", &playerID, 0, 999, 1, 1);
			if (playerID != MYID && SF->getSAMP()->getPlayers()->IsPlayerDefined(playerID))
			{
				const char* playerName = SF->getSAMP()->getPlayers()->GetPlayerName(playerID);
				if ((std::find(friendsList.begin(), friendsList.end(), playerName) == friendsList.end()) &&
					(std::find(enemiesList.begin(), enemiesList.end(), playerName) == enemiesList.end()))
				{
					char buffer[64];
					sprintf_s(buffer, "Add %s To Friends", playerName);
					if (ImGui::Button(buffer))
						friendsList.push_back(playerName);
				}
			}
			for (int i = 0; i < friendsList.size(); i++)
			{
				ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), friendsList[i].c_str());
				if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
					friendsList.erase(friendsList.begin() + i);

			}
			ImGui::EndChild();
		}
		ImGui::BeginChild("Enemies", ImVec2(330.f, 260.f), true);
		{
			static int playerID = 0;
			Lippets::ImGuiSnippets::BorderedInputInt("ID", &playerID, 0, 999, 1, 1);
			if (playerID != MYID && SF->getSAMP()->getPlayers()->IsPlayerDefined(playerID))
			{
				const char* playerName = SF->getSAMP()->getPlayers()->GetPlayerName(playerID);
				if ((std::find(friendsList.begin(), friendsList.end(), playerName) == friendsList.end()) &&
					(std::find(enemiesList.begin(), enemiesList.end(), playerName) == enemiesList.end()))
				{
					char buffer[64];
					sprintf_s(buffer, "Add %s To Enemies", playerName);
					if (ImGui::Button(buffer))
						enemiesList.push_back(playerName);
				}
			}
			for (int i = 0; i < enemiesList.size(); i++)
			{
				ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), enemiesList[i].c_str());
				if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
					enemiesList.erase(enemiesList.begin() + i);

			}
			ImGui::EndChild();
		}
		ImGui::EndMenu();
	}
}

bool PlayersList::onPackerOutcoming(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
{
	if (!noFriendDamage || params->packetId != ID_BULLET_SYNC)
		return true;
	bool bGiveOrTake;
	UINT16 wPlayerID;
	params->bitStream->ResetReadPointer();
	params->bitStream->Read(bGiveOrTake);
	if (!bGiveOrTake)
		return true;
	params->bitStream->Read(wPlayerID);
	if (!SF->getSAMP()->getPlayers()->IsPlayerDefined(wPlayerID))
		return true;
	if (std::find(friendsList.begin(), friendsList.end(),SF->getSAMP()->getPlayers()->GetPlayerName(wPlayerID)) == friendsList.end())
		return false;
	return true;
}

bool PlayersList::onRPCIncoming(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
{
	if (!connectLoger) return true;

	if (params->packetId == 137)
	{
		UINT8 PlayerNameLength;
		char PlayerName[32];
		params->bitStream->SetReadOffset(56);
		params->bitStream->Read(PlayerNameLength);
		params->bitStream->Read(PlayerName, PlayerNameLength);
		params->bitStream->ResetReadPointer();
		PlayerName[PlayerNameLength] = '\0';
		if (std::find(friendsList.begin(), friendsList.end(), PlayerName) != friendsList.end())
		{
			SF->getSAMP()->getChat()->AddChatMessage(0xFFFF00, "[Connect Logger] К серверу подключился ваш друг, {00FF00}%s", PlayerName);
		}
		else if (std::find(enemiesList.begin(), enemiesList.end(), PlayerName) != enemiesList.end())
		{
			SF->getSAMP()->getChat()->AddChatMessage(0xFFFF00, "[Connect Logger] К серверу подключился ваш враг, {FF0000}%s", PlayerName);
		}
		return true;
	}
	else if (params->packetId == 138)
	{
		UINT16 wPlayerID;
		params->bitStream->ResetReadPointer();
		params->bitStream->Read(wPlayerID);
		params->bitStream->ResetReadPointer();
		if (!SF->getSAMP()->getPlayers()->IsPlayerDefined(wPlayerID))
			return true;
		const char* PlayerName = SF->getSAMP()->getPlayers()->GetPlayerName(wPlayerID);
		if (std::find(friendsList.begin(), friendsList.end(), PlayerName) != friendsList.end())
		{
			SF->getSAMP()->getChat()->AddChatMessage(0xFFFF00, "[Connect Logger] Ваш друг {00FF00}%s{FFFF00} вышел из игры", PlayerName);
		}
		else if (std::find(enemiesList.begin(), enemiesList.end(), PlayerName) != enemiesList.end())
		{
			SF->getSAMP()->getChat()->AddChatMessage(0xFFFF00, "[Connect Logger] Ваш враг {FF0000}%s{FFFF00} вышел из игры", PlayerName);
		}
		return true;
	}
	return true;
}