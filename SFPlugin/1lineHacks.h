#pragma once
#include "Hack.h" 

void EnableNoAnims(bool bEnable)
{
	static const char16_t temp = 35669;//*(char16_t*)dwFUNC_DANIM;
	if (bEnable)
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x16FA0), 2, 50064);
	else
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x16FA0), 2, temp);
};

void EnableNoFreeze(bool bEnable)
{
	static const char16_t temp = 18921;//*(char16_t*)dwFUNC_Freez;
	if (bEnable)
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x168E0), 2, 50064);
	else
		WriteMem<char16_t>((SF->getSAMP()->getSAMPAddr() + 0x168E0), 2, temp);
}

void EnableAntiStun(bool bEnable)
{
	if (bEnable)
		*(uint8_t*)(*(uint32_t*)(0x00B6F5F0) + 0x478) = 0x04;
	else
		*(uint8_t*)(*(uint32_t*)(0x00B6F5F0) + 0x478) = 0x00;
}

void EnableDriveOrWalkUnderWater(bool bEnable)
{
	*(byte*)0x6C2759 = bEnable;
}

void EnableFireProtection(bool bEnable)
{
	WriteMem<byte>(0xB7CEE6, 1U, bEnable);
}

void EnableFastCrosshair(bool bEnable)
{
	static const byte temp = 116;//*(byte*)0x0058E1D9;`
	if (bEnable)
		WriteMem<byte>(0x0058E1D9, 1, 235);
	else
		WriteMem<byte>(0x0058E1D9, 1, temp);
}

void EnableInfOxygenAndStamina(bool bEnable)
{
	WriteMem<byte>(0x96916E, 1U, bEnable);
	WriteMem<byte>(0xB7CEE4, 1U, bEnable);
}

void EnableMegaJump(bool bEnable)
{
	WriteMem<byte>(0x96916C, 1, bEnable);
}

void EnableNoSpread(bool bEnable)
{
	*reinterpret_cast<float*>(0x008D6114) = (!bEnable * 100.f) / 20.f;
}

void EnableNoCamRestore(bool bEnable)
{
	static const byte temp1 = 122;//*(byte*)0x5109AC;
	static const byte temp2 = 122;// *(byte*)0x5109C5;
	static const byte temp3 = 117;// *(byte*)0x5231A6;
	static const byte temp4 = 117;// *(byte*)0x52322D;
	static const byte temp5 = 117;// *(byte*)0x5233BA;
	if (bEnable)
	{
		WriteMem<byte>(0x5109AC, 1, 235);
		WriteMem<byte>(0x5109C5, 1, 235);
		WriteMem<byte>(0x5231A6, 1, 235);
		WriteMem<byte>(0x52322D, 1, 235);
		WriteMem<byte>(0x5233BA, 1, 235);
	}
	else
	{
		WriteMem<byte>(0x5109AC, 1, temp1);
		WriteMem<byte>(0x5109C5, 1, temp2);
		WriteMem<byte>(0x5231A6, 1, temp3);
		WriteMem<byte>(0x52322D, 1, temp4);
		WriteMem<byte>(0x5233BA, 1, temp5);
	}

}

void EnableWallShot(bool bEnable)
{

	if (bEnable) {
		WriteMem(0x00740701, false, true);
		WriteMem(0x00740703, false, true);
		WriteMem(0x00740709, false, true);

		WriteMem(0x00740B49, false, true);
		WriteMem(0x00740B4B, false, true);
		WriteMem(0x00740B51, false, true);

		WriteMem(0x0073620D, false, true);
		WriteMem(0x0073620F, false, true);
		WriteMem(0x00736215, false, true);
	}
	else {
		WriteMem(0x00740701, true, true);
		WriteMem(0x00740703, true, true);
		WriteMem(0x00740709, true, true);

		WriteMem(0x00740B49, true, true);
		WriteMem(0x00740B4B, true, true);
		WriteMem(0x00740B51, true, true);

		WriteMem(0x0073620D, true, true);
		WriteMem(0x0073620F, true, true);
		WriteMem(0x00736215, true, true);
	}

}

void EnableNoFallDamage(bool bEnable)
{
	if (bEnable)
		SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTAEntity->flags = (0 | 0 | 64 | 0);
	else
		SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTAEntity->flags = (0 | 0 | 0 | 0);
}

void EnableWaterDrive(bool bEnable)
{
	WriteMem<UINT>(0x969152, 4, bEnable);
}

void EnableNewDL(bool bEnable)
{
	if (bEnable)
	{
		DWORD NewProtection;
		VirtualProtect((DWORD*)(SF->getSAMP()->getSAMPAddr() + 0xD83A8), 0x87, PAGE_EXECUTE_READWRITE, &NewProtection);
		memcpy((DWORD*)(SF->getSAMP()->getSAMPAddr() + 0xD83A8), "[id: %d, type: %d subtype: %d Health: %.1f]", 0x87);
		VirtualProtect((DWORD*)(SF->getSAMP()->getSAMPAddr() + 0xD83A8), 0x87, NewProtection, &NewProtection);

	}
	else
	{
		DWORD NewProtection;
		VirtualProtect((DWORD*)(SF->getSAMP()->getSAMPAddr() + 0xD83A8), 0x87, PAGE_EXECUTE_READWRITE, &NewProtection);
		memcpy((DWORD*)(SF->getSAMP()->getSAMPAddr() + 0xD83A8), "[id: %d, type: %d subtype: %d Health: %.1f preloaded: %u]\nDistance: %.2fm\nPassengerSeats: %u\ncPos: %.3f,%.3f,%.3f\nsPos: %.3f,%.3f,%.3f", 0x87);
		VirtualProtect((DWORD*)(SF->getSAMP()->getSAMPAddr() + 0xD83A8), 0x87, NewProtection, &NewProtection);
	}
}

void EnableWaterProofEng(bool bEnable)
{
	static const byte temp = 122;//*(byte*)0x6A90C5;
	if (bEnable)
		WriteMem<byte>(0x6A90C5, 1, 235);
	else
		WriteMem<byte>(0x6A90C5, 1, temp);
}

void Enable160HPbar(bool bEnable)
{
	static const float temp1 = 569.0f;//*(float*)12030944;
	if (bEnable)
		*(float*)12030944 = 930.f;
	else
		*(float*)12030944 = temp1;
}

class OneLineHacks : public IHack
{
public:
	OneLineHacks(const char* name)
	{
		hackName = name;
		isEnable = true;
	}
private:
	bool noReload = false;
	bool antiStun = false;
	bool driveWalkUnderWater = false;
	bool fireProtection = false;
	bool fastCrosshair = false;
	bool infOxygenAndStamina = false;
	bool megaJump = false;
	bool noSpread = false;
	bool noFreeze = false;
	bool noAnims = false;
	bool noCamrestore = false;
	bool noFall = false;
	bool surfOnVehicles = false;
	bool wallShot = false;
	bool pressNitro = false;
	bool noFallDamage = false;
	bool noBike = false;
	bool waterDrive = false;
	bool autoBike = false;
	bool newDl = false;
	bool waterProofEngine = false;
	bool bar160hp = false;
	void drawGUI()	  override
	{
		if (ImGui::Checkbox("Anti Stun", &antiStun))
			EnableAntiStun(antiStun);
		if (ImGui::Checkbox("Drive Walk UnderWater", &driveWalkUnderWater))
			EnableDriveOrWalkUnderWater(driveWalkUnderWater);
		if (ImGui::Checkbox("Fire Protection", &fireProtection))
			EnableFireProtection(fireProtection);
		if (ImGui::Checkbox("Fast Crosshair", &fastCrosshair))
			EnableFastCrosshair(fastCrosshair);
		if (ImGui::Checkbox("Infinity Oxygen | Stamina", &infOxygenAndStamina))
			EnableInfOxygenAndStamina(infOxygenAndStamina);
		if (ImGui::Checkbox("Mega Jump", &megaJump))
			EnableMegaJump(megaJump);
		if (ImGui::Checkbox("No Spread", &noSpread))
			EnableNoSpread(noSpread);
		if (ImGui::Checkbox("No Freeze", &noFreeze))
			EnableNoFreeze(noFreeze);
		if (ImGui::Checkbox("No Anims", &noAnims))
			EnableNoAnims(noAnims);
		if (ImGui::Checkbox("No Cam Restore", &noCamrestore))
			EnableNoCamRestore(noCamrestore);
		ImGui::Checkbox("No Fall", &noFall);
		ImGui::Checkbox("Surf On Vehicles", &surfOnVehicles);
		if (ImGui::Checkbox("Wall Shot", &wallShot))
			EnableWallShot(wallShot);
		ImGui::Checkbox("Press Nitro", &pressNitro);
		if (ImGui::Checkbox("No Fall Damage", &noFallDamage))
			EnableNoFallDamage(noFallDamage);
		ImGui::Checkbox("No Bike", &noBike);
		if (ImGui::Checkbox("Water Drive", &waterDrive))
			EnableWaterDrive(waterDrive);
		if (ImGui::Checkbox("New DL", &newDl))
			EnableNewDL(newDl);
		if (ImGui::Checkbox("Water Proof Engine", &waterProofEngine))
			EnableWaterProofEng(waterProofEngine);
		if (ImGui::Checkbox("160 HP bar", &bar160hp))
			Enable160HPbar(bar160hp);
		ImGui::Checkbox("No Reload", &noReload);
		ImGui::Checkbox("Auto Bike", &autoBike);
	}
	void switchHack()
	{
		EnableAntiStun(antiStun);
		EnableDriveOrWalkUnderWater(driveWalkUnderWater);
		EnableFireProtection(fireProtection);
		EnableFastCrosshair(fastCrosshair);
		EnableInfOxygenAndStamina(infOxygenAndStamina);
		EnableMegaJump(megaJump);
		EnableNoSpread(noSpread);
		EnableNoFreeze(noFreeze);
		EnableNoAnims(noAnims);
		EnableNoCamRestore(noCamrestore);
		EnableWallShot(wallShot);
		EnableNoFallDamage(noFallDamage);
		EnableWaterDrive(waterDrive);
		EnableNewDL(newDl);
		EnableWaterProofEng(waterProofEngine);
		Enable160HPbar(bar160hp);
	}
	void everyTickAction(const crTickLocalPlayerInfo& info) override
	{
		if (info.isDriver)
		{
			if (noBike)
			{
				if (Vehicles::getVehicleType(Vehicles::getVehicleCVehicle(Vehicles::getVehicleInfo(VEHICLE_SELF, false))) != Vehicles::eVehicleType::CBike)
					return;
				if (PEDSELF->GetVehicle()->IsDrowning())
				{
					if (PEDSELF->GetCantBeKnockedOffBike() == 1)
						PEDSELF->SetCantBeKnockedOffBike(0);
				}
				else
					if (PEDSELF->GetCantBeKnockedOffBike() == 0)
						PEDSELF->SetCantBeKnockedOffBike(1);
			}
			if (autoBike)
			{
				static uint8 eBikeState = 1;
				static DWORD dwBikeTime = 0;
				if (PEDSELF->GetVehicle()->GetGasPedal() == 1.f && !SF->getSAMP()->getInput()->iInputEnabled && !Vehicles::isVehicleInAir(2.5f, VEHICLE_SELF)) //GetAsyncKeyState(87)
				{
					if (GetTickCount() > dwBikeTime)
					{
						if (eBikeState == 1)
						{
							dwBikeTime = GetTickCount() + 30;
							eBikeState = 2;
						}
						else if (eBikeState == 2)
						{
							keybd_event(VK_BACK, 0, 0, 0);
							dwBikeTime = GetTickCount() + 5;
							eBikeState = 3;
						}
						else if (eBikeState == 3)
						{
							keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0);
							eBikeState = 1;
						}
					}
				}
				else
					if (eBikeState == 3)
					{
						keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0);
						eBikeState = 1;
					}
			}
		}


	}
	void wndProcHook(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info) override
	{
		if (pressNitro && info.isDriver)
			if (wParam == 0 || wParam == 1)
				if (msg == WM_KEYDOWN || msg == WM_LBUTTONDOWN || msg == WM_SYSKEYDOWN)
				{
					*reinterpret_cast<byte*>(0x969165) = 1;
				}
				else  if (msg == WM_KEYUP || msg == WM_LBUTTONUP || msg == WM_SYSKEYUP)
				{
					*reinterpret_cast<byte*>(0x969165) = 0;
					PEDSELF->GetVehicle()->RemoveVehicleUpgrade(1010);
				}
	}
	bool packetOutHook(stRakNetHookParams *param, const crTickLocalPlayerInfo& info) override
	{
		if ((noFall || surfOnVehicles) && (param->packetId == ID_PLAYER_SYNC))
		{
			stOnFootData data;
			memset(&data, 0, sizeof(stOnFootData));
			byte packet;
			param->bitStream->ResetReadPointer();
			param->bitStream->Read(packet);
			param->bitStream->Read((PCHAR)&data, sizeof(stOnFootData));
			param->bitStream->ResetReadPointer();
			if (noFall)
				data.stSampKeys.keys_decel__jump = 0;
			if (surfOnVehicles)
				data.sSurfingVehicleID = 0;
			param->bitStream->ResetWritePointer();
			param->bitStream->Write(packet);
			param->bitStream->Write((PCHAR)&data, sizeof(stOnFootData));
			return true;
		}
		if (noReload && param->packetId == ID_BULLET_SYNC)
			PEDSELF->GetWeapon(PEDSELF->GetCurrentWeaponSlot())->SetAmmoInClip(2);
		return true;
	}
	void save(Json::Value& data) override
	{
		data["antiStun"] = antiStun;
		data["driveWalkUnderWater"] = driveWalkUnderWater;
		data["fireProtection"] = fireProtection;
		data["fastCrosshair"] = fastCrosshair;
		data["infOxygenAndStamina"] = infOxygenAndStamina;
		data["megaJump"] = megaJump;
		data["noSpread"] = noSpread;
		data["noFreeze"] = noFreeze;
		data["noAnims"] = noAnims;
		data["noCamrestore"] = noCamrestore;
		data["noFall"] = noFall;
		data["surfOnVehicles"] = surfOnVehicles;
		data["wallShot"] = wallShot;
		data["pressNitro"] = pressNitro;
		data["noFallDamage"] = noFallDamage;
		data["noBike"] = noBike;
		data["waterDrive"] = waterDrive;
		data["noReload"] = noReload;
		data["autoBike"] = autoBike;
		data["NewDL"] = newDl;
		data["WaterProofEng"] = waterProofEngine;
		data["160hpbar"] = bar160hp;
	}
	void read(Json::Value& data)   override
	{
		antiStun = data["antiStun"].asBool();
		driveWalkUnderWater = data["driveWalkUnderWater"].asBool();
		fireProtection = data["fireProtection"].asBool();
		fastCrosshair = data["fastCrosshair"].asBool();
		infOxygenAndStamina = data["infOxygenAndStamina"].asBool();
		megaJump = data["megaJump"].asBool();
		noSpread = data["noSpread"].asBool();
		noFreeze = data["noFreeze"].asBool();
		noAnims = data["noAnims"].asBool();
		noCamrestore = data["noCamrestore"].asBool();
		noFall = data["noFall"].asBool();
		surfOnVehicles = data["surfOnVehicles"].asBool();
		wallShot = data["wallShot"].asBool();
		pressNitro = data["pressNitro"].asBool();
		noFallDamage = data["noFallDamage"].asBool();
		noBike = data["noBike"].asBool();
		waterDrive = data["waterDrive"].asBool();
		noReload = data["noReload"].asBool();
		autoBike = data["autoBike"].asBool();
		newDl = data["NewDL"].asBool();
		waterProofEngine = data["WaterProofEng"].asBool();
		bar160hp = data["160hpbar"].asBool();
	}
};
