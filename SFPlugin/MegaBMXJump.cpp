#include "MegaBMXJump.h"


MegaBMXJump::MegaBMXJump(const char* name)
{
	hackName = name;
}
void MegaBMXJump::onDrawGUI()	  
{
	ImGui::Checkbox(hackName.c_str(), &isEnable);
}
void MegaBMXJump::everyTickAction(const crTickLocalPlayerInfo& info) 
{
	if (!info.isDriver || info.vehType != Vehicles::eVehicleType::CBMX)
		return;
	static bool bWasInAir = false;
	bool isInAir = Vehicles::isVehicleInAir(3.f, VEHICLE_SELF);
	if (!bWasInAir && isInAir)
	{
		CVector vecMoveSpeed;
		PEDSELF->GetVehicle()->GetMoveSpeed(&vecMoveSpeed);
		vecMoveSpeed.fZ = fBMXJumpSpeed;
		PEDSELF->GetVehicle()->SetMoveSpeed(&vecMoveSpeed);
		bWasInAir = true;
	}
	else
		if (bWasInAir && !isInAir)
			bWasInAir = false;

}
void MegaBMXJump::save(Json::Value& data) 
{
	data[hackName] = isEnable;
	data["fBMXJumpSpeed"] = fBMXJumpSpeed;
}
void MegaBMXJump::read(Json::Value& data)   
{
	isEnable = data[hackName].asBool();
	fBMXJumpSpeed = data["fBMXJumpSpeed"].asFloat();
}