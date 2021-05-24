#include "GlobalFuncs.h"

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



