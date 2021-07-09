#pragma once
#include "SampSnipps/cheat_funcs.h"
#include "SampSnipps/math_stuff.h"
#include "SAMPFUNCS_API.h"
#include "game_api.h"

namespace SAMPSobeit
{

    int isBadSAMPVehicleID(int iVehicleID);

    int isBadSAMPPlayerID(int iPlayerID);

    int getNthPlayerID(int n);
    int getPlayerCount(void);

    int getVehicleCount(void);

    int getPlayerVehicleGTAScriptingID(int iPlayerID);

    int getPlayerSAMPVehicleID(int iPlayerID);

    struct actor_info *getGTAPedFromSAMPPlayerID(int iPlayerID);
    struct vehicle_info *getGTAVehicleFromSAMPVehicleID(int iVehicleID);

    int getSAMPPlayerIDFromGTAPed(struct actor_info *pGTAPed);

    int getSAMPVehicleIDFromGTAVehicle(struct vehicle_info *pVehicle);

    uint32_t getPedGTAScriptingIDFromPlayerID(int iPlayerID);

    uint32_t getVehicleGTAScriptingIDFromVehicleID(int iVehicleID);
}