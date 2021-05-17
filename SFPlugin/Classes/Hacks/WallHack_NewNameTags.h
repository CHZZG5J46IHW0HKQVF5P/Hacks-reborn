#pragma once
#include "Hack.h"
#include "C:\Lippets\FIles\Numbers.h"

class ChatBubble
{
public:
	UINT16 PlayerID = 0;
	UINT32 color = 0;
	DWORD timer = 0;
	float drawDistance = 0.f;
	char message[128];
	ChatBubble(UINT16 PlayerID,
		UINT32 color,
		UINT32 expiretime,
		float drawDistance,
		char* message);
	ChatBubble() {}
};



class WallHack : public IHack
{
public:
	WallHack(const char* name);
private:
	CMFont font = CMFont("WallHack");
	std::vector<ChatBubble> chatBubbles;
	// wallhack
	bool bNoNameTags = 0;
	int activationKey = 0;
	float fOrigDrawDistance = 100.f;
	bool wallHack = true;
	bool drawWallHack = false;
	bool  bDrawBones = false;
	bool  bShowGun = false;
	bool  bShowVeh = false;
	bool  bShowScore = false;
	// nametags
	int iBoxHight = 0;
	int iYBoxOffset = 0;
	float fYChatBubleOffset = 0.f;
	float fNameTagYOffset = 0.0;
	//
	void release() override;
	void init() override;
	void save(nlohmann::json &data) override;
	void read(nlohmann::json &data) override;
	void everyTickAction(crTickLocalPlayerInfo* info) override;
	void onDrawGUI() override;
	void switchHack() override;
	void onWndProc(WPARAM wParam, UINT msg, crTickLocalPlayerInfo* info) override;
	bool onRPCIncoming(stRakNetHookParams* params, crTickLocalPlayerInfo* info) override;
	void onDrawHack(crTickLocalPlayerInfo* info) override;
	void onDrawSettings() override;
};