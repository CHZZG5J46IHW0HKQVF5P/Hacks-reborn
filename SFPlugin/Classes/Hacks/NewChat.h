#include "Hack.h"

class NewChat : public IHack
{
public:
	NewChat(const char*);
private:
	void onDrawHack(crTickLocalPlayerInfo*) override;
	void everyTickAction(crTickLocalPlayerInfo*) override;


};