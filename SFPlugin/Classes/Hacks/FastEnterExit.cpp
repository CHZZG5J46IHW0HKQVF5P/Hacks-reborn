#include "FastEnterExit.h"		

DEFAULT_HACK_CONSTRUCTOR(FastEnterExit)

void FastEnterExit::onDrawGUI()
{
	ImGui::Checkbox("Fast Vehicle Enter \ Exit", &m_bEnabled);

	if (ImGui::BeginPopupContextItem("Fast Vehicle Enter \ Exit Settings"))
	{
		ImGui::SliderInt("Delay", &m_iDelay, 0, 5000);
		ImGui::SliderFloat("Distance To Vehicle To Sit In Limit", &m_fVehicleDistanceLimit, 0.f, 500.f);
		ImGui::EndPopup();
	}
}

void FastEnterExit::everyTickAction()
{

	if (m_ActionTimer.isEnded())
		switch (m_Action)
		{
		case Action::NONE:
			return;

		case Action::REMOVE_FROM_VEHICLE:
		{
			if (!g::pInfo->isInCar())
				return;

			float fCoords[3] = { PEDSELF->GetPosition()->fX,PEDSELF->GetPosition()->fY,PEDSELF->GetPosition()->fZ };
			fCoords[2] += GAME->GetModelInfo(PEDSELF->GetVehicle()->GetModelIndex())->GetBoundingBox()->vecBoundMax.fY;

			GTAfunc_RemoveActorFromCarAndPutAt(fCoords);
			m_Action = Action::NONE;
			break;
		}
		case Action::SET_AS_DRIVER:
		{
			GTAfunc_PutActorInCar(g::pInfo->nearestVehicles[0].pVehInfo);
			m_Action = Action::NONE;
			break;
		}
		case Action::SET_AS_PASSANGER:
		{
			int iFreeSeat = Vehicles::getVehicleFreeSeat(g::pInfo->nearestVehicles[0].pVehInfo);
			if (iFreeSeat != -1)
			{
				GTAfunc_PutActorInCarAsPassenger(g::pInfo->nearestVehicles[0].pVehInfo, iFreeSeat);
				m_Action = Action::NONE;
			}
			break;
		}
		}

}

bool FastEnterExit::onWndProc()
{
	if (g::pKeyEventInfo->bDown)
		if (g::pKeyEventInfo->iKeyID == 70 || g::pKeyEventInfo->iKeyID == 71)
			if (g::pInfo->_isInCar)
			{
				if (g::pKeyEventInfo->iKeyID == 70)
				{
					m_Action = Action::REMOVE_FROM_VEHICLE;
					SF->getSAMP()->sendExitVehicle(Vehicles::getVehicleID(g::pInfo->pLocalVeh));
					m_ActionTimer.setTimer(m_iDelay);
					return false;
				}
			}
			else
			{
				if (g::pKeyEventInfo->iKeyID == 70)
				{
					if (!g::pInfo->nearestVehicles.empty())
						if (g::pInfo->nearestVehicles[0].fDistance <= m_fVehicleDistanceLimit)
						{
							m_Action = Action::SET_AS_DRIVER;
							SF->getSAMP()->sendEnterVehicle(g::pInfo->nearestVehicles[0].id, false);
							m_ActionTimer.setTimer(m_iDelay);
							return false;
						}
				}
				else
				{
					if (!g::pInfo->nearestVehicles.empty())
						if (g::pInfo->nearestVehicles[0].fDistance <= m_fVehicleDistanceLimit)
						{
							m_Action = Action::SET_AS_PASSANGER;
							SF->getSAMP()->sendEnterVehicle(g::pInfo->nearestVehicles[0].id, true);
							m_ActionTimer.setTimer(m_iDelay);
						}
				}
			}
	return true;
}
void FastEnterExit::save(nlohmann::json& data)
{
	SERIALIZE_FIELD_JSON(m_bEnabled);
	SERIALIZE_FIELD_JSON(m_fVehicleDistanceLimit);
	SERIALIZE_FIELD_JSON(m_iDelay);
}
void FastEnterExit::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON(m_bEnabled);
	DESERIALIZE_FIELD_JSON(m_fVehicleDistanceLimit);
	DESERIALIZE_FIELD_JSON(m_iDelay);
	ASSIGN_VAR_VALUE_IF_EQUALS_ZERO(m_iDelay, 150);
	ASSIGN_VAR_VALUE_IF_EQUALS_ZEROF(m_fVehicleDistanceLimit, 10.f);
}