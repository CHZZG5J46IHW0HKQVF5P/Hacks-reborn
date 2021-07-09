#include "Sbiv.h"

DEFAULT_HACK_CONSTRUCTOR(Sbiv)

void Sbiv::onDrawGUI()
{
	ImGui::Checkbox("Sbiv", &m_bEnabled);
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(m_nActivationKey, g::keyButtonSplitter);
}

bool Sbiv:: onWndProc()
{
	if (m_nActivationKey != 0 && g::pKeyEventInfo->iKeyID == m_nActivationKey)
		if (!g::pInfo->isDriver())
			if (g::pKeyEventInfo->bDown)
			{
				PEDSELF->SetMoveSpeed(&CVectorConstants::zerVec);
				GTAfunc_PerformAnimation("PED", "HANDSUP", 200, 0, 0,1, 0, 0, 0, 0);
			}
	return true;
}


void Sbiv::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON(m_bEnabled);
	DESERIALIZE_FIELD_JSON(m_nActivationKey);
}

void Sbiv::save(nlohmann::json& data)
{
	SERIALIZE_FIELD_JSON(m_bEnabled);
	SERIALIZE_FIELD_JSON(m_nActivationKey);
}