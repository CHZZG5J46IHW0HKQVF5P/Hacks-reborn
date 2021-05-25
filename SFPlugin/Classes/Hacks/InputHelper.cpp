#include "InputHelper.h"


DEFAULT_HACK_CONSTRUCTOR(InputHelper)

void InputHelper::init()
{
	font.Init();
}
void InputHelper::onDrawGUI()
{
	ImGui::Checkbox(m_sHackName.c_str(), &m_bEnabled);
	if (ImGui::BeginPopupContextItem())
	{
		Lippets::ImGuiSnippets::BorderedInputInt("Y Offset", &offsetY, -500, 1000, 1, 1);
		Lippets::ImGuiSnippets::BorderedInputInt("X Offset", &offsetX, -500, 1000, 1, 1);
		if (ImGui::BeginMenu("Font"))
		{
			if (ImGui::InputText("Font###tagsFont", font.FontName, 64))
			{
				font.Release();
				font.Init();
			}
			if (ImGui::SliderInt("Font Size###tagsSize", &font.FontSize, 0, 24))
			{
				font.Release();
				font.Init();
			}
		}
		ImGui::EndPopup();
	}
}
void InputHelper::onDrawHack()
{
	if (!SF->getSAMP()->getInput()->iInputEnabled)
		return;
	char szBuffer[128];
	std::string LocaleName = Lippets::KeyBoard::GetKeyBoardLocaleName();
	if (g::pInfo->isInCar)
		sprintf_s(szBuffer, "¬аш ID: {00FF00}%d{FFFFFF} ID јвто: {00FF00}%d{FFFFFF} язык: {00FF00}%s", MYID, SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID, LocaleName.c_str());
	else
		sprintf_s(szBuffer, "¬аш ID: {00FF00}%d{FFFFFF} язык: {00FF00}%s", MYID, LocaleName.c_str());
	font.f->Print(szBuffer, 0xffffffff, SF->getSAMP()->getInput()->pDXUTEditBox->dwPosChatInput[0] + offsetX, SF->getSAMP()->getInput()->pDXUTEditBox->dwPosChatInput[1] + offsetY);
}

void InputHelper::save(nlohmann::json& data)
{
	SERIALIZE_FIELD_JSON(m_bEnabled);
	SERIALIZE_FIELD_JSON(offsetY);
	SERIALIZE_FIELD_JSON(offsetX);
	font.save(data);
}
void InputHelper::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON(m_bEnabled);

	DESERIALIZE_FIELD_JSON(offsetY);
	DESERIALIZE_FIELD_JSON(offsetX);
	font.read(data);
	ASSIGN_VAR_VALUE_IF_EQUALS_ZERO(offsetY, 45);
}