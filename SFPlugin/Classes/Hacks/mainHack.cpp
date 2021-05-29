#include "mainHack.h"


MainHack::MainHack(const char* szHackName)
{
	m_sHackName = szHackName;
	m_bEnabled = true;
}

bool MainHack::onRPCOutcoming(stRakNetHookParams* params)
{
	switch (params->packetId)
	{
	case RPCEnumeration::RPC_DamageVehicle:
		return false; /*UpdateVehicleDamageStatus*/
	}
	return true;
}

bool MainHack::onRPCIncoming(stRakNetHookParams* params)
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
		if (Lippets::Conditions::multiStrStr2(false, szMsg, "[Наркотики]", "авто крайне плохое!", "Необходимо заехать на станцию", "авто, крайне плохое!", "Обратитесь на станцию",
			"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", "Основные команды сервера:", "Пригласи друга и получи бонус", "Наш сайт: arizona-rp.com",
			"В нашем магазине ты можешь приобрести", "их на желаемый тобой {FFFFFF}бизнес", "Игроки со статусом {FFFFFF}VIP{6495ED}", "В магазине так-же можно приобрести редкие",
			"а так-же предметы, которые выделят тебя из толпы!", 0))
		{
			delete[] szMsg;
			return false;
		}
		delete[] szMsg;
		break;
	}
	case ScriptRPCEnumeration::RPC_ScrSetVehicleHealth:
	{
		if (!g::pInfo->isDriver())
			return true;
		int16 iAutoID;
		float fHealth;
		params->bitStream->ResetReadPointer();
		params->bitStream->Read(iAutoID);
		params->bitStream->Read(fHealth);
		if (iAutoID == SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID) // махинации с вашим авто
		{
			vehicle_info* vehicle = SF->getGame()->vehicleInfoGet(VEHICLE_SELF, VEHICLE_ALIVE);
			if (vehicle->hitpoints < fHealth) // если вам уменьшают хп
				if ((vehicle->hitpoints - fHealth) == 200.0f)
				{
					SF->getSAMP()->getChat()->AddChatMessage(0xFF00FF, "В изменении хп авто отказано");
					return false;
				}
		}
		break;
	}
	default:break;
	}
	return true;
}

bool MainHack::onWndProc()
{
	switch (g::pKeyEventInfo->iKeyID)
	{
	case 16:
		g::isShiftPressed = g::pKeyEventInfo->bDown;
		break;
	case 17:
		g::isCtrlPressed = g::pKeyEventInfo->bDown;
		break;
	case 18:
		g::isAltPressed = g::pKeyEventInfo->bDown;
		break;
	}
	return true;
}

void MainHack::everyTickAction()
{
	if (g::isWindowOpen)
	{

		SF->getSAMP()->getMisc()->ToggleCursor(2, 0);

		if (SF->getSAMP()->getInput()->iInputEnabled)
		{
			SF->getSAMP()->getInput()->DisableInput();
		}
	}
}

void  MainHack::init()
{
	WriteMem<byte>(0x96C009, 1, 1);
	WriteMem<byte>(0x72C1B7, 1, 235);
	WriteMem<int>(0x6CC303, 3, 0x621F8A);

	// no car fire when on roof
	WriteMem<short>(6977387, 2, 55517);
	WriteMem<int>(6977389, 4, -1869574000);
	WriteMem<short>(5705343, 2, 55517);
	WriteMem<int>(5705345, 4, -1869574000);
}