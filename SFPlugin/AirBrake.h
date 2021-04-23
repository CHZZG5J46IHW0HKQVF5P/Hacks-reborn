#pragma once
#include "Hack.h"

void AirBrakeForward(float force, bool isExist, bool isDriver)
{
	if (isExist)
	{
		float angle = *(float*)0xB6F258;
		PEDSELF->SetTargetRotation(angle + 1.57f);
		float heading = PEDSELF->GetTargetRotation();
		CVector pos;
		if (isDriver)
			pos = *PEDSELF->GetVehicle()->GetPosition();
		else
			pos = *PEDSELF->GetPosition();
		CVector slappos;
		slappos.fX = slappos.fX + force * sin(-heading);
		slappos.fY = slappos.fY + force * cos(-heading);
		pos += slappos;
		if (isDriver)
		{
			PEDSELF->GetVehicle()->SetMoveSpeed(&CVector(0.f, 0.f, 0.f));
			PEDSELF->GetVehicle()->SetPosition(&pos);
		}
		else
		{
			PEDSELF->SetMoveSpeed(&CVector(0.f, 0.f, 0.f));
			PEDSELF->SetPosition(&pos);
		}
	}
}

void TPup(float force, bool isExist, bool isDriver)
{
	if (isExist)
	{
		CVector pos;
		if (isDriver)
		{
			pos = *PEDSELF->GetVehicle()->GetPosition();
			pos.fZ += force;
			PEDSELF->GetVehicle()->SetMoveSpeed(&CVector(0.f, 0.f, 0.f));
			PEDSELF->GetVehicle()->SetPosition(&pos);
		}
		else
		{
			pos = *PEDSELF->GetPosition();
			pos.fZ += force;
			PEDSELF->SetMoveSpeed(&CVector(0.f, 0.f, 0.f));
			PEDSELF->SetPosition(&pos);
		}
	}
}


void TPdown(float force, bool isExist, bool isDriver)
{
	if (isExist)
	{
		CVector pos;
		if (isDriver)
		{
			pos = *PEDSELF->GetVehicle()->GetPosition();
			pos.fZ -= force;
			PEDSELF->GetVehicle()->SetMoveSpeed(&CVector(0.f, 0.f, 0.f));
			PEDSELF->GetVehicle()->SetPosition(&pos);
		}
		else
		{
			pos = *PEDSELF->GetPosition();
			pos.fZ -= force;
			PEDSELF->SetMoveSpeed(&CVector(0.f, 0.f, 0.f));
			PEDSELF->SetPosition(&pos);
		}
	}
}


class AirBrake : public IHack
{
public:
	AirBrake(const char* name)
	{
		hackName = name;
	}
private:
	bool isAirBrakeShouldWork = false;
	int activationKey = 0;
	float fAirBrakeForce = 0.f;
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

			isAirBrakeShouldWork ^= true;
			notify("Air Brake", isAirBrakeShouldWork);
		}
		if (isAirBrakeShouldWork)
		{
			switch (wParam)
			{
			case 87: AirBrakeForward(fAirBrakeForce, info.isExist, info.isDriver); break;
			case 32: TPup(fAirBrakeForce, info.isExist, info.isDriver); break;
			case 16: TPdown(fAirBrakeForce, info.isExist, info.isDriver); break;
			default:
				break;
			}
		}


	}
	void drawSettings() override
	{
		if (ImGui::BeginMenu("Air Brake"))
		{
			ImGui::SliderFloat("Force", &fAirBrakeForce, 0.0f, 3.0f);

			ImGui::EndMenu();
		}
	}
	void save(Json::Value& data) override
	{
		data[hackName] = isEnable;
		data["activationKey"] = activationKey;
		data["fAirBrakeForce"] = fAirBrakeForce;
	}
	void read(Json::Value& data)   override
	{
		isEnable = data[hackName].asBool();
		activationKey = data["activationKey"].asInt();
		fAirBrakeForce = data["fAirBrakeForce"].asFloat();
		if (fAirBrakeForce == 0.f)
			fAirBrakeForce = 1.f;
	}

};

