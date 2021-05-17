#include "Fix.h"


Fix::Fix(const char* name)
{
	m_sHackName = name;
	m_bEnabled = true;
}

bool Fix::onRPCOutcoming(stRakNetHookParams* params)
{
	switch (params->packetId)
	{
	case RPCEnumeration::RPC_DamageVehicle:
		return false; /*UpdateVehicleDamageStatus*/
	}
	return true;
}

bool Fix::onRPCIncoming(stRakNetHookParams* params)
{
	switch (params->packetId)
	{
	case ScriptRPCEnumeration::RPC_ScrSetPlayerDrunkLevel: /*SetPlayerDrunkLevel*/
		return false;
	case ScriptRPCEnumeration::RPC_ScrCreateObject /*CREATEOBJECT*/:
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
	case ScriptRPCEnumeration::RPC_ScrClientMessage /*SendClientMessage*/:
	{
		UINT32 iColor;
		UINT32 iMsgL;
		char *szMsg;
		params->bitStream->ResetReadPointer();
		params->bitStream->Read(iColor);
		params->bitStream->Read(iMsgL);
		szMsg = new char[iMsgL];
		params->bitStream->Read(szMsg, iMsgL);
		params->bitStream->ResetReadPointer();
		szMsg[iMsgL] = '\0';
		if (Lippets::Conditions::multiStrStr2(false, szMsg, "[���������]", "���� ������ ������!", "���������� ������� �� �������", "����, ������ ������!", "���������� �� �������",
			"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", "�������� ������� �������:", "�������� ����� � ������ �����", "��� ����: arizona-rp.com",
			"� ����� �������� �� ������ ����������", "�� �� �������� ����� {FFFFFF}������", "������ �� �������� {FFFFFF}VIP{6495ED}", "� �������� ���-�� ����� ���������� ������",
			"� ���-�� ��������, ������� ������� ���� �� �����!", 0))
		{
			delete[] szMsg;
			return false;
		}
		delete[] szMsg;
		break;
	}
	case ScriptRPCEnumeration::RPC_ScrSetVehicleHealth:
	{
		if (!g::pInfo->isDriver)
			return true;
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