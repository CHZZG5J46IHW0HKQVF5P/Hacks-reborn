#include "Hack.h"

enum class RUN_TYPE
{
	DEFAULT, //= -1
	CJ,//= 54
	ROLLER,//= 138
	SWAT //= 128
};

class CustomRun : public IHack
{
public:
	CustomRun(const char* szHackName);
private:
	RUN_TYPE m_CurrentRunType = RUN_TYPE::DEFAULT;
	void switchHack() override;
	void onDrawSettings() override;
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;
};