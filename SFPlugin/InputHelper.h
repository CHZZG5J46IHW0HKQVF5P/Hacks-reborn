#pragma once
#include "Hack.h"


class InputHelper : public IHack
{
public:
	InputHelper(const char* name)
	{
		hackName = name;
	}
private:
	CMFont font = CMFont("Chat Helper");
	void init() override
	{
		font.Init();
	}
	void drawGUI()	  override
	{
		ImGui::Checkbox(hackName.c_str(), &isEnable);
	}
	void drawHack(const crTickLocalPlayerInfo& info) override
	{
		if (!SF->getSAMP()->getInput()->iInputEnabled)
			return;
		char szBuffer[128];
		std::string LocaleName = Lippets::KeyBoard::GetKeyBoardLocaleName();
		if (info.isInCar)
			sprintf_s(szBuffer, "¬аш ID: {00FF00}%d{FFFFFF} ID јвто: {00FF00}%d{FFFFFF} язык: {00FF00}%s", MYID, SF->getSAMP()->getPlayers()->pLocalPlayer->sCurrentVehicleID, LocaleName.c_str());
		else
			sprintf_s(szBuffer, "¬аш ID: {00FF00}%d{FFFFFF} язык: {00FF00}%s", MYID, LocaleName.c_str());
		font.f->Print(szBuffer, 0xffffffff, SF->getSAMP()->getInput()->pDXUTEditBox->dwPosChatInput[0], SF->getSAMP()->getInput()->pDXUTEditBox->dwPosChatInput[1] + 45);

	}
	void drawSettings() override
	{
		if (ImGui::BeginMenu("Input Helper"))
		{
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
	void save(Json::Value& data) override
	{
		data[hackName] = isEnable;
		font.save(data);
	}
	void read(Json::Value& data)   override
	{
		isEnable = data[hackName].asBool();
		font.read(data);
	}

};