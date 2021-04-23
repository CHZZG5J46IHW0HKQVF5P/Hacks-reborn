#pragma once

#include "Hack.h"

class BMXspeedhack : public IHack
{
public:
	BMXspeedhack(const char* name)
	{
		hackName = name;
	}
private:
	int activationKey = 0;
	bool bmxspeedHack = false;
	void drawGUI()	  override
	{
		ImGui::Checkbox(hackName.c_str(), &isEnable);
		ImGui::SameLine();
		Lippets::ImGuiSnippets::KeyButton(activationKey, g::keyBtnSplitter);
	}
	void wndProcHook(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info) override
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
	void everyTickAction(const crTickLocalPlayerInfo& info) override
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
