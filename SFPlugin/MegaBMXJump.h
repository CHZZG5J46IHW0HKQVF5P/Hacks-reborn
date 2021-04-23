#pragma once
#include "Hack.h"

class MegaBMXJump : public IHack
{
public:
	MegaBMXJump(const char* name)
	{
		hackName = name;
	}
private:
	float fBMXJumpSpeed;
	void drawGUI()	  override
	{
		ImGui::Checkbox(hackName.c_str(), &isEnable);
	}
	void everyTickAction(const crTickLocalPlayerInfo& info) override
	{
		if (!info.isDriver || info.vehType != Vehicles::eVehicleType::CBMX)
			return;
		static bool bWasInAir = false;
		bool isInAir = Vehicles::isVehicleInAir(globalPresets->fVehHightLimit, VEHICLE_SELF);
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
	void save(Json::Value& data) override
	{
		data[hackName] = isEnable;
		data["fBMXJumpSpeed"] = fBMXJumpSpeed;
	}
	void read(Json::Value& data)   override
	{
		isEnable = data[hackName].asBool();
		fBMXJumpSpeed = data["fBMXJumpSpeed"].asFloat();
	}

};


