#include "FastEnterExit.h"		

DEFAULT_HACK_CONSTRUCTOR(FastEnterExit)

void FastEnterExit::onDrawGUI()
{
	ImGui::Checkbox("Fast Vehicle Enter \ Exit", &m_bEnabled);

	if (ImGui::BeginPopupContextItem("Fast Vehicle Enter \ Exit Settings"))
	{
		ImGui::InputFloat("Distance To Vehicle To Sit In Limit", &m_fVehicleDistanceLimit);
		ImGui::EndPopup();
	}
}

bool FastEnterExit::onWndProc()
{
	if (g::pKeyEventInfo->bDown)
		if (g::pKeyEventInfo->iKeyID == 70 || g::pKeyEventInfo->iKeyID == 71)
			if (g::pInfo->isInCar)
			{
				if (g::pKeyEventInfo->iKeyID == 70)
				{
					float fCoords[3] = { PEDSELF->GetPosition()->fX,PEDSELF->GetPosition()->fY,PEDSELF->GetPosition()->fZ };
					fCoords[2] += GAME->GetModelInfo(PEDSELF->GetVehicle()->GetModelIndex())->GetBoundingBox()->vecBoundMax.fY;
					GTAfunc_RemoveActorFromCarAndPutAt(fCoords);
					return false;
				}
			}
			else
			{
				if (g::pKeyEventInfo->iKeyID == 70)
				{
					if (!g::pInfo->nearestVehicles.empty())
						if (g::pInfo->nearestVehicles[0].fDistance <= m_fVehicleDistanceLimit)
							GTAfunc_PutActorInCar(g::pInfo->nearestVehicles[0].pVehInfo);
					return false;
				}
				else
				{
					if (!g::pInfo->nearestVehicles.empty())
						if (g::pInfo->nearestVehicles[0].fDistance <= m_fVehicleDistanceLimit)
						{
							int iFreeSeat = Vehicles::getVehicleFreeSeat(g::pInfo->nearestVehicles[0].pVehInfo);
							if (iFreeSeat != -1)
								GTAfunc_PutActorInCarAsPassenger(g::pInfo->nearestVehicles[0].pVehInfo, iFreeSeat);
						}

				}
			}
	return true;
}
void FastEnterExit::save(nlohmann::json& data)
{
	SERIALIZE_FIELD_JSON(m_bEnabled);
	SERIALIZE_FIELD_JSON(m_fVehicleDistanceLimit);
}
void FastEnterExit::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON(m_bEnabled);
	DESERIALIZE_FIELD_JSON(m_fVehicleDistanceLimit);

	ASSIGN_VAR_VALUE_IF_EQUALS_ZEROF(m_fVehicleDistanceLimit, 10.f);
}