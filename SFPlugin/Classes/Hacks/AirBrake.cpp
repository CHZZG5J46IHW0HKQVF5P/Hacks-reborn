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

void TPupdown(float force, bool isExist, bool isDriver, bool bUp)
{
	if (isExist)
	{
		CVector pos;
		if (isDriver)
		{
			pos = *PEDSELF->GetVehicle()->GetPosition();
			if (bUp)
				pos.fZ += force;
			else
				pos.fZ -= force;
			PEDSELF->GetVehicle()->SetMoveSpeed(&CVector(0.f, 0.f, 0.f));
			PEDSELF->GetVehicle()->SetPosition(&pos);
		}
		else
		{
			pos = *PEDSELF->GetPosition();
			if (bUp)
				pos.fZ += force;
			else
				pos.fZ -= force;
			PEDSELF->SetMoveSpeed(&CVector(0.f, 0.f, 0.f));
			PEDSELF->SetPosition(&pos);
		}
	}
}

AirBrake::AirBrake(const char* name)
{
	m_sHackName = name;
}

void AirBrake::onDrawGUI()
{
	ImGui::Checkbox(m_sHackName.c_str(), &m_bEnabled);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, g::keyButtonSplitter);
}
void AirBrake::onWndProc(WPARAM wParam, UINT msg)
{
	if (msg != WM_KEYDOWN && msg != WM_LBUTTONDOWN && msg != WM_SYSKEYDOWN)
		return;
	if (activationKey != 0 && wParam == activationKey)
	{

		isAirBrakeShouldWork = !isAirBrakeShouldWork;//true;
		notify("Air Brake", isAirBrakeShouldWork);
	}
	if (isAirBrakeShouldWork)
	{
		switch (wParam)
		{
		case 87: AirBrakeForward(fAirBrakeForce, g::pInfo->isExist, g::pInfo->isDriver); break;
		case 32: TPupdown(fAirBrakeForce, g::pInfo->isExist, g::pInfo->isDriver,true); break;
		case 16: TPupdown(fAirBrakeForce, g::pInfo->isExist, g::pInfo->isDriver,false); break;
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
void AirBrake::save(nlohmann::json& data)
{
	data[m_sHackName] = m_bEnabled;
	data["activationKey"] = activationKey;
	data["fAirBrakeForce"] = fAirBrakeForce;
}
void AirBrake::read(nlohmann::json& data)
{
	m_bEnabled = data[m_sHackName].get<bool>();
	activationKey = data["activationKey"].get<int>();
	fAirBrakeForce = data["fAirBrakeForce"].get<float>();
	if (fAirBrakeForce == 0.f)
		fAirBrakeForce = 1.f;
}