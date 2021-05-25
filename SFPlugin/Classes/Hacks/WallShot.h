#include "Hack.h"


HACK_CLASS(WallShot)
{
public:
	WallShot(const char* name);
private:
	OVERRIDE_SAVE_READ;
	void switchHack() override;
	void onDrawGUI() override;
};