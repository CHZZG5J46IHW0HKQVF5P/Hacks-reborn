#include "AutoShot.h"


DEFAULT_HACK_CONSTRUCTOR(AutoShot)

void AutoShot::onDrawGUI()
{
	ImGui::Checkbox("Auto Shot", &m_bEnabled);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, g::keyButtonSplitter);
}
bool AutoShot::onWndProc(WPARAM wParam, UINT msg)
{
	if (msg != WM_KEYDOWN && msg != WM_LBUTTONDOWN && msg != WM_SYSKEYDOWN)
		return true;
	if (activationKey != 0 && wParam == activationKey)
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
	data["ActivationKey"] = activationKey;
	data[m_sHackName] = m_bEnabled;

}
void AutoShot::read(nlohmann::json& data)
{
	m_bEnabled = data[m_sHackName].get<bool>();
	activationKey = data["ActivationKey"].get<int>();
}