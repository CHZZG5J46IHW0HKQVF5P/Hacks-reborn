#include "Hack.h"


HACK_CLASS(WallShot)
{
public:
	WallShot(const char* name);
private:
	OVERRIDE_SAVE_READ;
	OVERRIDE_SWITCH_HACK;
	OVERRIDE_DRAWGUI;
};