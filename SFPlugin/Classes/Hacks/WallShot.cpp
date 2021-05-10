#include "WallShot.h"

void EnableWallShot(bool bEnable)
{

	if (bEnable) {
		WriteMem<byte>(0x00740701, 1, false, true);
		WriteMem<byte>(0x00740703, 1, false, true);
		WriteMem<byte>(0x00740709, 1, false, true);

		WriteMem<byte>(0x00740B49, 1, false, true);
		WriteMem<byte>(0x00740B4B, 1, false, true);
		WriteMem<byte>(0x00740B51, 1, false, true);

		WriteMem<byte>(0x0073620D, 1, false, true);
		WriteMem<byte>(0x0073620F, 1, false, true);
		WriteMem<byte>(0x00736215, 1, false, true);
	}
	else {
		WriteMem<byte>(0x00740701, 1, true, true);
		WriteMem<byte>(0x00740703, 1, true, true);
		WriteMem<byte>(0x00740709, 1, true, true);

		WriteMem<byte>(0x00740B49, 1, true, true);
		WriteMem<byte>(0x00740B4B, 1, true, true);
		WriteMem<byte>(0x00740B51, 1, true, true);

		WriteMem<byte>(0x0073620D, 1, true, true);
		WriteMem<byte>(0x0073620F, 1, true, true);
		WriteMem<byte>(0x00736215, 1, true, true);
	}
}

WallShot::WallShot(const char* m_sHackName)
{
	this->m_sHackName = m_sHackName;
}

void WallShot::switchHack()
{
	EnableWallShot(m_bEnabled);
}

void WallShot::onDrawGUI()
{
	if (ImGui::Checkbox("Wall Shot", &m_bEnabled))
		switchHack();
}

void WallShot::save(nlohmann::json& data)
{
	data[m_sHackName] = m_bEnabled;
}

void WallShot::read(nlohmann::json& data)
{
	m_bEnabled = data[m_sHackName].get<bool>();
}