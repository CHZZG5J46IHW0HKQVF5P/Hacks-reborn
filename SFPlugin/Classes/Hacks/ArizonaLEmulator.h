#include "Hack.h"


HACK_CLASS(ArizonaLEmulator)
{
public:
	ArizonaLEmulator(const char* name);
private:
	OVERRIDE_SAVE_READ;
	bool onRPCOutcoming(stRakNetHookParams*  ) override;
	void onDrawGUI() override;
};