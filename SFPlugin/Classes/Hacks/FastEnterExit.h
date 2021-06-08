#include "Hack.h"


HACK_CLASS(FastEnterExit)
{
	enum class Action
	{	   
		NONE,
		SET_AS_DRIVER,
		SET_AS_PASSANGER,
		REMOVE_FROM_VEHICLE
	};
public:
	FastEnterExit(const char*);	
	float m_fVehicleDistanceLimit = 0.f;
	int m_iDelay = 0;
	Action m_Action = Action::NONE;
	CMTimer m_ActionTimer;
private:
	OVERRIDE_EVERY_TICK;
	OVERRIDE_DRAWGUI
	OVERRIDE_WNDPROC;
	OVERRIDE_SAVE_READ;
};