#include "VehicleGodMode.h"

DEFAULT_HACK_CONSTRUCTOR(VehicleGodMode)


void VehicleGodMode::onDrawGUI()
{

	ImGui::Checkbox("Vehicle God Mode", &m_bEnabled);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(m_nActivationKey, g::keyButtonSplitter);
}

void VehicleGodMode::enableVehGodMode(bool bEnable)
{
	if (bEnable)
	{
		vehicle_info* pVehicleInfo = vehicle_info_get(-1, 0);
		if (pVehicleInfo)
			pVehicleInfo->flags = (1 | 1 | 1 | 1 | 1);

	}
	else
	{
		vehicle_info* pVehicleInfo = vehicle_info_get(-1, 0);
		if (pVehicleInfo)
			pVehicleInfo->flags = (0 | 0 | 0 | 0 | 0);

	}

}

bool VehicleGodMode::onWndProc()
{
	if (g::pKeyEventInfo->iKeyID != m_nActivationKey)
		return true;

	enableVehGodMode(g::pKeyEventInfo->bDown);

}

void VehicleGodMode::save(nlohmann::json &data)
{
	SERIALIZE_FIELD_JSON(m_bEnabled);
	SERIALIZE_FIELD_JSON(m_nActivationKey);
}

void VehicleGodMode::read(nlohmann::json &data)
{
	DESERIALIZE_FIELD_JSON(m_bEnabled);
	DESERIALIZE_FIELD_JSON(m_nActivationKey);
}
