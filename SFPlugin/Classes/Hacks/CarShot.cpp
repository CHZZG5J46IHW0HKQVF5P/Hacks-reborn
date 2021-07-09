#include "CarShot.h"
#include "Collision.h"
#include "VehicleGodMode.h"
#include "GlobalFuncs.h"
DEFAULT_HACK_CONSTRUCTOR(CarShot);




void CarShot::onDrawGUI()
{
	ImGui::Checkbox("Car Shot", &m_bEnabled);
	if (ImGui::BeginPopupContextItem())
	{
		ImGui::SliderFloat("Force", &m_fForce, 0.5, 100.f);
		ImGui::EndPopup();
	}
}

CVector convertForceByCameraHeading(float fForce)
{
	float angle = *(float*)0xB6F258;
	PEDSELF->SetTargetRotation(angle + 1.57f);
	float heading = PEDSELF->GetTargetRotation();
	CVector output;
	output.fX = output.fX + fForce * sin(-heading);
	output.fY = output.fY + fForce * cos(-heading);

	return output;
}


bool CarShot::onPacketOutcoming(stRakNetHookParams* param)
{
	if (param->packetId == ID_VEHICLE_SYNC)
	{

		auto pTargetEntitiy = GAME->GetCamera()->GetCam(GAME->GetCamera()->GetActiveCam())->GetTargetEntity();

		if (!pTargetEntitiy)
			return true;

		stInCarData data;
		memset(&data, 0, sizeof(stInCarData));
		byte packet;
		param->bitStream->ResetReadPointer();
		param->bitStream->Read(packet);
		param->bitStream->Read((PCHAR)&data, sizeof(stInCarData));
		param->bitStream->ResetReadPointer();


		CVector wrapPos = *pTargetEntitiy->GetPosition() - *PEDSELF->GetPosition();
		wrapPos *= m_fForce;
		data.fMoveSpeed[0] = wrapPos.fX;
		data.fMoveSpeed[1] = wrapPos.fY;
		data.fMoveSpeed[2] = wrapPos.fZ;
		param->bitStream->ResetWritePointer();
		param->bitStream->Write(packet);
		param->bitStream->Write((PCHAR)&data, sizeof(stInCarData));
		return true;
	}
	return true;
}

void CarShot::save(nlohmann::json& data)
{

	SERIALIZE_FIELD_JSON(m_bEnabled);
	SERIALIZE_FIELD_JSON(m_fForce);
}

void CarShot::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON(m_bEnabled);
	DESERIALIZE_FIELD_JSON(m_fForce);
}