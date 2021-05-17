#include "AimBot.h"

#include "WallShot.h"

#include "GlobalFuncs.h"




Aimbot::Aimbot(const char* name)
{
	m_sHackName = name;
}

void Aimbot::onDrawGUI()
{
	ImGui::Checkbox("Aimbot", &m_bEnabled);
}


void Aimbot::onDrawSettings()
{
	if (ImGui::BeginMenu("Aimbot"))
	{
		ImGui::Checkbox("Can Aim To Same Colored Players", &bCanAimToSameColored);
		ImGui::EndMenu();
	}
}

void Aimbot::save(nlohmann::json& data)
{
	data[m_sHackName] = m_bEnabled;
	data["bCanAimToSameColored"] = bCanAimToSameColored;
}

void Aimbot::read(nlohmann::json& data)
{
	m_bEnabled = data[m_sHackName].get<bool>();
	bCanAimToSameColored = data["bCanAimToSameColored"].get<bool>();
}


int Aimbot::getPlayerTarget()
{
	auto&& nearestToCrosshairPlayers = Players::getNearestToCrosshairPlayers(!GFuncs::isHackWorking<WallShot>());
	if (nearestToCrosshairPlayers.empty())
		return -1;

	GFuncs::resortPlayersByDistance(&g::pInfo->nearestPlayers, false);


	for (auto&& playerId_Dist : nearestToCrosshairPlayers)
		if (std::find_if(g::pInfo->nearestPlayers.begin(), g::pInfo->nearestPlayers.end(), [&](const std::pair<int, float>& pair)
		{
			if (bCanAimToSameColored)
				return pair.first == playerId_Dist.first;
			else
			{
				if (SF->getSAMP()->getPlayers()->GetPlayerColor(pair.first) != SF->getSAMP()->getPlayers()->GetPlayerColor(MYID))
					return pair.first == playerId_Dist.first;
			}
		}) != g::pInfo->nearestPlayers.end())
			return playerId_Dist.first;
		return -1;
}

void Aimbot::aim(int iTargetID)
{
	if (iTargetID > 0)
	{
		CVector mypos;
		CVector enpos;
		CVector vector;

		enpos.fX = SF->getSAMP()->getPlayers()->pRemotePlayer[iTargetID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12];
		enpos.fY = SF->getSAMP()->getPlayers()->pRemotePlayer[iTargetID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[13];
		enpos.fZ = SF->getSAMP()->getPlayers()->pRemotePlayer[iTargetID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[14];

		CCamera* pCamera = GAME->GetCamera();
		mypos = *pCamera->GetCam(pCamera->GetActiveCam())->GetSource();
		vector = mypos - enpos;

		float* crosshairOffset = (float*)0xB6EC10;
		float mult = tan(pCamera->GetCam(pCamera->GetActiveCam())->GetFOV() * 0.5f * 0.017853292f);
		float fx = (3.14159265358979323846) - atan2(1.0f, mult * (crosshairOffset[1] - 0.5f + crosshairOffset[1] - 0.5f));

		float AngleX = atan2f(vector.fY, -vector.fX) - (3.14159265358979323846) / 2;

		*(float*)0xB6F258 = -(AngleX - fx);
	}
}

void Aimbot::everyTickAction()
{
	eWeaponSlot gun = PEDSELF->GetWeapon(PEDSELF->GetCurrentWeaponSlot())->GetSlot();
	if (Lippets::Conditions::multEqual<eWeaponSlot>(gun, 6,
		WEAPONSLOT_TYPE_HANDGUN, WEAPONSLOT_TYPE_HEAVY, WEAPONSLOT_TYPE_RIFLE, WEAPONSLOT_TYPE_SHOTGUN, WEAPONSLOT_TYPE_SMG, WEAPONSLOT_TYPE_MG))
		if (SF->getGame()->isKeyDown(1) && SF->getGame()->isKeyDown(2))
			aim(getPlayerTarget());
}

