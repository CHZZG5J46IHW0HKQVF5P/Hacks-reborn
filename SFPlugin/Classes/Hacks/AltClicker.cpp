#include "AltClicker.h"

AltClicker::AltClicker(const char* name)
{
	m_sHackName = name;
}

void AltClicker::onDrawGUI()
{
	ImGui::Checkbox(m_sHackName.c_str(), &m_bEnabled);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, g::keyButtonSplitter);
}

void AltClicker::read(nlohmann::json& data)
{
	m_bEnabled = data[m_sHackName].get<bool>();
	iDelay = data["iDelay"].get<int>();
	activationKey = data["activationKey"].get<int>();
	if (iDelay == 0)
		iDelay = 25;
}

void AltClicker::save(nlohmann::json& data)
{
	data[m_sHackName] = m_bEnabled;
	data["activationKey"] = activationKey;
	data["iDelay"] = iDelay;
}

void AltClicker::onDrawSettings()
{
	if (ImGui::BeginMenu("Alt Clicker"))
	{
		ImGui::SliderInt("Click Delay", &iDelay, 1, 300);
		ImGui::EndMenu();
	}
}


void AltClicker::onWndProc(WPARAM wParam, UINT msg,  crTickLocalPlayerInfo* info)
{
	if (msg != WM_KEYDOWN && msg != WM_LBUTTONDOWN && msg != WM_SYSKEYDOWN)
		return;

	if (activationKey != 0 && wParam == activationKey)
	{
		bWorking = !bWorking;
		notify("ALT Clicker", bWorking);
	}
}

void AltClicker::everyTickAction( crTickLocalPlayerInfo* info)
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