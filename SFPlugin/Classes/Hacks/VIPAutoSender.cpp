#include "VIPAutoSender.h"

VIPAutoSender::VIPAutoSender(const char* szHackName)
{
	m_dwProperties |= (HackProperties::RPCINC | HackProperties::RPCOUT | HackProperties::EVERYTICK_ACTION);
	m_sHackName = szHackName;
	m_bEnabled = 1;
}

bool VIPAutoSender::onRPCIncoming(stRakNetHookParams* params, crTickLocalPlayerInfo* pInfo)
{
	m_bIsWorking = true;
	if (params->packetId != ScriptRPCEnumeration::RPC_ScrClientMessage || !m_bIsWorking)
		return true;
	UINT8 length;
	char* ChatMessage;
	params->bitStream->ResetReadPointer();
	params->bitStream->Read(length);
	ChatMessage = new char[length];
	params->bitStream->Read(ChatMessage, length);
	ChatMessage[length] = '\0';

	std::string sMessage = ChatMessage;
	cm_(-1, sMessage.c_str());
	if (strstr(ChatMessage, m_sLastSentCommandText.c_str()))
	{
		cm_(-1, "Msg posted");
	}
	delete[]ChatMessage;
	return true;
}

bool VIPAutoSender::onRPCOutcoming(stRakNetHookParams* params, crTickLocalPlayerInfo* pInfo)
{
	if (params->packetId != RPCEnumeration::RPC_ServerCommand)
		return true;
	UINT32 length;
	char *buffer;
	std::string sCmdText;
	params->bitStream->ResetReadPointer();
	params->bitStream->Read(length);
	buffer = new char[length];
	params->bitStream->Read(buffer, length);
	buffer[length] = '\0';
	sCmdText = buffer;


	delete[] buffer;


	if (sCmdText.length() <= 4 || sCmdText.find("//vr ") != 0)
		return true;
	// if we inputed /vr ...
	sCmdText.erase(4);
	m_sLastSentCommandText = sCmdText;
	cm_(-1, sCmdText.c_str());
	return true;
}

void VIPAutoSender::everyTickAction(crTickLocalPlayerInfo* pInfo)
{

}

void VIPAutoSender::save(nlohmann::json& data)
{

}

void VIPAutoSender::read(nlohmann::json& data)
{

}