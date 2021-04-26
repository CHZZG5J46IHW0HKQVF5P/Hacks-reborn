#include "AutoShot.h"


AutoShot::AutoShot(const char* name)
{
	hackName = name;
}

void AutoShot::onDrawGUI()
{
	ImGui::Checkbox(hackName.c_str(), &isEnable);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, 0);
}
void AutoShot::onWndProc(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info)
{
	if (msg != WM_KEYDOWN && msg != WM_LBUTTONDOWN && msg != WM_SYSKEYDOWN)
		return;
	if (activationKey != 0 && wParam == activationKey)
	{
		autoShot ^= true;
		notify("Auto Shot", autoShot);
	}
}
void AutoShot::everyTickAction(const crTickLocalPlayerInfo& info)
{
	if (!info.isExist || !autoShot || info.isInCar)
		return;
	DWORD targetPedAddr = *(DWORD*)PEDSELF->GetMemoryValue(0x79C);
	if (targetPedAddr)
		SF->getGame()->emulateGTAKey(17, 255);
}
void AutoShot::save(Json::Value& data)
{
	data["ActivationKey"] = activationKey;
	data[hackName] = isEnable;

}
void AutoShot::read(Json::Value& data)
{
	isEnable = data[hackName].asBool();
	activationKey = data["ActivationKey"].asInt();
}