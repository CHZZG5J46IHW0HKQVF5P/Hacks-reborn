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

DEFAULT_HACK_CONSTRUCTOR(OneBulletKill)

void OneBulletKill::save(nlohmann::json& data)
{
	SERIALIZE_FIELD_JSON(m_bEnabled);
	SERIALIZE_FIELD_JSON(iDelay);
}

void OneBulletKill::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON(m_bEnabled);
	DESERIALIZE_FIELD_JSON(iDelay);

	ASSIGN_VAR_VALUE_IF_NOT_IN_BOUNDS(iDelay, 70, 1000, 100);
}

bool OneBulletKill::onRPCOutcoming(stRakNetHookParams* params)
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


void OneBulletKill::everyTickAction( )
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
	if (ImGui::BeginPopupContextItem())
	{
		ImGui::SliderInt("Delay Between Sending Damage", &iDelay, 70, 1000);
		ImGui::EndPopup();
	}
}
