#include "InputHelper.h"


InputHelper::InputHelper(const char* name)
{
	m_sHackName = name;
}
void InputHelper::init()
{
	font.Init();
}
void InputHelper::onDrawGUI()
{
	ImGui::Checkbox(m_sHackName.c_str(), &m_bEnabled);
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
	return;
}
void InputHelper::onDrawSettings()
{
	if (ImGui::BeginMenu("Input Helper"))
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
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}
void InputHelper::save(nlohmann::json& data)
{
	data[m_sHackName] = m_bEnabled;
	data["offsetY"] = offsetY;
	data["offsetX"] = offsetX;
	font.save(data);
}
void InputHelper::read(nlohmann::json& data)
{
	m_bEnabled = data[m_sHackName].get<bool>();
	offsetY = data["offsetY"].get<int>();
	offsetX = data["offsetX"].get<int>();
	font.read(data);
	if (offsetY == 0)
		offsetY = 45;
}