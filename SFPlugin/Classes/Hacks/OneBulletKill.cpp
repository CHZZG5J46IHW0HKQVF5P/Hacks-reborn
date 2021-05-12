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
	m_dwProperties |= (HackProperties::EVERYTICK_ACTION | HackProperties::RPCOUT);
	m_sHackName = name;
}

void OneBulletKill::save(nlohmann::json& data)
{
	data[m_sHackName] = m_bEnabled;
	data["delay"] = iDelay;
}

void OneBulletKill::read(nlohmann::json& data)
{
	m_bEnabled = data[m_sHackName].get<bool>();
	iDelay = data["delay"].get<int>();
	if (iDelay == 0)
		iDelay = 50;
}

bool OneBulletKill::onRPCOutcoming(stRakNetHookParams* params,  crTickLocalPlayerInfo* info)
{
	if (params->packetId != RPCEnumeration::RPC_GiveTakeDamage) // Give/Take Damage
		return true;

	bool bGiveOrTake;
	UINT16 wPlayerID;
	float damage_amount;
	UINT32 dWeaponID;
	UINT32 dBodypart;
	params->bitStream->ResetReadPointer();
	params->bitStream->Read(bGiveOrTake);

	if (bGiveOrTake)
		return true;

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


void OneBulletKill::everyTickAction( crTickLocalPlayerInfo* info)
{
	static CMTimer sendDamageTimer;
	if (sendDamageDeuqeLength > 0)
		if (sendDamageTimer.isEnded())
		{
			if (PEDSELF->GetWeapon(PEDSELF->GetCurrentWeaponSlot())->GetType() == dInfo.dWeaponID)
			{
				--sendDamageDeuqeLength;
				SF->getSAMP()->sendGiveDamage(dInfo.wPlayerID, dInfo.damage_amount, dInfo.dWeaponID, dInfo.dBodypart);
				sendDamageTimer.setTimer(iDelay);
			}
		}

}

void OneBulletKill::onDrawGUI()
{
	ImGui::Checkbox("One Bullet Kill", &m_bEnabled);
}

void OneBulletKill::onDrawSettings()
{
	if (ImGui::BeginMenu("One Bullet Kill"))
	{
		ImGui::SliderInt("Delay Between Sending Damage",&iDelay,70,1000);
		ImGui::EndMenu();
	}
}