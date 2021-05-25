#include "Hack.h"



HACK_CLASS(PlayersDescription)
{
public:
	PlayersDescription(const char*);

	float m_fNewDistance = 0.f;

	OVERRIDE_DRAWGUI;
	OVERRIDE_SAVE_READ;
	OVERRIDE_RPC_INC;
};