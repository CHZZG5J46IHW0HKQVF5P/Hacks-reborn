#include "ArizonaLEmulator.h"

DEFAULT_HACK_CONSTRUCTOR(ArizonaLEmulator)


bool ArizonaLEmulator::onRPCOutcoming(stRakNetHookParams* params)
{
	if (params->packetId != RPCEnumeration::RPC_ClientJoin)
		return true;
	INT32 iVersion;
	UINT8 byteMod;
	UINT8 byteNicknameLen;
	char *NickName;
	UINT32  uiClientChallengeResponse;
	UINT8 byteAuthKeyLen;
	char *auth_key;
	UINT8 iClientVerLen;
	char *ClientVersion;
	params->bitStream->ResetReadPointer();
	params->bitStream->Read(iVersion);
	params->bitStream->Read(byteMod);
	params->bitStream->Read(byteNicknameLen);
	NickName = new char[byteNicknameLen];
	NickName[byteNicknameLen] = '\0';
	params->bitStream->Read(NickName, byteNicknameLen);
	params->bitStream->Read(uiClientChallengeResponse);
	params->bitStream->Read(byteAuthKeyLen);
	auth_key = new char[byteAuthKeyLen];
	params->bitStream->Read(auth_key, byteAuthKeyLen);
	auth_key[byteAuthKeyLen] = '\0';
	params->bitStream->Read(iClientVerLen);
	ClientVersion = new char[iClientVerLen];
	params->bitStream->Read(ClientVersion, iClientVerLen);
	ClientVersion[iClientVerLen] = '\0';
	params->bitStream->ResetReadPointer();
	params->bitStream->ResetWritePointer();
	params->bitStream->Reset();
	params->bitStream->Write(iVersion);
	params->bitStream->Write(byteMod);
	params->bitStream->Write(byteNicknameLen);
	params->bitStream->Write(NickName, byteNicknameLen);
	params->bitStream->Write(uiClientChallengeResponse);
	params->bitStream->Write(byteAuthKeyLen);
	params->bitStream->Write(auth_key, byteAuthKeyLen);

	/*
	iClientVerLen = sizeof("Arizona PC");
	strcpy(ClientVersion, "Arizona PC");
	*/
	iClientVerLen = sizeof("arizona-mobile");
	strcpy(ClientVersion, "arizona-mobile");


	params->bitStream->Write(iClientVerLen);
	params->bitStream->Write(ClientVersion, iClientVerLen);

	delete[] ClientVersion;;
	delete[] NickName;
	delete[] auth_key;

	return true;

}

void ArizonaLEmulator::onDrawGUI()
{
	ImGui::Checkbox("Emulate Arz-mobile", &m_bEnabled);
}

void ArizonaLEmulator::save(nlohmann::json& data)
{
	data[m_sHackName] = m_bEnabled;
}

void ArizonaLEmulator::read(nlohmann::json& data)
{
	m_bEnabled = data[m_sHackName].get<bool>();
}