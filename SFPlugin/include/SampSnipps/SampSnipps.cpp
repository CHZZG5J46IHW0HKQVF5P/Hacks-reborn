#include "SampSnipps\SampSnipps.h"
#include "SampSnipps/samp.h"
#include "Files/LUtils.h"
#include <chrono>

extern SAMPFUNCS* SF;
void D3D::CalcScreenCoords(const CVector* vecWorld, CVector* vecScreen)
{

	D3DXMATRIX m((float*)(0xB6FA2C));
	DWORD* dwLenX = (DWORD*)(0xC17044);
	DWORD* dwLenY = (DWORD*)(0xC17048);

	vecScreen->fX = (vecWorld->fZ * m._31) + (vecWorld->fY * m._21) + (vecWorld->fX * m._11) + m._41;
	vecScreen->fY = (vecWorld->fZ * m._32) + (vecWorld->fY * m._22) + (vecWorld->fX * m._12) + m._42;
	vecScreen->fZ = (vecWorld->fZ * m._33) + (vecWorld->fY * m._23) + (vecWorld->fX * m._13) + m._43;

	double fRecip = (double)1.0 / vecScreen->fZ;
	vecScreen->fX *= (float)(fRecip * (*dwLenX));
	vecScreen->fY *= (float)(fRecip * (*dwLenY));
}
void D3D::CalcScreenCoords(D3DXVECTOR3* vecWorld, D3DXVECTOR3* vecScreen)
{
	D3DXMATRIX m((float*)(0xB6FA2C));
	DWORD* dwLenX = (DWORD*)(0xC17044);
	DWORD* dwLenY = (DWORD*)(0xC17048);

	vecScreen->x = (vecWorld->z * m._31) + (vecWorld->y * m._21) + (vecWorld->x * m._11) + m._41;
	vecScreen->y = (vecWorld->z * m._32) + (vecWorld->y * m._22) + (vecWorld->x * m._12) + m._42;
	vecScreen->z = (vecWorld->z * m._33) + (vecWorld->y * m._23) + (vecWorld->x * m._13) + m._43;

	double fRecip = (double)1.0 / vecScreen->z;
	vecScreen->x *= (float)(fRecip * (*dwLenX));
	vecScreen->y *= (float)(fRecip * (*dwLenY));
}
bool D3D::isCoordsOnScreen(const CVector& vecWorld)
{
	CVector posOnScreen;
	CalcScreenCoords(&vecWorld, &posOnScreen);
	return posOnScreen.fZ > 0.01f;
}
float Stuff::getDistanceBetween(const CVector* pos1, const CVector& pos2)
{
	return sqrt((pos1->fX - pos2.fX) * (pos1->fX - pos2.fX) + (pos1->fY - pos2.fY) * (pos1->fY - pos2.fY) + (pos1->fZ - pos2.fZ) * (pos1->fZ - pos2.fZ));
}
float Stuff::getDistanceBetween2d(const CVector2D& vec1, const CVector2D& vec2)
{
	return sqrt(pow(vec1.fX - vec2.fX, 2) + pow(vec1.fY - vec2.fY, 2));
}
void Stuff::AddMessageJumpQ(const std::string& text, unsigned int time, unsigned short flag, bool bPreviousBrief)
{
	static char* szText = nullptr;
	if (szText)
	{
		delete[] szText;
		szText = nullptr;
	}
	szText = new char[text.length()];
	strcpy(szText, text.c_str());
	((void(__cdecl*)(char*, unsigned int, unsigned short, bool))0x69F1E0)(szText, time, flag, bPreviousBrief);
}

int Stuff::isModelLoaded(int iModelID)
{
	int* ModelsLoadStateArray = (int*)0x8E4CD0;
	return ModelsLoadStateArray[5 * iModelID];
}
bool Stuff::TestCheat(const char* cheat)
{
	char* c = reinterpret_cast<char*>(0x00969110);
	char buf[30];
	strcpy(buf, cheat);
	char* s = _strrev(buf);
	if (_strnicmp(s, c, strlen(s)))
		return false;
	*reinterpret_cast<char*>(0x00969110) = 0;
	return true;
}
bool Vehicles::isInValid(sampid id)
{
	return !(id >= 0 && id < 2000);
}
bool Vehicles::isVehicleExist(sampid id)
{
	if (isInValid(id))
		return false;
	if (SF->getSAMP()->getVehicles()->iIsListed[id] != 1)
		return false;
	if (SF->getSAMP()->getVehicles()->pGTA_Vehicle[id] == nullptr)
		return false;
	return true;
}

CVehicle* Vehicles::getVehicleCVehicle(vehicle_info* vehInfo)
{
	CHECK_VALID(vehInfo, nullptr);
	return GAME->GetPools()->GetVehicle((DWORD*)vehInfo);
}

eVehicleType Vehicles::getVehicleType(CVehicle* cveh)
{
	CHECK_VALID(cveh, eVehicleType::NONE);
	return (eVehicleType) * (DWORD*)cveh->GetMemoryValue(0x594);
}
bool Vehicles::isVehicleInAir(float lim, vehicle_info* pVehInfo)
{
	CHECK_VALID(pVehInfo, false);
	CVehicle* cveh = getVehicleCVehicle(pVehInfo);
	eVehicleType vehType = Vehicles::getVehicleType(cveh);
	if (vehType == eVehicleType::CAutomobile)
	{
		return !(*(byte*)cveh->GetMemoryValue(0x0961));
	}
	else
	{
		float zCoord = GAME->GetWorld()->FindGroundZFor3DPosition(cveh->GetPosition());
		return zCoord > lim;
	}
}
bool Vehicles::isVehicleHavePassengers(vehicle_info* vehInfo)
{
	for (int i = 0; i < vehInfo->m_nMaxPassengers; i++)
		if (vehInfo->passengers[i] != nullptr)
			return true;
	return false;
}
int Vehicles::getVehicleFreeSeat(vehicle_info* pVehicleInfo)
{
	for (int i = 0; i < pVehicleInfo->m_nMaxPassengers; i++)
	{
		if (pVehicleInfo->passengers[i] == nullptr)
			return i;
	}
	return -1;
}
std::string Vehicles::getVehicleNameByModel(int model_alt_id)
{
	return Stuff::VehiclesNames[model_alt_id - 400];
}
std::vector<NearVehicle> Vehicles::getNearestVehicles(bool bInvert)
{
	/*

	std::vector<NearVehicle> vehicles;

	for (handle i = 0; i < Stuff::getVehiclesPool()->size; i++)
	{
		vehicle_info* pVehInfo = vehicleInfoGet_(i, 0);
		if (!pVehInfo)
			continue;
		float vehicleCoords[3] = { pVehInfo->base.matrix[4 * 3],
								  pVehInfo->base.matrix[4 * 3 + 1],
								  pVehInfo->base.matrix[4 * 3 + 2] };
		float distTovehicle = Stuff::getDistanceBetween(PEDSELF->GetPosition(), CVector(vehicleCoords[0], vehicleCoords[1], vehicleCoords[2]));
		sampid id = SobFuncs::getSAMPVehicleIDFromGTAVehicle(pVehInfo);
		if (id == -1)
			continue;
		vehicles.push_back({ id ,pVehInfo,distTovehicle });
	}

	if (bInvert)
		std::sort(vehicles.begin(), vehicles.end(), [](const NearVehicle &a, const NearVehicle &b) {
		return (a.fDistance > b.fDistance);
	});
	else
		std::sort(vehicles.begin(), vehicles.end(), [](const NearVehicle &a, const NearVehicle &b) {
		return (a.fDistance < b.fDistance);
	});
	return vehicles;
	  */
	std::vector<NearVehicle> vehicles;

	for (sampid i = 0; i < SAMP_MAX_VEHICLES; i++)
	{
		vehicle_info* pVehInfo = SAMPSobeit::getGTAVehicleFromSAMPVehicleID(i);
		if (!pVehInfo)
			continue;
		float vehicleCoords[3] = { pVehInfo->base.matrix[4 * 3],
								  pVehInfo->base.matrix[4 * 3 + 1],
								  pVehInfo->base.matrix[4 * 3 + 2] };
		float distTovehicle = Stuff::getDistanceBetween(PEDSELF->GetPosition(), CVector(vehicleCoords[0], vehicleCoords[1], vehicleCoords[2]));
		vehicles.push_back({ i ,pVehInfo,distTovehicle });
	}

	if (bInvert)
		std::sort(vehicles.begin(), vehicles.end(), [](const NearVehicle& a, const NearVehicle& b) {
		return (a.fDistance > b.fDistance);
			});
	else
		std::sort(vehicles.begin(), vehicles.end(), [](const NearVehicle& a, const NearVehicle& b) {
		return (a.fDistance < b.fDistance);
			});
	return vehicles;

}
sampid Vehicles::getVehicleID(vehicle_info* pVehInfo)
{
	CHECK_VALID(pVehInfo, -1);
	return SF->getSAMP()->getVehicles()->GetSAMPVehicleIDFromGTAHandle(GAME->GetPools()->GetVehicleRef(GAME->GetPools()->GetVehicle((DWORD*)pVehInfo)));
}
bool Players::isInValid(sampid sampID)
{
	return (sampID < 0 || sampID > 1000);
}
bool Players::isLocal(sampid sampID)
{
	return (sampID == ACTOR_SELF || sampID == SF->getSAMP()->getPlayers()->sLocalPlayerID);
}
bool Players::isPlayerExist(sampid sampID)
{
	if (isInValid(sampID))
		return false;
	if (isLocal(sampID))
		return false;
	if (SF->getSAMP()->getPlayers()->iIsListed[sampID] != 1 || SF->getSAMP()->getPlayers()->pRemotePlayer[sampID] == nullptr || SF->getSAMP()->getPlayers()->pRemotePlayer[sampID]->pPlayerData == nullptr || SF->getSAMP()->getPlayers()->pRemotePlayer[sampID]->pPlayerData->pSAMP_Actor == nullptr || SF->getSAMP()->getPlayers()->pRemotePlayer[sampID]->pPlayerData->pSAMP_Actor->pGTA_Ped == nullptr)
		return false;
	return true;
}
bool Players::isLocalPlayerExist()
{
	if (SF->getSAMP()->getPlayers()->pLocalPlayer == nullptr || SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor == nullptr || SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped == nullptr)
		return false;
	return true;
}
bool Players::isPlayerInCar(actor_info* pActorInfo)
{
	CHECK_VALID(pActorInfo, false);
	return pActorInfo->state == 50;
}
bool Players::isLocalPlayerInCar()
{
	return SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->state == 50;
}
bool Players::isPlayerDriver(actor_info* pActorInfo)
{
	if (!isPlayerInCar(pActorInfo))
		return false;
	return pActorInfo->vehicle->passengers[0] == pActorInfo;
}

bool Players::isLocalPlayerDrivingCar(vehicle_info* veh)
{
	CHECK_VALID(veh, false);
	return veh->passengers[0] == SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped;
}

bool Players::isLocalPlayerDriver()
{
	auto pVehicleInfo = vehicleInfoGet_(VEHICLE_SELF, 0);
	CHECK_VALID(pVehicleInfo, false);
	return pVehicleInfo->passengers[0] == SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped;
}

int Players::getLocalPlayerCarID()
{
	auto pVehInfo = vehicleInfoGet_(VEHICLE_SELF, 0);
	CHECK_VALID(pVehInfo, -1);
	return SF->getSAMP()->getVehicles()->GetSAMPVehicleIDFromGTAHandle(GAME->GetPools()->GetVehicleRef(GAME->GetPools()->GetVehicle((DWORD*)pVehInfo)));
}
actor_info* Players::getPlayerInfo(sampid id, bool checkExist)
{
	if (id == ACTOR_SELF)
		return SF->getGame()->actorInfoGet(VEHICLE_SELF, 0);
	if (checkExist)
	{
		if (!Players::isPlayerExist(id))
			return nullptr;
	}

	return SF->getGame()->actorInfoGet(SAMPSobeit::getPedGTAScriptingIDFromPlayerID(id), 0);

}

std::vector<NearPlayer> Players::getNearestToCrosshairPlayers(bool bCheckLineOfSight)
{
	static SLineOfSightFlags lineOfSightFlags;
	lineOfSightFlags.bCheckBuildings = true;
	lineOfSightFlags.bCheckObjects = true;
	lineOfSightFlags.bCheckPeds = false;
	lineOfSightFlags.bCheckVehicles = true;
	lineOfSightFlags.bCheckCarTires = true;

	std::vector<NearPlayer> players;
	actor_info* pSelf = actorInfoGet_(-1, 0);
	for (handle i = 0; i < Stuff::getActorsPool()->size; i++)
	{
		actor_info* pActorInfo = actorInfoGet_(i, 0);
		if (!pActorInfo)
			continue;
		if (pSelf == pActorInfo)
			continue;
		D3DXVECTOR3 vecPos;
		vecPos.x = pActorInfo->base.matrix[12];
		vecPos.y = pActorInfo->base.matrix[13];
		vecPos.z = pActorInfo->base.matrix[14];

		D3DXVECTOR3 screenPos;
		D3D::CalcScreenCoords(&vecPos, &screenPos);
		if (screenPos.z < 1.f)
			continue;
		CMatrix matrix;
		GAME->GetCamera()->GetMatrix(&matrix);
		if (bCheckLineOfSight)
			if (!GAME->GetWorld()->IsLineOfSightClear(&matrix.vPos, Lippets::LUtils::getRValueObjectPtr(CVector(vecPos.x, vecPos.y, vecPos.z)), lineOfSightFlags))
				continue;
		float fRadius = Stuff::getDistanceBetween2d(CVector2D(screenPos.x, screenPos.y), CVector2D(cshX, cshY));
		sampid id = SAMPSobeit::getSAMPPlayerIDFromGTAPed(pActorInfo);
		if (id == -1)
			continue;
		players.push_back({ id,pActorInfo,fRadius });
	}
	std::sort(players.begin(), players.end(), [](const NearPlayer& a, const NearPlayer& b) {
		return (a.fDistance < b.fDistance);
		});
	return players;
}


std::vector<NearPlayer> Players::getNearestPlayers(bool bInvert)
{

	/*
	std::vector<NearPlayer> players;
	actor_info* pSelf = actorInfoGet_(-1, 0);
	for (handle i = 0; i < Stuff::getActorsPool()->size; i++)
	{
		actor_info* pActorInfo = actorInfoGet_(i, 0);
		if (!pActorInfo)
			continue;
		if (pSelf == pActorInfo)
			continue;

		float distToPlayer = Stuff::getDistanceBetween(PEDSELF->GetPosition(), CVector(pActorInfo->base.coords[0], pActorInfo->base.coords[1], pActorInfo->base.coords[2]));
		sampid id = SobFuncs::getSAMPPlayerIDFromGTAPed(pActorInfo);
		if (id == -1)
			continue;
		players.push_back({ id,pActorInfo,distToPlayer });
	}

	if (bInvert)
		std::sort(players.begin(), players.end(), [](const NearPlayer& a, const NearPlayer&b) {
		return (a.fDistance > b.fDistance);
	});
	else
		std::sort(players.begin(), players.end(), [](const NearPlayer& a, const NearPlayer& b) {
		return (a.fDistance < b.fDistance);
	});

	return players;
	  */
	std::vector<NearPlayer> players;
	for (sampid i = 0; i < SAMP_MAX_ACTORS; i++)
	{
		if (i == SF->getSAMP()->getPlayers()->sLocalPlayerID)
			continue;
		actor_info* pActorInfo = SAMPSobeit::getGTAPedFromSAMPPlayerID(i);
		if (!pActorInfo)
			continue;
		float distToPlayer = Stuff::getDistanceBetween(PEDSELF->GetPosition(), CVector(pActorInfo->base.matrix[4 * 3], pActorInfo->base.matrix[4 * 3 + 1], pActorInfo->base.matrix[4 * 3 + 2]));
		players.push_back({ i,pActorInfo,distToPlayer });
	}

	if (bInvert)
		std::sort(players.begin(), players.end(), [](const NearPlayer& a, const NearPlayer& b) {
		return (a.fDistance > b.fDistance);
			});
	else
		std::sort(players.begin(), players.end(), [](const NearPlayer& a, const NearPlayer& b) {
		return (a.fDistance < b.fDistance);
			});

	return players;

}
CVector2D Players::getBonePosOnScreen(CPed* ped, eBone bone)
{
	CVector returnValue;
	CVector bonePosition;
	ped->GetBonePosition(bone, &bonePosition);
	D3D::CalcScreenCoords(&bonePosition, &returnValue);
	return CVector2D(returnValue.fX, returnValue.fY);
}


bool Pools::isObjectExist(int id)
{
	if (!SF->getSAMP()->getInfo()->pPools->pObject->IsObjectExists(id))
		return false;
	object_info* pObject = SF->getSAMP()->getInfo()->pPools->pObject->object[id]->pGTAEntity;
	return pObject != nullptr;
	return (SF->getSAMP()->getInfo()->pPools->pObject->IsObjectExists(id) &&
		SF->getSAMP()->getInfo()->pPools->pObject->iIsListed[id] == 1 &&
		SF->getSAMP()->getInfo()->pPools->pObject->object[id] != nullptr &&
		SF->getSAMP()->getInfo()->pPools->pObject->object[id]->pGTAEntity != nullptr);
}
bool Pools::isPickupExist(int id)
{
	return (SF->getSAMP()->getInfo()->pPools->pPickup->IsPickupExists(id) &&
		SF->getSAMP()->getInfo()->pPools->pPickup->GetPickupHandleByID(id));
}
bool Pools::is3DTextExist(int id)
{
	static stTextLabel textLabel;
	return SF->getSAMP()->getInfo()->pPools->pText3D->Get3DTextInfo(id, textLabel);
}

bool Pools::IsPickOnScreen(int p)
{

	D3DXVECTOR3 vecPos;
	vecPos.x = SF->getSAMP()->getInfo()->pPools->pPickup->pickup[p].fPosition[0];
	vecPos.y = SF->getSAMP()->getInfo()->pPools->pPickup->pickup[p].fPosition[1];
	vecPos.z = SF->getSAMP()->getInfo()->pPools->pPickup->pickup[p].fPosition[2];

	D3DXVECTOR3 screenPos;
	D3D::CalcScreenCoords(&vecPos, &screenPos);
	if (screenPos.z < 1.f)
		return false;
	return true;
}

bool Pools::IsObjOnScreen(int p)
{
	D3DXVECTOR3 vecPos;
	vecPos.x = SF->getSAMP()->getInfo()->pPools->pObject->object[p]->pGTAEntity->base.matrix[4 * 3];
	vecPos.y = SF->getSAMP()->getInfo()->pPools->pObject->object[p]->pGTAEntity->base.matrix[4 * 3 + 1];
	vecPos.z = SF->getSAMP()->getInfo()->pPools->pObject->object[p]->pGTAEntity->base.matrix[4 * 3 + 2];

	D3DXVECTOR3 screenPos;
	D3D::CalcScreenCoords(&vecPos, &screenPos);
	if (screenPos.z < 1.f)
		return false;
	return true;
}

bool Pools::Is3dTOnScreen(int p)
{
	D3DXVECTOR3 vecPos;
	vecPos.x = SF->getSAMP()->getInfo()->pPools->pText3D->textLabel[p].fPosition[0];
	vecPos.y = SF->getSAMP()->getInfo()->pPools->pText3D->textLabel[p].fPosition[1];
	vecPos.z = SF->getSAMP()->getInfo()->pPools->pText3D->textLabel[p].fPosition[2];

	D3DXVECTOR3 screenPos;
	D3D::CalcScreenCoords(&vecPos, &screenPos);
	if (screenPos.z < 1.f)
		return false;
	return true;
}
void RPC_emulating::setVehicleZAngle(UINT16 wVehicleID, float Angle)
{
	BitStream bs;
	bs.Write(wVehicleID);
	bs.Write(Angle);
	SF->getRakNet()->emulateRecvRPC(160, &bs);
}

void RPC_emulating::setskin(uint32_t player_id, uint32_t skin_id)
{
	BitStream bsClass;
	bsClass.Write(uint32_t(player_id));
	bsClass.Write(uint32_t(skin_id));
	SF->getRakNet()->emulateRecvRPC(153, &bsClass);
}
void RPC_emulating::giveweapon(uint32_t weapon_id, uint32_t ammo)
{
	BitStream bsClass;
	bsClass.Write(uint32_t(weapon_id)); // WeaponID
	bsClass.Write(uint32_t(ammo));      // Ammo
	SF->getRakNet()->emulateRecvRPC(22, &bsClass);
}

void RPC_emulating::setPlayerFightStyle(UINT16 wPlayerID, UINT8 fightstyle)
{
	BitStream bsClass;
	bsClass.Write(wPlayerID); // WeaponID
	bsClass.Write(fightstyle);      // Ammo
	SF->getRakNet()->emulateRecvRPC(89, &bsClass);
}
void RPC_emulating::clearActorAnimation(UINT16 wActorID)
{
	BitStream bsClass;
	bsClass.Write(wActorID);
	SF->getRakNet()->emulateRecvRPC(174, &bsClass);
}

Stuff::pool*& Stuff::getActorsPool()
{
	static pool* pool_actor;
	return pool_actor;
}
Stuff::pool*& Stuff::getVehiclesPool()
{
	static pool* pool_vehicle;
	return pool_vehicle;
}

void SampSnipps::setup()
{
	static bool bWasInitialized = false;
	if (bWasInitialized)
		return;
	/* setup & refresh actor pool */
	Stuff::getActorsPool() = *(Stuff::pool**)ACTOR_POOL_POINTER;
	if (Stuff::getActorsPool() == nullptr || Stuff::getActorsPool()->start == nullptr || Stuff::getActorsPool()->size <= 0)
		return;

	/* setup & refresh vehicle pool */
	Stuff::getVehiclesPool() = *(Stuff::pool**)VEHICLE_POOL_POINTER;
	if (Stuff::getVehiclesPool == nullptr || Stuff::getVehiclesPool()->start == nullptr || Stuff::getVehiclesPool()->size <= 0)
		return;
	bWasInitialized = true;
}