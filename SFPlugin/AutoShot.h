#pragma once
#include "Hack.h"

class AutoShot : public IHack
{
public:
	AutoShot(const char* name)
	{
		hackName = name;
	}
private:
	bool autoShot = false;
	int activationKey = 0;
	void drawGUI()	  override
	{
		ImGui::Checkbox(hackName.c_str(), &isEnable);
		ImGui::SameLine();
		Lippets::ImGuiSnippets::KeyButton(activationKey, g::keyBtnSplitter);
	}
	void wndProcHook(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info) override
	{
		if (msg != WM_KEYDOWN && msg != WM_LBUTTONDOWN && msg != WM_SYSKEYDOWN)
			return;
		if (activationKey != 0 && wParam == activationKey)
		{
			autoShot ^= true;
			notify("Auto Shot", autoShot);
		}
	}
	void everyTickAction(const crTickLocalPlayerInfo& info) override
	{
		if (!info.isExist || !autoShot || info.isInCar)
			return;
		DWORD targetPedAddr = *(DWORD*)PEDSELF->GetMemoryValue(0x79C);
		if (targetPedAddr)
			SF->getGame()->emulateGTAKey(17,255);
	}
	void save(Json::Value& data) override
	{
		data["ActivationKey"] = activationKey;
		data[hackName] = isEnable;

	}
	void read(Json::Value& data)   override
	{
		isEnable = data[hackName].asBool();
		activationKey = data["ActivationKey"].asInt();
	}
};
