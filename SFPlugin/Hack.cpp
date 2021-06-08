#include "Hack.h"

bool crTickLocalPlayerInfo::isInCar()
{
	return _isInCar && pLocalVeh;
}
bool crTickLocalPlayerInfo::isDriver()
{
	return _isDriver && pLocalVeh;
}

