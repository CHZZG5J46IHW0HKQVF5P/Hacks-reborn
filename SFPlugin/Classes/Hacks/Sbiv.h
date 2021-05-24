#include "Hack.h"

HACK_CLASS(Sbiv)
{
public:
	Sbiv(const char*);
	
	int m_nActivationKey = 0;

	void onDrawGUI() override;
	bool onWndProc(WPARAM, UINT) override;
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;
};