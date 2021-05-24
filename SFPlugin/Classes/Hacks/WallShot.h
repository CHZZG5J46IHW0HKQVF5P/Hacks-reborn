#include "Hack.h"


HACK_CLASS(WallShot)
{
public:
	WallShot(const char* name);
private:
	void save(nlohmann::json& data) override;
	void read(nlohmann::json& data) override;
	void switchHack() override;
	void onDrawGUI() override;
};