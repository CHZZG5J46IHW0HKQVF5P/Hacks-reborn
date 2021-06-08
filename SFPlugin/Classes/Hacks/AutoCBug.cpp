#include "AutoCBug.h"
#include "nameof/nameof.hpp"
DEFAULT_HACK_CONSTRUCTOR(AutoCBUG);


void applyActorAnimation(UINT16 wActorID, const char *AnimLib, const char *AnimName, float fDelta, bool loop, bool lockx, bool locky, bool freeze, UINT32 time)
{
	BitStream bs;
	bs.Write(wActorID);
	bs.Write((UINT8)strlen(AnimLib));
	bs.Write(AnimLib);
	bs.Write((UINT8)strlen(AnimName));
	bs.Write(AnimName);
	bs.Write(fDelta);

	bs.Write(loop);
	bs.Write(lockx);
	bs.Write(locky);
	bs.Write(freeze);
	bs.Write(time);
	SF->getRakNet()->emulateRecvRPC(RPC_ScrApplyAnimation, &bs);
}


void AutoCBUG::everyTickAction()
{
	static CMTimer timer;
	auto&& pWeapon = PEDSELF->GetWeapon(PEDSELF->GetCurrentWeaponSlot());

	
	if (pWeapon->GetState() == eWeaponState::WEAPONSTATE_FIRING)
	{
		timer.setTimer(m_iDelay);
		return;
	}
	if (timer.isEnded() && !timer.wasReseted())
	{
		SF->getSAMP()->getPlayers()->SetLocalPlayerName("idiot");
		GTAfunc_PerformAnimation("PED", "HIT_WALK", 0, 0, 1, 0, 0, 0, 0, 0);
		timer.reset();
	}


}

void AutoCBUG::onDrawGUI()
{
	ImGui::Checkbox("Auto CBug", &m_bEnabled);
	if (ImGui::BeginPopupContextItem())
	{
		ImGui::SliderInt("Delay", &m_iDelay, 0, 530);
		ImGui::EndPopup();
	}
}

void AutoCBUG::save(nlohmann::json& data)
{
	SERIALIZE_FIELD_JSON(m_bEnabled);
	SERIALIZE_FIELD_JSON(m_iDelay);
}

void AutoCBUG::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON(m_bEnabled);
	DESERIALIZE_FIELD_JSON(m_iDelay);
}