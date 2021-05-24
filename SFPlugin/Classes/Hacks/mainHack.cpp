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
		if (!g::pInfo->isDriver)
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

bool MainHack::onWndProc(WPARAM wParam, UINT msg)
{
	auto keyState = Stuff::getKeyStateByMsg(msg);
	switch (wParam)
	{
	case 16:
		g::isShiftPressed = (keyState == eKeyState::PRESSED ? true : false);
		break;
	case 17:
		g::isCtrlPressed = (keyState == eKeyState::PRESSED ? true : false);
		break;
	case 18:
		g::isAltPressed = (keyState == eKeyState::PRESSED ? true : false);
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