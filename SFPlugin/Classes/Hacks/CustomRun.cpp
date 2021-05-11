#include "CustomRun.h"
#include "nameof/nameof.hpp"


void setAnimGroupByRunType(RUN_TYPE runType)
{
	int iModelIndex = PEDSELF->GetModelIndex();
	switch (runType)
	{
	case RUN_TYPE::CJ:
	{
		RPC_emulating::setskin(MYID, 0);
		RPC_emulating::setskin(MYID, iModelIndex);
		*PEDSELF->GetMemoryValue(0x4D4) = 54;
		break;
	}
	case RUN_TYPE::ROLLER:
	{
		RPC_emulating::setskin(MYID, 99);
		RPC_emulating::setskin(MYID, iModelIndex);
		*PEDSELF->GetMemoryValue(0x4D4) = 138;
		break;
	}
	case RUN_TYPE::SWAT:
	{
		RPC_emulating::setskin(MYID, 285);
		RPC_emulating::setskin(MYID, iModelIndex);
		*PEDSELF->GetMemoryValue(0x4D4) = 128;
		break;
	}
	case RUN_TYPE::DEFAULT:
	{
		RPC_emulating::setskin(MYID, iModelIndex);
		break;
	}
	}
}

CustomRun::CustomRun(const char* szHackName)
{
	m_sHackName = szHackName;
}

void CustomRun::switchHack()
{
	setAnimGroupByRunType(m_CurrentRunType);
}

void CustomRun::onDrawSettings()
{
	if (ImGui::BeginMenu("Custom Run Anim"))
	{
		static RUN_TYPE choosedRunType = RUN_TYPE::DEFAULT;
		for (int i = 0; i <= (int)RUN_TYPE::SWAT; i++)
			if (ImGui::Button(nameof::nameof_enum((RUN_TYPE)i).data()))
			{
				m_CurrentRunType = (RUN_TYPE)i;
				setAnimGroupByRunType(m_CurrentRunType);
			}
		ImGui::EndMenu();
	}
}

void CustomRun::read(nlohmann::json& data)
{
	m_CurrentRunType = (RUN_TYPE)data["Type"].get<int>();
}

void CustomRun::save(nlohmann::json& data)
{
	data["Type"] = (int)m_CurrentRunType;
}