
#include "Hack.h"



HACK_CLASS(FPSController)
{
public:
	FPSController(const char*);
	DWORD m_dwRTSSHookDllModuleAddres = 0;
	int  m_iIDLE_FPSLimit = 0;
	int  m_iInVehicle_FPSLimit = 0;
	int  m_iSwimming_FPSLimit = 0;
	void Refresh(bool);
	OVERRIDE_EVERY_TICK;
	OVERRIDE_DRAWGUI;
	OVERRIDE_SAVE_READ;
};
