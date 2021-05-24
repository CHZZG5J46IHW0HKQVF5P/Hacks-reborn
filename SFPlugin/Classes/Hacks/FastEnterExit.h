#include "Hack.h"

HACK_CLASS(FastEnterExit)
{
public:
	FastEnterExit(const char*);	
	float m_fVehicleDistanceLimit = 0.f;
private:
	void onDrawGUI() override;
	bool onWndProc(WPARAM, UINT) override;
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;
};