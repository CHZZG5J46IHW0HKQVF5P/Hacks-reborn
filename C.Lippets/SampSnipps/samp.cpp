/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, BlastHack

	mod_sa is available from https://github.com/BlastHackNet/mod_s0beit_sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

	*/

#define SAMP_DLL "samp.dll"
#define SAMP_CMP "F8036A004050518D4C24"

#include "SampSnipps/samp.h"

extern SAMPFUNCS *SF;

int SAMPSobeit::isBadSAMPVehicleID(int iVehicleID)
{
	if (SF->getSAMP()->getVehicles() == NULL || iVehicleID == (uint16_t)-1 || iVehicleID >= SAMP_MAX_VEHICLES)
		return 1;
	return !SF->getSAMP()->getVehicles()->iIsListed[iVehicleID];
}

int SAMPSobeit::isBadSAMPPlayerID(int iPlayerID)
{
	if (SF->getSAMP()->getPlayers() == NULL || iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
		return 1;
	return !SF->getSAMP()->getPlayers()->iIsListed[iPlayerID];
}

int SAMPSobeit::getNthPlayerID(int n)
{
	if (SF->getSAMP()->getPlayers() == NULL)
		return -1;

	int thisplayer = 0;
	for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (SF->getSAMP()->getPlayers()->iIsListed[i] != 1)
			continue;
		if (SF->getSAMP()->getPlayers()->sLocalPlayerID == i)
			continue;
		if (thisplayer < n)
		{
			thisplayer++;
			continue;
		}

		return i;
	}

	//shouldnt happen
	return -1;
}

int SAMPSobeit::getPlayerCount(void)
{
	if (SF->getSAMP()->getPlayers() == NULL)
		return NULL;

	int iCount = 0;
	int i;

	for (i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (SF->getSAMP()->getPlayers()->iIsListed[i] != 1)
			continue;
		iCount++;
	}

	return iCount + 1;
}

int SAMPSobeit::getVehicleCount(void)
{
	if (SF->getSAMP()->getVehicles() == NULL)
		return NULL;

	int iCount = 0;
	int i;

	for (i = 0; i < SAMP_MAX_VEHICLES; i++)
	{
		if (SF->getSAMP()->getVehicles()->iIsListed[i] != 1)
			continue;
		iCount++;
	}

	return iCount;
}

int SAMPSobeit::getPlayerVehicleGTAScriptingID(int iPlayerID)
{
	if (SF->getSAMP()->getPlayers() == NULL)
		return 0;

	// fix to always return our own vehicle always if that's what's being asked for
	if (iPlayerID == ACTOR_SELF)
	{
		if (SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID == (uint16_t)-1)
			return 0;

		stSAMPVehicle *sampveh = SF->getSAMP()->getVehicles()->pSAMP_Vehicle[SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID];
		if (sampveh)
		{
			return ScriptCarId(sampveh->pGTA_Vehicle);
			//return (int)( ((DWORD) sampveh->pGTA_Vehicle) - (DWORD) pool_vehicle->start ) / 2584;
		}
		else
			return 0;
	}

	// make sure remote player is legit
	if (SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID] == NULL || SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData == NULL ||
		SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle == NULL ||
		SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle == NULL)
		return 0;

	// make sure samp knows the vehicle exists
	if (SF->getSAMP()->getVehicles()->pSAMP_Vehicle[SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->sVehicleID] == NULL)
		return 0;

	// return the remote player's vehicle
	return ScriptCarId(SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle);
}

int SAMPSobeit::getPlayerSAMPVehicleID(int iPlayerID)
{
	if (SF->getSAMP()->getPlayers() == NULL && SF->getSAMP()->getVehicles() == NULL)
		return 0;
	if (SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID] == NULL)
		return 0;
	if (SF->getSAMP()->getVehicles()->pSAMP_Vehicle[SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->sVehicleID] == NULL)
		return 0;
	return SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->sVehicleID;
}

struct actor_info *SAMPSobeit::getGTAPedFromSAMPPlayerID(int iPlayerID)
{
	if (SF->getSAMP()->getPlayers() == NULL || iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
		return NULL;
	if (iPlayerID == SF->getSAMP()->getPlayers()->sLocalPlayerID)
		return actor_info_get(ACTOR_SELF, 0);
	if (SF->getSAMP()->getPlayers()->iIsListed[iPlayerID] != 1)
		return NULL;
	if (SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID] == NULL)
		return NULL;
	if (SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
		return NULL;
	if (SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL)
		return NULL;
	if (SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL)
		return NULL;

	// return actor_info, null or otherwise
	return SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;
}

struct vehicle_info *SAMPSobeit::getGTAVehicleFromSAMPVehicleID(int iVehicleID)
{
	if (SF->getSAMP()->getVehicles() == NULL || iVehicleID < 0 || iVehicleID >= SAMP_MAX_VEHICLES)
		return NULL;
	if (iVehicleID == SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID)
		return vehicle_info_get(VEHICLE_SELF, 0);
	if (SF->getSAMP()->getVehicles()->iIsListed[iVehicleID] != 1)
		return NULL;

	// return vehicle_info, null or otherwise
	return SF->getSAMP()->getVehicles()->pGTA_Vehicle[iVehicleID];
}

int SAMPSobeit::getSAMPPlayerIDFromGTAPed(struct actor_info *pGTAPed)
{
	if (SF->getSAMP()->getPlayers() == NULL)
		return 0;
	if (actor_info_get(ACTOR_SELF, 0) == pGTAPed)
		return SF->getSAMP()->getPlayers()->sLocalPlayerID;

	int i;
	for (i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (SF->getSAMP()->getPlayers()->iIsListed[i] != 1)
			continue;
		if (SF->getSAMP()->getPlayers()->pRemotePlayer[i] == NULL)
			continue;
		if (SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData == NULL)
			continue;
		if (SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL)
			continue;
		if (SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL)
			continue;
		if (SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == pGTAPed)
			return i;
	}

	return ACTOR_SELF;
}

int SAMPSobeit::getSAMPVehicleIDFromGTAVehicle(struct vehicle_info *pVehicle)
{
	if (SF->getSAMP()->getVehicles() == NULL)
		return NULL;
	if (vehicle_info_get(VEHICLE_SELF, 0) == pVehicle && SF->getSAMP()->getPlayers() != NULL)
		return SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID;

	int i, iReturn = 0;
	for (i = 0; i < SAMP_MAX_VEHICLES; i++)
	{
		if (SF->getSAMP()->getVehicles()->iIsListed[i] != 1)
			continue;
		if (SF->getSAMP()->getVehicles()->pGTA_Vehicle[i] == pVehicle)
			return i;
	}

	return VEHICLE_SELF;
}

uint32_t SAMPSobeit::getPedGTAScriptingIDFromPlayerID(int iPlayerID)
{

	if (SF->getSAMP()->getPlayers()->iIsListed[iPlayerID] != 1)
		return NULL;
	if (SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID] == NULL)
		return NULL;
	if (SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
		return NULL;
	if (SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL)
		return NULL;

	return SF->getSAMP()->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle;
}

uint32_t SAMPSobeit::getVehicleGTAScriptingIDFromVehicleID(int iVehicleID)
{
	if (SF->getSAMP()->getVehicles() == NULL)
		return NULL;

	if (SF->getSAMP()->getVehicles()->iIsListed[iVehicleID] != 1)
		return NULL;
	if (SF->getSAMP()->getVehicles()->pSAMP_Vehicle[iVehicleID] == NULL)
		return NULL;

	return SF->getSAMP()->getVehicles()->pSAMP_Vehicle[iVehicleID]->ulGTAEntityHandle;
}
