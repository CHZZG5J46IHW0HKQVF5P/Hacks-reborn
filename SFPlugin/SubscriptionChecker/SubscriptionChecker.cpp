#include "SubscriptionChecker.h"

#include "fstream"
#include <sstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

HRESULT SubscriptionChecker::downloadFile()
{
	return URLDownloadToFileA(0, m_sURLtoFile.c_str(), m_sPathToOutPutFile.c_str(), 0, 0);
}

void SubscriptionChecker::initialize(const char *szURLtoFile, const char* szPathToOutPutFile)
{
	m_sPathToOutPutFile = szPathToOutPutFile;
	m_sURLtoFile = szURLtoFile;
}

HackSubscription SubscriptionChecker::checkSubscription(DWORD dwKey)
{
	json jFile;
	HRESULT hres = downloadFile();
	if (hres != S_OK)
		return HackSubscription::CHECK_FAILED;

	std::ifstream inStream(m_sPathToOutPutFile);

	if (!inStream.is_open())
		return HackSubscription::CHECK_FAILED;

	try
	{
		std::string sFileData;
		std::ostringstream oss;
		oss << inStream.rdbuf();
		sFileData = oss.str();
		jFile = json::parse(sFileData);


		HackSubscription hackSubscription;
		jFile.at(std::to_string(dwKey)).get_to(hackSubscription);
		
		return hackSubscription;
	}
	catch (...)
	{
		return HackSubscription::CHECK_FAILED;
	}
		


}