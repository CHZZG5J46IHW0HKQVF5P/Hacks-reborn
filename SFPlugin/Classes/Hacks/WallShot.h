#include "Hack.h"


class WallShot : public IHack
{
public:
	WallShot(const char* name);
private:
	void save(nlohmann::json& data) override;
	void read(nlohmann::json& data) override;
	void switchHack() override;
	void onDrawGUI() override;
};