#include "SpeedControl.h"


SpeedControl::SpeedControl(const char* name)
{
	hackName = name;
}

void SpeedControl::onDrawGUI()	  
{
	if (ImGui::Checkbox(hackName.c_str(), &isEnable))
		this->switchHack();
}
void SpeedControl::save(Json::Value& data) 
{
	data[hackName] = isEnable;
	data["bOnlyIFOnGround"] = bOnlyIFOnGround;
	data["bSpeedUpOnlyIFGasPedal"] = bSpeedUpOnlyIFGasPedal;
	data["bSlowDownOnlyIFBreakPedal"] = bSlowDownOnlyIFBreakPedal;
	data["bNoSlowDown"] = bNoSlowDown;
}
void SpeedControl::read(Json::Value& data)   
{
	isEnable = data[hackName].asBool();
	bOnlyIFOnGround = data["bOnlyIFOnGround"].asBool();
	bSpeedUpOnlyIFGasPedal = data["bSpeedUpOnlyIFGasPedal"].asBool();
	bSlowDownOnlyIFBreakPedal = data["bSlowDownOnlyIFBreakPedal"].asBool();
	bNoSlowDown = data["bNoSlowDown"].asBool();
}
bool SpeedControl::onRPCIncoming(stRakNetHookParams* params, const crTickLocalPlayerInfo& info) 
{
	if (params->packetId != 91 && !info.isDriver)
		return true;
	auto vehType = Vehicles::getVehicleType(Vehicles::getVehicleCVehicle(Vehicles::getVehicleInfo(VEHICLE_SELF)));
	if (vehType == Vehicles::eVehicleType::CAutomobile || vehType == Vehicles::eVehicleType::CBike)
	{
		if (bOnlyIFOnGround)
		{
			if (vehType == Vehicles::eVehicleType::CBike)
			{
				if (Vehicles::isVehicleInAir(3.f, VEHICLE_SELF))
					return false;
			}
			else
			{
				if (Vehicles::isVehicleInAir(3.f, VEHICLE_SELF))
					return false;
			}
		}
	}
	else
		return false;
	CVector currentSpeed;
	PEDSELF->GetVehicle()->GetMoveSpeed(&currentSpeed);
	CVector newSpeed;
	params->bitStream->SetReadOffset(8);
	params->bitStream->Read(newSpeed.fX);
	params->bitStream->Read(newSpeed.fY);
	params->bitStream->Read(newSpeed.fZ);
	params->bitStream->ResetReadPointer();
	float gasPedal = PEDSELF->GetVehicle()->GetGasPedal();
	if ((currentSpeed.Length() < newSpeed.Length())) // boosting
	{
		if (bSpeedUpOnlyIFGasPedal)
			if (gasPedal > 0.f)
				return true;
	}
	else // замедляемся
	{
		if (bNoSlowDown)
			return false;
		if (bSlowDownOnlyIFBreakPedal)
			if (gasPedal <= 0.f)
				return true;
	}
	return true;
}
void SpeedControl::onDrawSettings()	
{
	if (ImGui::BeginMenu("Speed Controller Settings"))
	{
		ImGui::Checkbox("Accept All Speed Changes If Not On Ground", &bOnlyIFOnGround);
		ImGui::Checkbox("No Slow Down", &bNoSlowDown);
		if (!bNoSlowDown)
			ImGui::Checkbox("Slow Down Only If Break Pedal Pressed", &bSlowDownOnlyIFBreakPedal);

		ImGui::Checkbox("Boost Only If Gas Pedal Pressed", &bSpeedUpOnlyIFGasPedal);
		ImGui::EndMenu();
	}
}