#include "GlobalFuncs.h"


bool GFuncs::isHackWorking(const char* szHackName)
{
	auto&& hacks = HacksManager::getInstance()->getHacks();
	for (auto&& hack : *hacks)
	{
		auto&& pHack = std::get<IHack*>(hack);
		if (pHack->m_sHackName == szHackName)
			return pHack->isHackWorking();
	}



	return false;
}

void GFuncs::resortPlayersByDistance(std::vector<NearPlayer>* toSort, bool bInvert)
{
	if (bInvert)
		std::sort(toSort->begin(), toSort->end(), [](const NearPlayer& a, const NearPlayer&b) {
		return (a.fDistance > b.fDistance);
	});
	else
		std::sort(toSort->begin(), toSort->end(), [](const NearPlayer& a, const NearPlayer& b) {
		return (a.fDistance < b.fDistance);
	});
}

void GFuncs::resortVehiclesByDistance(std::vector<NearVehicle>* toSort, bool bInvert)
{
	if (bInvert)
		std::sort(toSort->begin(), toSort->end(), [](const NearVehicle &a, const NearVehicle &b) {
		return (a.fDistance > b.fDistance);
	});
	else
		std::sort(toSort->begin(), toSort->end(), [](const NearVehicle &a, const NearVehicle &b) {
		return (a.fDistance < b.fDistance);
	});
}



