#include "Hack.h"

HACK_CLASS(CollisionHack)
{
public:
	CollisionHack(const char*);
	bool m_bIsVehicleCollisionEnabled = false;
	bool m_bIsPedsCollisionEnabled = false;
	bool m_bIsObjectsCollisionEnabled = false;
	bool m_bIsBuildingsCollisionEnabled = false;
private:
	BYTE patch[6];

	void release() override;
	void init() override;
	void onDrawGUI() override;
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;

};