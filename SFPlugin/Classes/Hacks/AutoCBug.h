#include "Hack.h"

HACK_CLASS(AutoCBUG)
{
public:
	AutoCBUG(const char*);
	int m_iDelay = 15;
	OVERRIDE_DRAWGUI;
	OVERRIDE_SAVE_READ;
	OVERRIDE_EVERY_TICK;
};