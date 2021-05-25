#include "AltClicker.h"

DEFAULT_HACK_CONSTRUCTOR(AltClicker)

void AltClicker::onDrawGUI()
{
	ImGui::Checkbox(m_sHackName.c_str(), &m_bEnabled);
	if (ImGui::BeginPopupContextVoid())
	{
		ImGui::SliderInt("Click Delay", &iDelay, 1, 300);
		ImGui::EndPopup();
	}
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, g::keyButtonSplitter);
}

void AltClicker::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON(m_bEnabled);
	DESERIALIZE_FIELD_JSON(iDelay);
	DESERIALIZE_FIELD_JSON(activationKey);
	ASSIGN_VAR_VALUE_IF_EQUALS_ZERO(iDelay,25);
}

void AltClicker::save(nlohmann::json& data)
{
	SERIALIZE_FIELD_JSON(m_bEnabled);
	SERIALIZE_FIELD_JSON(activationKey);
	SERIALIZE_FIELD_JSON(iDelay);
}




bool AltClicker::onWndProc()
{
	if (!g::pKeyEventInfo->bDown)
		return true;

	if (activationKey != 0 && g::pKeyEventInfo->iKeyID== activationKey)
	{
		bWorking = !bWorking;
		notify("ALT Clicker", bWorking);
	}
	return true;
}

void AltClicker::everyTickAction( )
{
	static CMTimer timer;
	static uint8 eALTstate = 1;
	if (bWorking)
		if (timer.isEnded())
		{
			if (eALTstate == 1)
			{
				timer.setTimer(1);
				eALTstate = 2;
				SF->getGame()->emulateGTAKey(21, 255);
			}
			else if (eALTstate == 2)
			{
				timer.setTimer(iDelay);
				eALTstate = 1;
				SF->getGame()->emulateGTAKey(21, 0);
			}
		}

}