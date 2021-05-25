#include "Hack.h"

HACK_CLASS(FastEnterExit)
{
public:
	FastEnterExit(const char*);	
	float m_fVehicleDistanceLimit = 0.f;
private:
	void onDrawGUI() override;
	OVERRIDE_WNDPROC;
	OVERRIDE_SAVE_READ;
};