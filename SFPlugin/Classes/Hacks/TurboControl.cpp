#include "TurboControl.h"

void DisableTwinTurbo(bool bDisable)
{
	static const char16_t temp1 = 40169;//*(char16_t*)dwFUNC_SetVehVelocity;
	if (bDisable)
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x15030), 2, 50064); // -
	else
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x15030), 2, temp1); // +
}


TurboControl::TurboControl(const char* name)
{
	m_dwProperties |= (HackProperties::PROCKEYS);
	m_sHackName = name;
}
void TurboControl::onDrawGUI() 
{
	ImGui::Checkbox(m_sHackName.c_str(), &m_bEnabled);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, g::keyButtonSplitter);

}
void TurboControl::onWndProc(WPARAM wParam, UINT msg,  crTickLocalPlayerInfo* info) 
{
	if (activationKey != 0 && wParam == activationKey)
		if (info->isDriver)
			switch (Stuff::getKeyStateByMsg(msg))
			{
			case eKeyState::PRESSED:
			{
				DisableTwinTurbo(false);
				Stuff::AddMessageJumpQ("~r~Turbo", 500, 0, 0);
				break;
			}
			case eKeyState::RELEASED:
			{

				DisableTwinTurbo(true);
				Stuff::AddMessageJumpQ("~r~Comfort", 500, 0, 0);
				break;
			}
			}

}
void TurboControl::save(nlohmann::json& data) 
{
	data[m_sHackName] = m_bEnabled;
	data["ActivationKey"] = activationKey;

}
void TurboControl::read(nlohmann::json& data) 
{
	m_bEnabled = data[m_sHackName].get<bool>();
	activationKey = data["ActivationKey"].get<int>();
}