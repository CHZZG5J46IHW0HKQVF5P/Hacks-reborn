#include "1lineHacks.h"
#include "nameof/nameof.hpp"

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

void GiveWeapon(eWeaponType eWeapon, uint32_t ammo)
{
	PEDSELF->GiveWeapon(eWeapon, ammo, eWeaponSkill::WEAPONSKILL_MAX_NUMBER);
}

void EnableMegaBMXJump(bool bEnable)
{
	WriteMem<byte>(0x969161, sizeof(byte), bEnable, true);
	//*(byte*)0x969161 = bEnable;
}

void EnableGodMode(bool bEnable)
{
	*(byte*)(0x96916D) = bEnable;
}


void setAnimGroupByRunType(RUN_TYPE runType)
{
	int iModelIndex = PEDSELF->GetModelIndex();
	switch (runType)
	{
	case RUN_TYPE::CJ:
	{
		RPC_emulating::setskin(MYID, 0);
		RPC_emulating::setskin(MYID, iModelIndex);
		*PEDSELF->GetMemoryValue(0x4D4) = 54;
		break;
	}
	case RUN_TYPE::ROLLER:
	{
		RPC_emulating::setskin(MYID, 99);
		RPC_emulating::setskin(MYID, iModelIndex);
		*PEDSELF->GetMemoryValue(0x4D4) = 138;
		break;
	}
	case RUN_TYPE::SWAT:
	{
		RPC_emulating::setskin(MYID, 285);
		RPC_emulating::setskin(MYID, iModelIndex);
		*PEDSELF->GetMemoryValue(0x4D4) = 128;
		break;
	}
	case RUN_TYPE::DEFAULT:
	{
		RPC_emulating::setskin(MYID, iModelIndex);
		break;
	}
	}
}

void setFightStyle(FIGHT_STYLE fightStyle)
{

	switch (fightStyle)
	{
	case  FIGHT_STYLE::DEFAULT:
		RPC_emulating::setPlayerFightStyle(MYID, 4);
		break;
	case  FIGHT_STYLE::BOXING:
		RPC_emulating::setPlayerFightStyle(MYID, 5);
		break;
	case  FIGHT_STYLE::KUNG_FU:
		RPC_emulating::setPlayerFightStyle(MYID, 6);
		break;
	case  FIGHT_STYLE::KNEE_HEAD:
		RPC_emulating::setPlayerFightStyle(MYID, 7);
		break;
	case  FIGHT_STYLE::GRABKICK:
		RPC_emulating::setPlayerFightStyle(MYID, 15);
		break;
	case  FIGHT_STYLE::ELBOWS:
		RPC_emulating::setPlayerFightStyle(MYID, 16);
		break;
	}
}


OneLineHacks::OneLineHacks(const char* name)
{
	m_sHackName = name;
	m_bEnabled = true;
	SF->getSAMP()->registerChatCommand("setskin", [](std::string args)
		{

			uint32_t iSkinID = atoi(args.c_str());
			if (iSkinID > 0 && iSkinID < 311)
				RPC_emulating::setskin(MYID, iSkinID);

		});
	SF->getSAMP()->registerChatCommand("die", [](std::string args)
		{
			if (Players::isLocalPlayerExist())
				PEDSELF->SetHealth(0.0f);
		});
	SF->getSAMP()->registerChatCommand("delgun", [](std::string args)
		{
			if (Players::isLocalPlayerExist())
			{
				eWeaponSlot eWSlot = PEDSELF->GetCurrentWeaponSlot();
				if (eWSlot != 0)
					PEDSELF->GetWeapon(eWSlot)->Remove();
			}
		});
	SF->getSAMP()->registerChatCommand("parashut", [](std::string args)
		{
			GiveWeapon(eWeaponType::WEAPONTYPE_PARACHUTE, 1);
			PEDSELF->SetCurrentWeaponSlot(eWeaponSlot::WEAPONSLOT_TYPE_PARACHUTE);
		});
	SF->getSAMP()->registerChatCommand("fafk", [](std::string args)
		{
			bFakeAfk = !bFakeAfk;// true;
			notify("Fake AFK", bFakeAfk);
		});
	SF->getSAMP()->registerChatCommand("fasth", [](std::string args)
		{
			bFastHelper = !bFastHelper;// true;
			notify("Fast Helper", bFastHelper);
		});
}


void OneLineHacks::onDrawGUI()
{
	if (ImGui::Checkbox("Anti Stun", &bAntiStun))
		EnableAntiStun(bAntiStun);
	if (ImGui::Checkbox("Drive Walk UnderWater", &bDriveWalkUnderWater))
		EnableDriveOrWalkUnderWater(bDriveWalkUnderWater);
	if (ImGui::Checkbox("Fire Protection", &bFireProtection))
		EnableFireProtection(bFireProtection);
	if (ImGui::Checkbox("Fast Crosshair", &bFastCrosshair))
		EnableFastCrosshair(bFastCrosshair);
	if (ImGui::Checkbox("Infinity Oxygen | Stamina", &bInfOxygenAndStamina))
		EnableInfOxygenAndStamina(bInfOxygenAndStamina);
	if (ImGui::Checkbox("Mega Jump", &bMegaJump))
		EnableMegaJump(bMegaJump);
	if (ImGui::Checkbox("No Spread", &bNoSpread))
		EnableNoSpread(bNoSpread);
	if (ImGui::Checkbox("No Freeze", &bNoFreeze))
		EnableNoFreeze(bNoFreeze);
	if (ImGui::Checkbox("No Anims", &bNoAnims))
		EnableNoAnims(bNoAnims);
	if (ImGui::Checkbox("No Cam Restore", &bNoCamrestore))
		EnableNoCamRestore(bNoCamrestore);
	ImGui::Checkbox("No Fall & No Drop", &bNoFall);
	ImGui::Checkbox("Surf On Vehicles", &bSurfOnVehicles);

	ImGui::Checkbox("Press Nitro", &bPressNitro);
	if (ImGui::Checkbox("No Fall Damage", &bNoFallDamage))
		EnableNoFallDamage(bNoFallDamage);
	ImGui::Checkbox("No Bike", &bNoBike);
	if (ImGui::Checkbox("Water Drive", &bWaterDrive))
		EnableWaterDrive(bWaterDrive);
	if (ImGui::Checkbox("New DL", &bNewDl))
		EnableNewDL(bNewDl);
	if (ImGui::Checkbox("Water Proof Engine", &bWaterProofEngine))
		EnableWaterProofEng(bWaterProofEngine);
	if (ImGui::Checkbox("160 HP bar", &bBar160hp))
		Enable160HPbar(bBar160hp);
	ImGui::Checkbox("No Reload", &bNoReload);
	ImGui::Checkbox("Auto Bike", &bAutoBike);
	ImGui::Checkbox("Dont Give Me Bat", &bDontGiveMeBat);
	ImGui::Checkbox("Mega BMX Jump", &bMegaBMXJump);

	ImGui::Text("Custom Run Anim");
	if (ImGui::IsItemClicked())
		ImGui::OpenPopup("Choose Run Anim");
	if (ImGui::BeginPopup("Choose Run Anim"))
	{

		for (int i = 0; i <= (int)RUN_TYPE::SWAT; i++)
			if (ImGui::Button(nameof::nameof_enum((RUN_TYPE)i).data()))
			{
				CurrentRunType = (RUN_TYPE)i;
				setAnimGroupByRunType(CurrentRunType);
			}

		ImGui::EndPopup();
	}
	ImGui::Text("Custom Fight Style");
	if (ImGui::IsItemClicked())
		ImGui::OpenPopup("Choose Fight Style");
	if (ImGui::BeginPopup("Choose Fight Style"))
	{
		for (int i = 0; i <= (int)FIGHT_STYLE::ELBOWS; i++)
			if (ImGui::Button(nameof::nameof_enum((FIGHT_STYLE)i).data()))
			{
				CurrentFightStyle = (FIGHT_STYLE)i;
				setFightStyle(CurrentFightStyle);
			}
		ImGui::EndPopup();
	}
	if (ImGui::Checkbox("GodMode", &bGodMode))
		EnableGodMode(bGodMode);
	ImGui::Checkbox("Flip Vehicle", &bFlipVehicle);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(nFlipVehicleActivationKey, g::keyButtonSplitter);
	ImGui::Checkbox("Map Teleport", &bMapTeleport);
	ImGui::Checkbox("Always Horn", &bEternalHorn);
}

void OneLineHacks::onDrawHack()
{
	if (bFastHelper)
		SF->getRender()->DrawPolygon(iScrResX - 10, iScrResY - 10, 10, 10, 0, 7, 0xFF0000FF);
}

void OneLineHacks::switchHack()
{
	EnableAntiStun(bAntiStun);
	EnableDriveOrWalkUnderWater(bDriveWalkUnderWater);
	EnableFireProtection(bFireProtection);
	EnableFastCrosshair(bFastCrosshair);
	EnableInfOxygenAndStamina(bInfOxygenAndStamina);
	EnableMegaJump(bMegaJump);
	EnableNoSpread(bNoSpread);
	EnableNoFreeze(bNoFreeze);
	EnableNoAnims(bNoAnims);
	EnableNoCamRestore(bNoCamrestore);
	EnableNoFallDamage(bNoFallDamage);
	EnableWaterDrive(bWaterDrive);
	EnableNewDL(bNewDl);
	EnableWaterProofEng(bWaterProofEngine);
	EnableMegaBMXJump(bMegaBMXJump);
	EnableGodMode(bGodMode);
	setAnimGroupByRunType(CurrentRunType);
	setFightStyle(CurrentFightStyle);
}
void OneLineHacks::everyTickAction()
{
	if (bFastHelper)
		SF->getGame()->emulateGTAKey(4, 255);
	if (g::pInfo->isDriver())
	{
		if (bNoBike)
		{
			if (g::pInfo->vehType != Vehicles::eVehicleType::CBike ||
				g::pInfo->vehType != eVehicleType::CBMX)
			{
				if (PEDSELF->GetVehicle()->IsDrowning())
				{
					if (PEDSELF->GetCantBeKnockedOffBike() == 1)
						PEDSELF->SetCantBeKnockedOffBike(0);
				}
				else
					if (PEDSELF->GetCantBeKnockedOffBike() == 0)
						PEDSELF->SetCantBeKnockedOffBike(1);
			}

		}
		if (bAutoBike)
		{
			static uint8 eBikeState = 1;
			static CMTimer timer;
			if (PEDSELF->GetVehicle()->GetGasPedal() == 1.f && !SF->getSAMP()->getInput()->iInputEnabled)
			{
				if (timer.isEnded())
				{
					if (eBikeState == 1)
					{
						timer.setTimer(50);
						eBikeState = 2;
					}
					else if (eBikeState == 2)
					{
						Lippets::KeyBoard::SendKeyPress(VK_UP, 0); //keybd_event(VK_BACK, 0, 0, 0);
						timer.setTimer(5);
						eBikeState = 3;
					}
					else if (eBikeState == 3)
					{
						Lippets::KeyBoard::SendKeyRelease(VK_UP, 0); //keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0);
						eBikeState = 1;
					}
				}
			}
			else
				if (eBikeState == 3)
				{
					Lippets::KeyBoard::SendKeyRelease(VK_UP, 0); //keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0);
					eBikeState = 1;
				}
		}
	}


}



bool OneLineHacks::onWndProc()
{

	if (g::pInfo->isDriver())
	{
		if (g::pKeyEventInfo->iKeyID == 0 || g::pKeyEventInfo->iKeyID == 1)
			if (bPressNitro)
				if (g::pKeyEventInfo->bDown)
				{
					*reinterpret_cast<byte*>(0x969165) = 1;
				}
				else
				{
					*reinterpret_cast<byte*>(0x969165) = 0;
					PEDSELF->GetVehicle()->RemoveVehicleUpgrade(1010);

				}
		if (g::pKeyEventInfo->iKeyID == nFlipVehicleActivationKey)
		{

			float fRotation = PEDSELF->GetTargetRotation();
			PEDSELF->GetVehicle()->Teleport(g::pInfo->pLocalVeh->base.matrix[4 * 3],
				g::pInfo->pLocalVeh->base.matrix[4 * 3 + 1],
				g::pInfo->pLocalVeh->base.matrix[4 * 3 + 2]);
			RPC_emulating::setVehicleZAngle(SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID, fRotation * (180.0 / M_PI));
		}
	}

	return true;
}

bool OneLineHacks::onRPCOutcoming(stRakNetHookParams* params)
{

	switch (params->packetId)
	{
	case RPCEnumeration::RPC_MapMarker:
	{
		if (bMapTeleport)
		{
			float fCoords[3];
			params->bitStream->ResetReadPointer();
			params->bitStream->Read((char*)fCoords, 12);
			PEDSELF->Teleport(fCoords[0], fCoords[1], fCoords[2]);
		}
		return true;
	}
	default:
		break;
	}
	return true;
}
bool OneLineHacks::onRPCIncoming(stRakNetHookParams* params)
{
	if (!bDontGiveMeBat || params->packetId != ScriptRPCEnumeration::RPC_ScrGivePlayerWeapon)
		return true;
	UINT32 dWeaponID;
	params->bitStream->ResetReadPointer();
	params->bitStream->Read(dWeaponID);
	if (dWeaponID == 5)
		return false;
	return true;
}
bool OneLineHacks::onPacketOutcoming(stRakNetHookParams* param)
{
	switch (param->packetId)
	{
	case ID_VEHICLE_SYNC:
		if (bEternalHorn)
		{
			stInCarData data;
			memset(&data, 0, sizeof(stInCarData));
			byte packet;
			param->bitStream->ResetReadPointer();
			param->bitStream->Read(packet);
			param->bitStream->Read((PCHAR)&data, sizeof(stInCarData));
			param->bitStream->ResetReadPointer();
			data.byteSiren = 1;
			data.stSampKeys.keys_horn__crouch = 1;
			param->bitStream->ResetWritePointer();
			param->bitStream->Write(packet);
			param->bitStream->Write((PCHAR)&data, sizeof(stInCarData));
			return true;
		}
	case ID_PLAYER_SYNC:
		if (bNoFall || bSurfOnVehicles || bFakeAfk)
		{
			if (bFakeAfk)
				return false;
			stOnFootData data;
			memset(&data, 0, sizeof(stOnFootData));
			byte packet;
			param->bitStream->ResetReadPointer();
			param->bitStream->Read(packet);
			param->bitStream->Read((PCHAR)&data, sizeof(stOnFootData));
			param->bitStream->ResetReadPointer();
			if (bNoFall)
				data.stSampKeys.keys_decel__jump = 0;
			if (bSurfOnVehicles)
				data.sSurfingVehicleID = 0;
			param->bitStream->ResetWritePointer();
			param->bitStream->Write(packet);
			param->bitStream->Write((PCHAR)&data, sizeof(stOnFootData));
			return true;
		}
	case ID_BULLET_SYNC:
		if (bNoReload)
			PEDSELF->GetWeapon(PEDSELF->GetCurrentWeaponSlot())->SetAmmoInClip(2);
	}

	return true;
}

void OneLineHacks::save(nlohmann::json& data)
{
	SERIALIZE_FIELD_JSON(bMapTeleport);
	SERIALIZE_FIELD_JSON(bFlipVehicle);
	SERIALIZE_FIELD_JSON(nFlipVehicleActivationKey);
	SERIALIZE_FIELD_JSON(CurrentRunType);
	SERIALIZE_FIELD_JSON(CurrentFightStyle);
	SERIALIZE_FIELD_JSON(bMegaBMXJump);
	SERIALIZE_FIELD_JSON(bDontGiveMeBat);
	SERIALIZE_FIELD_JSON(bAntiStun);
	SERIALIZE_FIELD_JSON(bDriveWalkUnderWater);
	SERIALIZE_FIELD_JSON(bFireProtection);
	SERIALIZE_FIELD_JSON(bFastCrosshair);
	SERIALIZE_FIELD_JSON(bInfOxygenAndStamina);
	SERIALIZE_FIELD_JSON(bMegaJump);
	SERIALIZE_FIELD_JSON(bNoSpread);
	SERIALIZE_FIELD_JSON(bNoFreeze);
	SERIALIZE_FIELD_JSON(bNoAnims);
	SERIALIZE_FIELD_JSON(bNoCamrestore);
	SERIALIZE_FIELD_JSON(bNoFall);
	SERIALIZE_FIELD_JSON(bSurfOnVehicles);
	SERIALIZE_FIELD_JSON(bPressNitro);
	SERIALIZE_FIELD_JSON(bNoFallDamage);
	SERIALIZE_FIELD_JSON(bNoBike);
	SERIALIZE_FIELD_JSON(bWaterDrive);
	SERIALIZE_FIELD_JSON(bNoReload);
	SERIALIZE_FIELD_JSON(bAutoBike);
	SERIALIZE_FIELD_JSON(bNewDl);
	SERIALIZE_FIELD_JSON(bWaterProofEngine);
	SERIALIZE_FIELD_JSON(bBar160hp);
	SERIALIZE_FIELD_JSON(bGodMode);
}
void OneLineHacks::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON(bMapTeleport);
	DESERIALIZE_FIELD_JSON(bFlipVehicle);
	DESERIALIZE_FIELD_JSON(nFlipVehicleActivationKey);
	DESERIALIZE_FIELD_JSON(CurrentFightStyle);// = (FIGHT_STYLE)data["FightStyle"].get<int>();
	DESERIALIZE_FIELD_JSON(CurrentRunType); //(RUN_TYPE)data["RunType"].get<int>();
	DESERIALIZE_FIELD_JSON(bMegaBMXJump);
	DESERIALIZE_FIELD_JSON(bDontGiveMeBat);
	DESERIALIZE_FIELD_JSON(bAntiStun);
	DESERIALIZE_FIELD_JSON(bDriveWalkUnderWater);
	DESERIALIZE_FIELD_JSON(bFireProtection);
	DESERIALIZE_FIELD_JSON(bFastCrosshair);
	DESERIALIZE_FIELD_JSON(bInfOxygenAndStamina);
	DESERIALIZE_FIELD_JSON(bMegaJump);
	DESERIALIZE_FIELD_JSON(bNoSpread);
	DESERIALIZE_FIELD_JSON(bNoFreeze);
	DESERIALIZE_FIELD_JSON(bNoAnims);
	DESERIALIZE_FIELD_JSON(bNoCamrestore);
	DESERIALIZE_FIELD_JSON(bNoFall);
	DESERIALIZE_FIELD_JSON(bSurfOnVehicles);
	DESERIALIZE_FIELD_JSON(bPressNitro);
	DESERIALIZE_FIELD_JSON(bNoFallDamage);
	DESERIALIZE_FIELD_JSON(bNoBike);
	DESERIALIZE_FIELD_JSON(bWaterDrive);
	DESERIALIZE_FIELD_JSON(bNoReload);
	DESERIALIZE_FIELD_JSON(bAutoBike);
	DESERIALIZE_FIELD_JSON(bNewDl);
	DESERIALIZE_FIELD_JSON(bWaterProofEngine);
	DESERIALIZE_FIELD_JSON(bBar160hp);
	DESERIALIZE_FIELD_JSON(bGodMode);
}


