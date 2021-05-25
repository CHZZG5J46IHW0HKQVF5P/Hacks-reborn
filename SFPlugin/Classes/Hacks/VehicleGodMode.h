#include "Hack.h"

HACK_CLASS(VehicleGodMode)
{
public:
	VehicleGodMode(const char*);

	int m_nActivationKey = 0;

	OVERRIDE_WNDPROC;
	
	void onDrawGUI() override;

	OVERRIDE_SAVE_READ;
};