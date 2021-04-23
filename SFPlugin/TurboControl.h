#pragma once
#include "Hack.h"

void DisableTwinTurbo(bool bDisable)
{
	static const char16_t temp1 = 40169;//*(char16_t*)dwFUNC_SetVehVelocity;
	if (bDisable)
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x15030), 2, 50064); // -
	else
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x15030), 2, temp1); // +
}

class TurboControl : public IHack
{
public:
	TurboControl(const char* name)
	{
		hackName = name;
	}
private:
	int activationKey = 0;
	void drawGUI() override
	{
		ImGui::Checkbox(hackName.c_str(), &isEnable);
		ImGui::SameLine();
		Lippets::ImGuiSnippets::KeyButton(activationKey,g::keyBtnSplitter);
			
	}
	void wndProcHook(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info) override
	{
		if (activationKey != 0 && wParam == activationKey)
			if (info.isDriver)
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
	void save(Json::Value& data) override
	{
		data[hackName] = isEnable;
		data["ActivationKey"] = activationKey;

	}
	void read(Json::Value& data) override
	{
		isEnable = data[hackName].asBool();
		activationKey = data["ActivationKey"].asInt();
	}
};

