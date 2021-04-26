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
		if (Lippets::Conditions::multiStrStr2(false, szMsg, "[Наркотики]", "авто крайне плохое!", "Необходимо заехать на станцию", "авто, крайне плохое!", "Обратитесь на станцию",
			"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", "Основные команды сервера:", "Пригласи друга и получи бонус", "Наш сайт: arizona-rp.com",
			"В нашем магазине ты можешь приобрести", "их на желаемый тобой {FFFFFF}бизнес", "Игроки со статусом {FFFFFF}VIP{6495ED}", "В магазине так-же можно приобрести редкие",
			"а так-же предметы, которые выделят тебя из толпы!", 0))
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