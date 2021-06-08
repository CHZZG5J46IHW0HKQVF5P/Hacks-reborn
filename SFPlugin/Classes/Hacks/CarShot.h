#include "Hack.h"

HACK_CLASS(CarShot)
{
public:
	CarShot(const char*);
	float m_fForce = 5.f;
	
	OVERRIDE_DRAWGUI;
	OVERRIDE_PACKET_OUT;
	OVERRIDE_SAVE_READ;
};