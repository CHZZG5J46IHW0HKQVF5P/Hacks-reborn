#include "Hack.h"

class VIPAutoSender : public IHack
{
public:
	VIPAutoSender(const char*);
private:
	bool m_bIsWorking = false;
	std::string m_sLastSentCommandText = "";
	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;
	bool onRPCOutcoming(stRakNetHookParams*, crTickLocalPlayerInfo*) override;
	bool onRPCIncoming(stRakNetHookParams*, crTickLocalPlayerInfo*) override;
	void everyTickAction(crTickLocalPlayerInfo*) override;
};