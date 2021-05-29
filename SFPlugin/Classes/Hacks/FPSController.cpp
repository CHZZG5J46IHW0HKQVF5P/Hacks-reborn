#include "FPSController.h"
#include "GlobalFuncs.h"
#include <chrono>
DEFAULT_HACK_CONSTRUCTOR_WITH_IMGUI(FPSController)

FPSController* pFPSControllerInst;



void FPSController::Refresh(bool bForceRefresh)
{

	static bool bWasInVehicle = false;
	if (bWasInVehicle == false &&
		g::pInfo->isInCar())
	{
		bWasInVehicle = true;
		WriteMem<int>(m_dwRTSSHookDllModuleAddres, 4, (m_iInVehicle_FPSLimit == 0 ? 100 : m_iInVehicle_FPSLimit));
	}
	bWasInVehicle = g::pInfo->isInCar();

	static bool bWasInIDLE = false;
	if (bWasInIDLE == false &&
		!g::pInfo->isInCar() && !PEDSELF->IsInWater())
	{
		bWasInIDLE = true;
		WriteMem<int>(m_dwRTSSHookDllModuleAddres, 4, (m_iIDLE_FPSLimit == 0 ? 500 : m_iIDLE_FPSLimit));
	}
	bWasInIDLE = !g::pInfo->isInCar() && !PEDSELF->IsInWater();


	static bool bWasInWater = false;
	if (bWasInWater == false &&
		PEDSELF->IsInWater())
	{
		bWasInWater = true;
		WriteMem<int>(m_dwRTSSHookDllModuleAddres, 4, (m_iSwimming_FPSLimit == 0 ? 35 : m_iSwimming_FPSLimit));
	}
	bWasInWater = PEDSELF->IsInWater();
	if (bForceRefresh)
	{
		bWasInIDLE = false;
		bWasInWater = false;
		bWasInVehicle = false;
	}
}

void FPSController::everyTickAction()
{
	static CMTimer getRTSSHookTimer;
	if (m_dwRTSSHookDllModuleAddres == 0)
	{
		if (!getRTSSHookTimer.isEnded())
			return;

		m_dwRTSSHookDllModuleAddres = Lippets::Computer::GetModuleBaseAddress(Lippets::Computer::FindProcessId("gta_sa.exe"), "RTSSHooks.dll");
		if (m_dwRTSSHookDllModuleAddres)
		{
			m_dwRTSSHookDllModuleAddres += 3736724;
			cm_(0x30FFCC, "[FPS Controller] RTSS Found (%d)", m_dwRTSSHookDllModuleAddres);
		}
		else
			getRTSSHookTimer.setTimer(5000);
	}
	else
		Refresh(false);
}


void FPSController::onDrawGUI()
{
	ImGui::Checkbox(m_sHackName.c_str(), &m_bEnabled);

	if (ImGui::BeginPopupContextItem("FPSSettings Menu"))
	{
		if (Lippets::ImGuiSnippets::BorderedInputInt("IDLE FPS Limit", &m_iIDLE_FPSLimit, 10, 1000, 1, 100) ||
			Lippets::ImGuiSnippets::BorderedInputInt("Driving FPS Limit", &m_iInVehicle_FPSLimit, 10, 1000, 1, 100) ||
			Lippets::ImGuiSnippets::BorderedInputInt("Swimming FPS Limit", &m_iSwimming_FPSLimit, 10, 100, 1, 100))
			Refresh(true);
		ImGui::EndPopup();
	}

}
void FPSController::save(nlohmann::json& data)
{
	SERIALIZE_FIELD_JSON(m_bEnabled);
	SERIALIZE_FIELD_JSON(m_iIDLE_FPSLimit);
	SERIALIZE_FIELD_JSON(m_iInVehicle_FPSLimit);
	SERIALIZE_FIELD_JSON(m_iSwimming_FPSLimit);
}

void FPSController::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON(m_bEnabled);
	DESERIALIZE_FIELD_JSON(m_iIDLE_FPSLimit);
	DESERIALIZE_FIELD_JSON(m_iInVehicle_FPSLimit);
	DESERIALIZE_FIELD_JSON(m_iSwimming_FPSLimit);

	ASSIGN_VAR_VALUE_IF_EQUALS_ZERO(m_iIDLE_FPSLimit, 500);
	ASSIGN_VAR_VALUE_IF_EQUALS_ZERO(m_iInVehicle_FPSLimit, 100);
	ASSIGN_VAR_VALUE_IF_EQUALS_ZERO(m_iSwimming_FPSLimit, 35);
}