#include "PlayersDescription.h"

DEFAULT_HACK_CONSTRUCTOR(PlayersDescription)

void PlayersDescription::onDrawGUI()
{
	ImGui::Checkbox("Edit Players Descriptions View Distance", &m_bEnabled);
	if (ImGui::BeginPopupContextItem())
	{
		ImGui::SliderFloat("New View Distance",&m_fNewDistance,0.f,300.f);
		ImGui::EndPopup();
	}
}

void PlayersDescription::save(nlohmann::json& data)
{
	SERIALIZE_FIELD_JSON(m_bEnabled);
	SERIALIZE_FIELD_JSON(m_fNewDistance);
}

void PlayersDescription::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON(m_bEnabled);
	DESERIALIZE_FIELD_JSON(m_fNewDistance);
}

bool PlayersDescription::onRPCIncoming(stRakNetHookParams* params)
{
	if (params->packetId == ScriptRPCEnumeration::RPC_ScrCreate3DTextLabel)
	{

		int16 id;
		int32 color;
		float position[3];
		float distance;
		bool testLOS;
		int16 attachedPlayerId;
		int16 attachedVehicleId;

		params->bitStream->ResetReadPointer();
		params->bitStream->Read(id);
		params->bitStream->Read(color);
		params->bitStream->Read(position[0]);
		params->bitStream->Read(position[1]);
		params->bitStream->Read(position[2]);
		params->bitStream->Read(distance);
		params->bitStream->Read(testLOS);
		params->bitStream->Read(attachedPlayerId);
		params->bitStream->Read(attachedVehicleId);

		if (attachedPlayerId != 65535 && color == -858993409)// && position[2] == -1)
		{
			if (m_fNewDistance <= 0.5f)
				return false;
			else
			{
				params->bitStream->SetWriteOffset(144);
				params->bitStream->Write(m_fNewDistance);
				params->bitStream->ResetWritePointer();
				return true;
			}
		}

	}
	return true;
}
