#include "AutoShot.h"


DEFAULT_HACK_CONSTRUCTOR(AutoShot)

void AutoShot::onDrawGUI()
{
	ImGui::Checkbox("Auto Shot", &m_bEnabled);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, g::keyButtonSplitter);
}
bool AutoShot::onWndProc()
{
	if (!g::pKeyEventInfo->bDown)
		return true;
	if (activationKey != 0 && g::pKeyEventInfo->iKeyID == activationKey)
	{
		autoShot = !autoShot;
		notify("Auto Shot", autoShot);
	}
	return true;
}
void AutoShot::everyTickAction()
{
	if (!g::pInfo->isExist || !autoShot || g::pInfo->isInCar)
		return;
	if (*(DWORD*)PEDSELF->GetMemoryValue(0x79C))
		SF->getGame()->emulateGTAKey(17, 255);
}
void AutoShot::save(nlohmann::json& data)
{
	SERIALIZE_FIELD_JSON(activationKey);
	SERIALIZE_FIELD_JSON(m_bEnabled);

}
void AutoShot::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON(activationKey);
	DESERIALIZE_FIELD_JSON(m_bEnabled);
}