#pragma once
#include "Files\Strings.h"
#include "d3d9.h"
#include "SAMPFUNCS_API.h"
#include "game_api.h"

#include "SampSnipps/cheat_funcs.h"
#include "SampSnipps/GTAfuncs.h"
#include "SampSnipps/samp.h"

#define iScrResX *(int *)0xC9C040
#define iScrResY *(int *)0xC9C044
#define cshX iScrResX * 0.5299999714f
#define cshY iScrResY * 0.4f

#define cm_ SF->getSAMP()->getChat()->AddChatMessage

#define CHECK_VALID(x,ret) if (!(x)) return (ret);

#define ACTOR_POOL_POINTER		0x00B74490
#define ACTOR_POINTER_SELF		0x00B7CD98
#define VEHICLE_POOL_POINTER	0x00B74494
#define VEHICLE_POINTER_SELF	0x00B6F980
#define OBJECT_POOL_POINTER		0x00B7449C
#define BUILDING_POOL_POINTER	0x00B74498

#define vehicleInfoGet_(id,flags)  SF->getGame()->vehicleInfoGet(id,flags)
#define actorInfoGet_(id,flags)  SF->getGame()->actorInfoGet(id,flags)

typedef int sampid;
typedef int handle;

namespace D3D
{
	void CalcScreenCoords(const CVector *vecWorld, CVector *vecScreen);
	void CalcScreenCoords(D3DXVECTOR3 *vecWorld, D3DXVECTOR3 *vecScreen);
	bool isCoordsOnScreen(const CVector &vecWorld);
}
namespace Stuff
{

	struct pool
	{
#pragma pack( 1 )
		void	*start;		/* pointer to start of pool */
		void	*__end;		/* end of this structure? (not the pool) */
		int32_t size;		/* max number of items in the pool */
		/* there's some more junk after this */
	};
	pool*& getActorsPool();
	pool*& getVehiclesPool();
	static const char *WeaponsNames[] =
	{
		{"Fist"},
		{"Brass Knuckles"},
		{"Golf Club"},
		{"Nitestick"},
		{"Knife"},
		{"Baseball Bat"},
		{"Shovel"},
		{"Pool Cue"},
		{"Katana"},
		{"Chainsaw"},
		{"Dildo 1"},
		{"Dildo 2"},
		{"Vibe 1"},
		{"Vibe 2"},
		{"Flowers"},
		{"Cane"},
		{"Grenade"},
		{"Teargas"},
		{"Molotov Cocktail"},
		{"NULL"},
		{"NULL"},
		{"NULL"},
		{"Pistol"},
		{"Silenced Pistol"},
		{"Desert Eagle"},
		{"Shotgun"},
		{"Sawn-Off Shotgun"},
		{"SPAZ12"},
		{"Micro UZI"},
		{"MP5"},
		{"AK47"},
		{"M4"},
		{"Tech9"},
		{"Country Rifle"},
		{"Sniper Rifle"},
		{"Rocket Launcher"},
		{"Heat Seeking RPG"},
		{"Flame Thrower"},
		{"Minigun"},
		{"Remote Explosives"},
		{"Detonator"},
		{"Spray Can"},
		{"Fire Extinguisher"},
		{"Camera"},
		{"NV Goggles"},
		{"IR Goggles"},
		{"Parachute"} };
	static const char *VehiclesNames[] = {
		{"Landstalker"},
		{"Bravura"},
		{"Buffalo"},
		{"Linerunner"},
		{"Perrenial"},
		{"Sentinel"},
		{"Dumper"},
		{"Firetruck"},
		{"Trashmaster"},
		{"Stretch"},
		{"Manana"},
		{"Infernus"},
		{"Voodoo"},
		{"Pony"},
		{"Mule"},
		{"Cheetah"},
		{"Ambulance"},
		{"Leviathan"},
		{"Moonbeam"},
		{"Esperanto"},
		{"Taxi"},
		{"Washington"},
		{"Bobcat"},
		{"MrWhoopee"},
		{"BFInjection"},
		{"Hunter"},
		{"Premier"},
		{"Enforcer"},
		{"Securicar"},
		{"Banshee"},
		{"Predator"},
		{"Bus"},
		{"Rhino"},
		{"Barracks"},
		{"Hotknife"},
		{"Trailer1"},
		{"Previon"},
		{"Coach"},
		{"Cabbie"},
		{"Stallion"},
		{"Rumpo"},
		{"RCBandit"},
		{"Romero"},
		{"Packer"},
		{"Monster"},
		{"Admiral"},
		{"Squalo"},
		{"Seasparrow"},
		{"Pizzaboy"},
		{"Tram"},
		{"Trailer2"},
		{"Turismo"},
		{"Speeder"},
		{"Reefer"},
		{"Tropic"},
		{"Flatbed"},
		{"Yankee"},
		{"Caddy"},
		{"Solair"},
		{"BerkleyRCVan"},
		{"Skimmer"},
		{"PCJ-600"},
		{"Faggio"},
		{"Freeway"},
		{"RCBaron"},
		{"RCRaider"},
		{"Glendale"},
		{"Oceanic"},
		{"Sanchez"},
		{"Sparrow"},
		{"Patriot"},
		{"Quad"},
		{"Coastguard"},
		{"Dinghy"},
		{"Hermes"},
		{"Sabre"},
		{"Rustler"},
		{"ZR-350"},
		{"Walton"},
		{"Regina"},
		{"Comet"},
		{"BMX"},
		{"Burrito"},
		{"Camper"},
		{"Marquis"},
		{"Baggage"},
		{"Dozer"},
		{"Maverick"},
		{"NewsChopper"},
		{"Rancher"},
		{"FBIRancher"},
		{"Virgo"},
		{"Greenwood"},
		{"Jetmax"},
		{"Hotring"},
		{"Sandking"},
		{"Blista Compact"},
		{"Police Maverick"},
		{"Boxville"},
		{"Benson"},
		{"Mesa"},
		{"RCGoblin"},
		{"HotringRacer A"},
		{"HotringRacer B"},
		{"BloodringBanger"},
		{"Rancher"},
		{"SuperGT"},
		{"Elegant"},
		{"Journey"},
		{"Bike"},
		{"MountainBike"},
		{"Beagle"},
		{"Cropdust"},
		{"Stunt"},
		{"Tanker"},
		{"Roadtrain"},
		{"Nebula"},
		{"Majestic"},
		{"Buccaneer"},
		{"Shamal"},
		{"Hydra"},
		{"FCR-900"},
		{"NRG-500"},
		{"HPV1000"},
		{"CementTruck"},
		{"TowTruck"},
		{"Fortune"},
		{"Cadrona"},
		{"FBITruck"},
		{"Willard"},
		{"Forklift"},
		{"Tractor"},
		{"Combine"},
		{"Feltzer"},
		{"Remington"},
		{"Slamvan"},
		{"Blade"},
		{"Freight"},
		{"Streak"},
		{"Vortex"},
		{"Vincent"},
		{"Bullet"},
		{"Clover"},
		{"Sadler"},
		{"FiretruckLA"},
		{"Hustler"},
		{"Intruder"},
		{"Primo"},
		{"Cargobob"},
		{"Tampa"},
		{"Sunrise"},
		{"Merit"},
		{"Utility"},
		{"Nevada"},
		{"Yosemite"},
		{"Windsor"},
		{"MonsterA"},
		{"MonsterB"},
		{"Uranus"},
		{"Jester"},
		{"Sultan"},
		{"Stratum"},
		{"Elegy"},
		{"Raindance"},
		{"RC Tiger"},
		{"Flash"},
		{"Tahoma"},
		{"Savanna"},
		{"Bandito"},
		{"FreightFlat"},
		{"StreakCarriage"},
		{"Kart"},
		{"Mower"},
		{"Duneride"},
		{"Sweeper"},
		{"Broadway"},
		{"Tornado"},
		{"AT-400"},
		{"DFT-30"},
		{"Huntley"},
		{"Stafford"},
		{"BF-400"},
		{"Newsvan"},
		{"Tug"},
		{"Trailer 3"},
		{"Emperor"},
		{"Wayfarer"},
		{"Euros"},
		{"Hotdog"},
		{"Club"},
		{"FreightCarriage"},
		{"Trailer3"},
		{"Andromada"},
		{"Dodo"},
		{"RCCam"},
		{"Launch"},
		{"PoliceCar(LSPD)"},
		{"PoliceCar(SFPD)"},
		{"PoliceCar(LVPD)"},
		{"PoliceRanger"},
		{"Picador"},
		{"S.W.A.T.Van"},
		{"Alpha"},
		{"Phoenix"},
		{"Glendale"},
		{"Sadler"},
		{"LuggageTrailerA"},
		{"LuggageTrailerB"},
		{"StairTrailer"},
		{"Boxville"},
		{"FarmPlow"},
		{"UtilityTrailer"} };
	float getDistanceBetween(const CVector *pos1, const CVector &pos2);
	float getDistanceBetween2d(const CVector2D &vec1, const CVector2D &vec2);
	void AddMessageJumpQ(const std::string& text, unsigned int time = 1000, unsigned short flag = 0, bool bPreviousBrief = 0);
	int isModelLoaded(int iModelID);
	bool TestCheat(const char *cheat);
}

namespace Vehicles
{
	enum class eVehicleType
	{
		NONE = -1,
		CAutomobile,
		CMtruck,
		CQuad,
		CHeli,
		CPlane,
		CBoat,
		CTrain,
		CFHeli,
		CFPlane,
		CBike,
		CBMX,
		CTrailer
	};
	struct NearVehicle
	{
		sampid id;
		vehicle_info* pVehInfo;
		float fDistance;
	};
	int getVehicleFreeSeat(vehicle_info* pVehicleInfo);
	bool isInValid(sampid sampID);
	bool isVehicleExist(sampid sampID);
	CVehicle *getVehicleCVehicle(vehicle_info *vehInfo);
	bool isVehicleInAir(float lim, vehicle_info*);
	bool isVehicleHavePassengers(vehicle_info *vehInfo);
	std::string getVehicleNameByModel(int model_alt_id);
	std::vector<NearVehicle> getNearestVehicles(bool bInvert = false);
	sampid getVehicleID(vehicle_info* pVehInfo);
	eVehicleType getVehicleType(CVehicle *cveh);

}

namespace Players
{
	struct NearPlayer
	{
		sampid id;
		actor_info* pActorInfo;
		float fDistance;
	};
	bool isInValid(sampid sampID);
	bool isLocal(sampid sampID);
	bool isPlayerExist(sampid sampID);
	bool isLocalPlayerExist();
	bool isPlayerInCar(actor_info* pInfo);
	bool isLocalPlayerInCar();
	bool isPlayerDriver(actor_info* pActorInfo);
	bool isLocalPlayerDriver();
	int getLocalPlayerCarID();
	bool isLocalPlayerDrivingCar(vehicle_info*);
	actor_info* getPlayerInfo(sampid id, bool checkExist = true);
	std::vector<NearPlayer> getNearestToCrosshairPlayers(bool bCheckLineOfSight = true);
	std::vector<NearPlayer> getNearestPlayers(bool bInvert = false);
	CVector2D getBonePosOnScreen(CPed *ped, eBone bone);
}

namespace Pools // refactor this ->
{
	bool isObjectExist(sampid id);
	bool isPickupExist(sampid id);
	bool is3DTextExist(sampid id);
	bool IsPickOnScreen(sampid p);
	bool IsObjOnScreen(sampid p);
	bool Is3dTOnScreen(sampid p);
}
namespace RPC_emulating
{
	void setVehicleZAngle(UINT16 wVehicleID, float Angle);
	void setskin(uint32_t player_id, uint32_t skin_id);
	void giveweapon(uint32_t weapon_id, uint32_t ammo);
	void setPlayerFightStyle(UINT16 wPlayerID, UINT8 fightstyle);
	void clearActorAnimation(UINT16 wActorID);
}

namespace SampSnipps
{
	void setup();
}


using Vehicles::eVehicleType;
using Vehicles::NearVehicle;
using Players::NearPlayer;