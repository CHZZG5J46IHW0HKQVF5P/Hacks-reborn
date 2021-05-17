#include "PlayersList.h"
#include "GlobalFuncs.h"
PlayersList::PlayersList(const char* name)
{
	m_bDrawHackNeedImGui = true;
	m_sHackName = name;
	m_bEnabled = true;
}

void PlayersList::onDrawGUI()
{
	ImGui::Checkbox("Connect Logger", &connectLoger);
	ImGui::Checkbox("No Friends Damage", &noFriendDamage);
}

void PlayersList::save(nlohmann::json &data)
{
	data["noFriendDamage"] = noFriendDamage;
	data["Connect_logger"] = connectLoger;

	data["FriendsList"] = friendsList;

	data["EnemiesList"] = enemiesList;

	data["FriendsListWindowPos"]["x"] = friendsListWindowPos.x;
	data["FriendsListWindowPos"]["y"] = friendsListWindowPos.y;

	data["EnemiesListWindowPos"]["x"] = enemiesListWindowPos.x;
	data["EnemiesListWindowPos"]["y"] = enemiesListWindowPos.y;
}

void PlayersList::read(nlohmann::json &data)
{
	noFriendDamage = data["noFriendDamage"].get<bool>();
	connectLoger = data["Connect_logger"].get<bool>();
	friendsList = data["FriendsList"].get<std::vector<std::string>>();

	enemiesList = data["EnemiesList"].get<std::vector<std::string>>();


	friendsListWindowPos.x = data["FriendsListWindowPos"]["x"].get<float>();
	friendsListWindowPos.y = data["FriendsListWindowPos"]["y"].get<float>();

	enemiesListWindowPos.x = data["EnemiesListWindowPos"]["x"].get<float>();
	enemiesListWindowPos.y = data["EnemiesListWindowPos"]["y"].get<float>();

}

void PlayersList::onDrawHack()
{

	if (g::pInfo->nearestPlayers.empty())
		return;

	GFuncs::resortPlayersByDistance(&g::pInfo->nearestPlayers, false);
	if (std::find_if(g::pInfo->nearestPlayers.begin(), g::pInfo->nearestPlayers.end(), [&](const std::pair<int, float>& id_dist)
	{
		return std::find(friendsList.begin(), friendsList.end(), SF->getSAMP()->getPlayers()->GetPlayerName(id_dist.first)) != friendsList.end();
	}) != g::pInfo->nearestPlayers.end())
	{
		ImGui::SetNextWindowPos(friendsListWindowPos, ImGuiCond_FirstUseEver);
		ImGui::Begin("Friends", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar);
		{
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), "Friends");
			ImGui::Separator();
			for (auto&& player : g::pInfo->nearestPlayers)
			{
				auto szPlayerName = SF->getSAMP()->getPlayers()->GetPlayerName(player.first);
				if (std::find(friendsList.begin(), friendsList.end(), std::string(szPlayerName)) == friendsList.end())
					continue;
				ImGui::TextColored(ImGui::ColorConvertU32ToFloat4(SF->getSAMP()->getPlayers()->GetPlayerColor(player.first)), "%s[%d] %.1f", szPlayerName, player.first, player.second);
			}
			friendsListWindowPos = ImGui::GetWindowPos();
		}
		ImGui::End();
	}

	if (std::find_if(g::pInfo->nearestPlayers.begin(), g::pInfo->nearestPlayers.end(), [&](const std::pair<int, float>& id_dist)
	{
		return std::find(enemiesList.begin(), enemiesList.end(), SF->getSAMP()->getPlayers()->GetPlayerName(id_dist.first)) != enemiesList.end();
	}) != g::pInfo->nearestPlayers.end())
	{
		ImGui::SetNextWindowPos(enemiesListWindowPos, ImGuiCond_FirstUseEver);
		ImGui::Begin("Enemies", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar);
		{
			ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "Enemies");
			ImGui::Separator();
			for (auto&& player : g::pInfo->nearestPlayers)
			{
				auto szPlayerName = SF->getSAMP()->getPlayers()->GetPlayerName(player.first);
				if (std::find(enemiesList.begin(), enemiesList.end(), std::string(szPlayerName)) == enemiesList.end())
					continue;
				ImGui::TextColored(ImGui::ColorConvertU32ToFloat4(SF->getSAMP()->getPlayers()->GetPlayerColor(player.first)), "%s[%d] %.1f", szPlayerName, player.first, player.second);
			}
			enemiesListWindowPos = ImGui::GetWindowPos();
		}
		ImGui::End();
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
					char buffer[128];
					sprintf_s(buffer, "Add %s To Friends", playerName);
					if (ImGui::Button(buffer))
						friendsList.push_back(std::string(playerName));
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
					char buffer[128];
					sprintf_s(buffer, "Add %s To Enemies", playerName);
					if (ImGui::Button(buffer))
						enemiesList.push_back(std::string(playerName));
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

bool PlayersList::onPacketOutcoming(stRakNetHookParams* params)
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
	if (std::find(friendsList.begin(), friendsList.end(), SF->getSAMP()->getPlayers()->GetPlayerName(wPlayerID)) == friendsList.end())
		return false;
	return true;
}

bool PlayersList::onRPCIncoming(stRakNetHookParams* params)
{
	if (!connectLoger) return true;

	if (params->packetId == ScriptRPCEnumeration::RPC_ScrServerJoin)
	{
		UINT8 PlayerNameLength;
		char PlayerName[64];
		params->bitStream->SetReadOffset(56);
		params->bitStream->Read(PlayerNameLength);
		if (PlayerNameLength >= 64)
			return true;
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
	else if (params->packetId == ScriptRPCEnumeration::RPC_ScrServerQuit)
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