#include "Hack.h"

HACK_CLASS(VehicleGodMode)
{
public:
	VehicleGodMode(const char*);

	int m_nActivationKey = 0;

	static void enableVehGodMode(bool);

	OVERRIDE_WNDPROC;

	OVERRIDE_DRAWGUI;

	OVERRIDE_SAVE_READ;
};