#include "BMXSpeedHack.h"


DEFAULT_HACK_CONSTRUCTOR(BMXspeedhack)

void BMXspeedhack::onDrawGUI()
{
	ImGui::Checkbox(m_sHackName.c_str(), &m_bEnabled);
	if (ImGui::BeginPopupContextItem())
	{
		ImGui::SliderInt("Delay", &iDelay, 1, 300);
		ImGui::EndPopup();
	}
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, g::keyButtonSplitter);
}

bool BMXspeedhack::onWndProc()
{
	if (activationKey != 0 && g::pKeyEventInfo->iKeyID == activationKey)
		if (g::pKeyEventInfo->bDown)
		{
			bmxspeedHack = true;
		}
		else 
		{
			bmxspeedHack = false;
		}
	return true;
}
void BMXspeedhack::everyTickAction( )
{
	if (!g::pInfo->isDriver || g::pInfo->vehType != Vehicles::eVehicleType::CBMX || !bmxspeedHack)
		return;
	static uint8 BMXState = 1;
	static CMTimer timer;
	if (timer.isEnded())
	{
		if (BMXState == 1)
		{
			timer.setTimer(iDelay);
			BMXState = 2;
			SF->getGame()->emulateGTAKey(16, 128);
		}
		else if (BMXState == 2)
		{
			timer.setTimer(iDelay);
			BMXState = 1;
			SF->getGame()->emulateGTAKey(16, 255);
		}
	}

}
void BMXspeedhack::save(nlohmann::json& data)
{
	SERIALIZE_FIELD_JSON(activationKey);
	SERIALIZE_FIELD_JSON(m_bEnabled);

}
void BMXspeedhack::read(nlohmann::json& data)
{
	
	DESERIALIZE_FIELD_JSON(m_bEnabled); 
	DESERIALIZE_FIELD_JSON(activationKey);
}