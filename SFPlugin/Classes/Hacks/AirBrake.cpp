#include "AirBrake.h"


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



AirBrake::AirBrake(const char* name)
{
	hackName = name;
}

void AirBrake::onDrawGUI()
{
	ImGui::Checkbox(hackName.c_str(), &isEnable);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, 0);
}
void AirBrake::onWndProc(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info) 
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
void AirBrake::onDrawSettings() 
{
	if (ImGui::BeginMenu("Air Brake"))
	{
		ImGui::SliderFloat("Force", &fAirBrakeForce, 0.0f, 3.0f);

		ImGui::EndMenu();
	}
}
void AirBrake::save(Json::Value& data) 
{
	data[hackName] = isEnable;
	data["activationKey"] = activationKey;
	data["fAirBrakeForce"] = fAirBrakeForce;
}
void AirBrake::read(Json::Value& data)
{
	isEnable = data[hackName].asBool();
	activationKey = data["activationKey"].asInt();
	fAirBrakeForce = data["fAirBrakeForce"].asFloat();
	if (fAirBrakeForce == 0.f)
		fAirBrakeForce = 1.f;
}