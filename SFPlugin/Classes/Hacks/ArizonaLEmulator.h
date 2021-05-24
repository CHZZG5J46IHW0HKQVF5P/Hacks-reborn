#include "Hack.h"


HACK_CLASS(ArizonaLEmulator)
{
public:
	ArizonaLEmulator(const char* name);
private:
	void save(nlohmann::json& data) override;
	void read(nlohmann::json& data) override;
	bool onRPCOutcoming(stRakNetHookParams*  ) override;
	void onDrawGUI() override;
};