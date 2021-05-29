#pragma once

#include "FIles/LUtils.h"

#include "string"

#include "urlmon.h" 
#include <wininet.h> 
#pragma comment(lib, "urlmon.lib")


enum class HackSubscription
{
	CHECK_FAILED,
	FREE,
	STAGE_1,
	FULL_PACKET
};

class SubscriptionChecker : Lippets::LUtils::Singleton<SubscriptionChecker>
{
public:
	SubscriptionChecker() {}
	void initialize(const char *szURLtoFile, const char* szPathToOutPutFile);
	HackSubscription checkSubscription(DWORD dwKey);
private:
	std::string m_sURLtoFile;
	std::string m_sPathToOutPutFile;

	HRESULT downloadFile();

};