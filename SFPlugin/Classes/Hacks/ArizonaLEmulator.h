#include "Hack.h"


HACK_CLASS(ArizonaLEmulator)
{
public:
	ArizonaLEmulator(const char* name);
private:
	OVERRIDE_SAVE_READ;
	OVERRIDE_RPC_OUT;
	OVERRIDE_DRAWGUI;
};