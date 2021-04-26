#include "Fix.h"


Fix::Fix(const char* name)
{
	isEnable = true;
}
bool Fix::onRPCIncoming(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
{
	switch (params->packetId)
	{
	case 35: /*SetPlayerDrunkLevel*/
		return false;
	case 106:
		return false; /*UpdateVehicleDamageStatus*/
	case 44 /*CREATEOBJECT*/:
	{
		UINT16 wObjectID;
		UINT32 ModelID;
		params->bitStream->ResetReadPointer();
		params->bitStream->Read(wObjectID);
		params->bitStream->Read(ModelID);
		params->bitStream->ResetReadPointer();
		if (ModelID == 0) return false;
		break;
	}
	case 93 /*SendClientMessage*/:
	{
		UINT32 iColor;
		UINT32 iMsgL;
		char szMsg[256];
		params->bitStream->ResetReadPointer();
		params->bitStream->Read(iColor);
		params->bitStream->Read(iMsgL);
		params->bitStream->Read(szMsg, iMsgL);
		params->bitStream->ResetReadPointer();
		szMsg[iMsgL] = '\0';
		if (Lippets::Conditions::multiStrStr2(false, szMsg, "[���������]", "���� ������ ������!", "���������� ������� �� �������", "����, ������ ������!", "���������� �� �������",
			"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", "�������� ������� �������:", "�������� ����� � ������ �����", "��� ����: arizona-rp.com",
			"� ����� �������� �� ������ ����������", "�� �� �������� ����� {FFFFFF}������", "������ �� �������� {FFFFFF}VIP{6495ED}", "� �������� ���-�� ����� ���������� ������",
			"� ���-�� ��������, ������� ������� ���� �� �����!", 0))
			return false;
		break;
	}
	case 147:
	{
		if (!info.isDriver)
			break;
		int16 iAutoID;
		float fHealth;
		params->bitStream->ResetReadPointer();
		params->bitStream->Read(iAutoID);
		params->bitStream->Read(fHealth);
		if (iAutoID == SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID) // ��������� � ����� ����
		{
			vehicle_info* vehicle = SF->getGame()->vehicleInfoGet(VEHICLE_SELF, VEHICLE_ALIVE);
			if (vehicle->hitpoints < fHealth) // ���� ��� ��������� ��
				if ((vehicle->hitpoints - fHealth) == 200.0f)
				{
					SF->getSAMP()->getChat()->AddChatMessage(0xFF00FF, "� ��������� �� ���� ��������");
					return false;
				}
		}
		break;
	}
	default:break;
	}
	return true;
}