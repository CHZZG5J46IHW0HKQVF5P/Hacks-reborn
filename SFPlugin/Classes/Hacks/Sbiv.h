#include "Hack.h"

HACK_CLASS(Sbiv)
{
public:
	Sbiv(const char*);
	
	int m_nActivationKey = 0;

	OVERRIDE_DRAWGUI;
	OVERRIDE_WNDPROC;
	OVERRIDE_SAVE_READ;
};