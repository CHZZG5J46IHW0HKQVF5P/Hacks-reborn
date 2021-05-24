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
	m_bEnabled = data[m_sHackName].get<bool>();
	iDelay = data["iDelay"].get<int>();
	activationKey = data["activationKey"].get<int>();
	ASSIGN_VAR_VALUE_IF_EQUALS_ZERO(iDelay,25);
}

void AltClicker::save(nlohmann::json& data)
{
	data[m_sHackName] = m_bEnabled;
	data["activationKey"] = activationKey;
	data["iDelay"] = iDelay;
}




bool AltClicker::onWndProc(WPARAM wParam, UINT msg)
{
	if (msg != WM_KEYDOWN && msg != WM_LBUTTONDOWN && msg != WM_SYSKEYDOWN)
		return true;

	if (activationKey != 0 && wParam == activationKey)
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