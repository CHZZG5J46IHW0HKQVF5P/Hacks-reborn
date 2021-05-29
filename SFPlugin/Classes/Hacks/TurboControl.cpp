#include "TurboControl.h"

void DisableTwinTurbo(bool bDisable)
{
	static const char16_t temp1 = 40169;//*(char16_t*)dwFUNC_SetVehVelocity;
	if (bDisable)
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x15030), 2, 50064); // -
	else
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x15030), 2, temp1); // +
}

DEFAULT_HACK_CONSTRUCTOR(TurboControl)

void TurboControl::onDrawGUI()
{
	ImGui::Checkbox("TurboControl", &m_bEnabled);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, g::keyButtonSplitter);

}
bool TurboControl::onWndProc()
{
	if (activationKey != 0 && g::pKeyEventInfo->iKeyID == activationKey)
		if (g::pInfo->isDriver())
			if (g::pKeyEventInfo->bDown)
			{

				DisableTwinTurbo(false);
				Stuff::AddMessageJumpQ("~r~Turbo", 500, 0, 0);

			}
			else
			{
				DisableTwinTurbo(true);
				Stuff::AddMessageJumpQ("~r~Comfort", 500, 0, 0);
			}
	return true;
}
void TurboControl::save(nlohmann::json& data)
{
	SERIALIZE_FIELD_JSON(m_bEnabled);
	SERIALIZE_FIELD_JSON(activationKey);

}
void TurboControl::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON(m_bEnabled);
	DESERIALIZE_FIELD_JSON(activationKey);
}