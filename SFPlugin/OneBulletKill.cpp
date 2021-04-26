#include "OneBulletKill.h"

DamageInfo::DamageInfo() {}
DamageInfo::DamageInfo(UINT16 wPlayerID,
	float damage_amount,
	UINT32 dWeaponID,
	UINT32 dBodypart)
{
	this->damage_amount = damage_amount;
	this->dBodypart = dBodypart;
	this->dWeaponID = dWeaponID;
	this->wPlayerID = wPlayerID;
}

OneBulletKill::OneBulletKill(const char* name)
{
	hackName = name;
}

void OneBulletKill::save(Json::Value& data)
{
	data[hackName] = isEnable;
	data["delay"] = iDelay;
}

void OneBulletKill::read(Json::Value& data)
{
	isEnable = data[hackName].asBool();
	iDelay = data["delay"].asInt();
	if (iDelay == 0)
		iDelay = 50;
}

bool OneBulletKill::onRPCOutcoming(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
{
	if (params->packetId != 115) // Give/Take Damage
		return true;
	// bool bGiveOrTake, UINT16 wPlayerID, float damage_amount, UINT32 dWeaponID, UINT32 dBodypart
	bool bGiveOrTake;
	UINT16 wPlayerID;
	float damage_amount;
	UINT32 dWeaponID;
	UINT32 dBodypart;
	params->bitStream->ResetReadPointer();
	params->bitStream->Read(bGiveOrTake);
	params->bitStream->Read(wPlayerID);
	params->bitStream->Read(damage_amount);
	params->bitStream->Read(dWeaponID);
	params->bitStream->Read(dBodypart);

	if (wPlayerID >= 1000) return true;
	if (!Players::isPlayerExist(wPlayerID)) return true;

	float fPlayerHealth = SF->getSAMP()->getPlayers()->pRemotePlayer[wPlayerID]->pPlayerData->fActorHealth +
		SF->getSAMP()->getPlayers()->pRemotePlayer[wPlayerID]->pPlayerData->fActorArmor;

	sendDamageDeuqeLength = (fPlayerHealth / damage_amount) + 2;

	dInfo = DamageInfo(wPlayerID, damage_amount, dWeaponID, dBodypart);

	return false;
}

void OneBulletKill::everyTickAction(const crTickLocalPlayerInfo& info)
{
	static DWORD lastSendDamageTime = 0;
	if (sendDamageDeuqeLength > 0)
		if (lastSendDamageTime < GetTickCount())
		{
			--sendDamageDeuqeLength;
			SF->getSAMP()->sendGiveDamage(dInfo.wPlayerID, dInfo.damage_amount, dInfo.dWeaponID, dInfo.dBodypart);
			lastSendDamageTime = GetTickCount() + iDelay;
		}

}

void OneBulletKill::onDrawGUI()
{
	ImGui::Checkbox("One Bullet Kill", &isEnable);
}

void OneBulletKill::onDrawSettings()
{
	if (ImGui::BeginMenu("New Name Tags"))
	{
		ImGui::SliderInt("Delay Between Sending Damage",&iDelay,10,1000);
		ImGui::EndMenu();
	}
}