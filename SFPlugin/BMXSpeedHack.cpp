#include "BMXSpeedHack.h"


BMXspeedhack::BMXspeedhack(const char* name)
{
	hackName = name;
}

void BMXspeedhack::onDrawGUI()
{
	ImGui::Checkbox(hackName.c_str(), &isEnable);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, 0);
}
void BMXspeedhack::onWndProc(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info)
{
	if (msg == WM_KEYDOWN || msg == WM_LBUTTONDOWN || msg == WM_SYSKEYDOWN)
	{
		bmxspeedHack = true;
	}
	else if (msg == WM_KEYUP || msg == WM_LBUTTONUP || msg == WM_SYSKEYUP)
	{
		bmxspeedHack = false;
	}

}
void BMXspeedhack::everyTickAction(const crTickLocalPlayerInfo& info)
{
	if (!info.isDriver || info.vehType != Vehicles::eVehicleType::CBMX)
		return;

	static uint8 BMXState = 1;
	static DWORD dwBMXTime = 0;
	if (GetTickCount() > dwBMXTime)
	{
		if (BMXState == 1)
		{
			dwBMXTime = GetTickCount() + 20;
			BMXState = 2;
			SF->getGame()->emulateGTAKey(16, 128);
		}
		else if (BMXState == 2)
		{
			dwBMXTime = GetTickCount() + 20;
			BMXState = 1;
			SF->getGame()->emulateGTAKey(16, 255);
		}
	}

}
void BMXspeedhack::save(Json::Value& data)
{
	data["ActivationKey"] = activationKey;
	data[hackName] = isEnable;

}
void BMXspeedhack::read(Json::Value& data)
{
	isEnable = data[hackName].asBool();
	activationKey = data["ActivationKey"].asInt();
}