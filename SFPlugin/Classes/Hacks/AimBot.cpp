#include "AimBot.h"
#include "WallShot.h"
#include "GlobalFuncs.h"

DEFAULT_HACK_CONSTRUCTOR(Aimbot)

void Aimbot::onDrawGUI()
{
	ImGui::Checkbox("Aimbot", &m_bEnabled);
	if (ImGui::IsItemHovered())
	{
		SF->getRender()->DrawPolygon(cshX, cshY, m_fFov, m_fFov, 0.f, 15, 0x8883d446);
	}
	if (ImGui::BeginPopupContextItem())
	{
		ImGui::Checkbox("Can Aim To Same Colored Players", &bCanAimToSameColored);
		ImGui::InputFloat("Fov", &m_fFov);
		ImGui::EndPopup();
	}
}

void Aimbot::save(nlohmann::json& data)
{
	data[m_sHackName] = m_bEnabled;
	data["bCanAimToSameColored"] = bCanAimToSameColored;
	SERIALIZE_FIELD_JSON(m_fFov);
}

void Aimbot::read(nlohmann::json& data)
{
	m_bEnabled = data[m_sHackName].get<bool>();
	bCanAimToSameColored = data["bCanAimToSameColored"].get<bool>();
	DESERIALIZE_FIELD_JSON(m_fFov);
}


actor_info* Aimbot::getPlayerTarget()
{
	auto&& nearestToCrosshairPlayers = Players::getNearestToCrosshairPlayers(!GFuncs::isHackWorking<WallShot>());
	if (nearestToCrosshairPlayers.empty())
		return nullptr;

	GFuncs::resortPlayersByDistance(&g::pInfo->nearestPlayers, false);


	for (auto&& playerId_Dist : nearestToCrosshairPlayers)
		if (playerId_Dist.fDistance <= m_fFov)
			if (std::find_if(g::pInfo->nearestPlayers.begin(), g::pInfo->nearestPlayers.end(), [&](const NearPlayer& pair)
			{

				if (bCanAimToSameColored)
					return pair.pActorInfo == playerId_Dist.pActorInfo;
				else
				{
					if (SF->getSAMP()->getPlayers()->GetPlayerColor(pair.id) != SF->getSAMP()->getPlayers()->GetPlayerColor(MYID))
						return pair.pActorInfo == playerId_Dist.pActorInfo;
				}

				return false;
			}) != g::pInfo->nearestPlayers.end())
				return playerId_Dist.pActorInfo;
			return nullptr;


}

void Aimbot::aim(actor_info* pActorInfo)
{
	if (pActorInfo != nullptr)
	{
		CVector mypos;
		CVector enpos;
		CVector vector;
		static CCamera* pCamera = GAME->GetCamera();

		enpos.fX = pActorInfo->base.matrix[12];
		enpos.fY = pActorInfo->base.matrix[13];
		enpos.fZ = pActorInfo->base.matrix[14];

		mypos = *pCamera->GetCam(pCamera->GetActiveCam())->GetSource();
		vector = mypos - enpos;

		float* crosshairOffset = (float*)0xB6EC10;
		float mult = tan(pCamera->GetCam(pCamera->GetActiveCam())->GetFOV() * 0.5f);// *0.017853292f);
		float fx = (M_PI)-atan2(1.0f, mult * (crosshairOffset[1] - 0.5f + crosshairOffset[1] - 0.5f));

		float AngleX = atan2f(vector.fY, -vector.fX) - (M_PI) / 2;

		*(float*)0xB6F258 = -(AngleX - fx);

	}
}

void Aimbot::everyTickAction()
{
	auto&& pWeapon = PEDSELF->GetWeapon(PEDSELF->GetCurrentWeaponSlot());
	if (pWeapon->GetState() == eWeaponState::WEAPONSTATE_FIRING)
		if (Lippets::Conditions::multEqual<eWeaponSlot>(pWeapon->GetSlot(), 6,
			WEAPONSLOT_TYPE_HANDGUN, WEAPONSLOT_TYPE_HEAVY, WEAPONSLOT_TYPE_RIFLE, WEAPONSLOT_TYPE_SHOTGUN, WEAPONSLOT_TYPE_SMG, WEAPONSLOT_TYPE_MG))
			aim(getPlayerTarget());
}

