#include "AirBrake.h"


DEFAULT_HACK_CONSTRUCTOR(AirBrake)

void AirBrakeForward(float force)
{
	float angle = *(float*)0xB6F258;
	PEDSELF->SetTargetRotation(angle + 1.57f);
	float heading = PEDSELF->GetTargetRotation();
	CVector pos;
	if (g::pInfo->isDriver())
		pos = *PEDSELF->GetVehicle()->GetPosition();
	else
		pos = *PEDSELF->GetPosition();
	CVector slappos;
	slappos.fX = slappos.fX + force * sin(-heading);
	slappos.fY = slappos.fY + force * cos(-heading);
	pos += slappos;
	if (g::pInfo->isDriver())
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

void TPupdown(float force, bool bUp)
{

	CVector pos;
	if (g::pInfo->isDriver())
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


void AirBrake::onDrawGUI()
{
	ImGui::Checkbox(m_sHackName.c_str(), &m_bEnabled);
	if (ImGui::BeginPopupContextItem())
	{
		ImGui::SliderFloat("Force", &fAirBrakeForce, 0.0f, 3.0f);
		ImGui::EndPopup();
	}
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, g::keyButtonSplitter);
}
bool AirBrake::onWndProc()
{
	if (!g::pKeyEventInfo->bDown)
		return true;
	if (activationKey != 0 && g::pKeyEventInfo->iKeyID == activationKey)
	{

		isAirBrakeShouldWork = !isAirBrakeShouldWork;//true;
		notify("Air Brake", isAirBrakeShouldWork);
	}
	if (isAirBrakeShouldWork)
	{
		switch (g::pKeyEventInfo->iKeyID)
		{
		case 87: AirBrakeForward(fAirBrakeForce); break;
		case 32: TPupdown(fAirBrakeForce, true); break;
		case 16: TPupdown(fAirBrakeForce, false); break;
		default:
			break;
		}
	}
	return true;

}

void AirBrake::save(nlohmann::json& data)
{

	SERIALIZE_FIELD_JSON(m_bEnabled);
	SERIALIZE_FIELD_JSON(activationKey);
	SERIALIZE_FIELD_JSON(fAirBrakeForce);
}
void AirBrake::read(nlohmann::json& data)
{

	DESERIALIZE_FIELD_JSON(m_bEnabled);
	DESERIALIZE_FIELD_JSON(activationKey);
	DESERIALIZE_FIELD_JSON(fAirBrakeForce);

	ASSIGN_VAR_VALUE_IF_EQUALS_ZEROF(fAirBrakeForce, 3.f);
}