
#include "Hack.h"



HACK_CLASS(FPSController)
{
public:
	FPSController(const char*);
private:
	DWORD m_dwRTSSHookDllModuleAddres = 0;
	int  m_iIDLE_FPSLimit = 0;
	int  m_iInVehicle_FPSLimit = 0;
	int  m_iSwimming_FPSLimit = 0;
	OVERRIDE_EVERY_TICK;
	void onDrawGUI() override;
	OVERRIDE_SAVE_READ;
};
