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

bool BMXspeedhack::onWndProc(WPARAM wParam, UINT msg)
{
	if (activationKey != 0 && wParam == activationKey)
		if (msg == WM_KEYDOWN || msg == WM_LBUTTONDOWN || msg == WM_SYSKEYDOWN)
		{
			bmxspeedHack = true;
		}
		else if (msg == WM_KEYUP || msg == WM_LBUTTONUP || msg == WM_SYSKEYUP)
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
	data["ActivationKey"] = activationKey;
	data[m_sHackName] = m_bEnabled;

}
void BMXspeedhack::read(nlohmann::json& data)
{
	m_bEnabled = data[m_sHackName].get<bool>();
	activationKey = data["ActivationKey"].get<int>();
}