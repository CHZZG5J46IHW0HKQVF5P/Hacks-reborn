#include "AltClicker.h"

AltClicker::AltClicker(const char* name)
{
	hackName = name;
}

void AltClicker::onDrawGUI()
{
	ImGui::Checkbox(hackName.c_str(), &isEnable);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, 0);
}

void AltClicker::read(Json::Value& data)
{
	isEnable = data[hackName].asBool();
	iDelay = data["iDelay"].asInt();
	activationKey = data["activationKey"].asInt();
	if (iDelay == 0)
		iDelay = 25;
}

void AltClicker::save(Json::Value& data)
{
	data[hackName] = isEnable;
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


void AltClicker::onWndProc(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info)
{
	if (msg != WM_KEYDOWN && msg != WM_LBUTTONDOWN && msg != WM_SYSKEYDOWN)
		return;

	if (activationKey != 0 && wParam == activationKey)
	{
		bWorking ^= true;
		notify("ALT Clicker", bWorking);
	}
}

void AltClicker::everyTickAction(const crTickLocalPlayerInfo& info)
{
	static DWORD dwALTtime = 0;
	static uint8 eALTstate = 1;
	if (bWorking)
		if (dwALTtime < GetTickCount())
		{
			if (eALTstate == 1)
			{
				dwALTtime = GetTickCount() + 1;
				eALTstate = 2;
				SF->getGame()->emulateGTAKey(21, 255);
			}
			else if (eALTstate == 2)
			{
				dwALTtime = GetTickCount() + iDelay;
				eALTstate = 1;
				SF->getGame()->emulateGTAKey(21, 0);
			}
		}

}