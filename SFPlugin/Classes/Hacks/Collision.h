#pragma once
#include "Hack.h"

HACK_CLASS(CollisionHack)
{
public:
	CollisionHack(const char*);
	bool m_bIsVehicleCollisionEnabled = false;
	bool m_bIsPedsCollisionEnabled = false;
	bool m_bIsObjectsCollisionEnabled = false;
	bool m_bIsBuildingsCollisionEnabled = false;
private:
	BYTE patch[6];

	OVERRIDE_RELEASE;
	OVERRIDE_INIT;
	OVERRIDE_DRAWGUI;
	OVERRIDE_SAVE_READ;

};