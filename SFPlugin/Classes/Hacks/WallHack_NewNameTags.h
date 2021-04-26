#pragma once
#include "Hack.h"
#include "C:\Lippets\FIles\SingleFile\Numbers.h"

class ChatBubble
{
public:
	UINT16 PlayerID;
	UINT32 color;
	DWORD timer;
	float drawDistance;
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
	std::deque<ChatBubble> chatBubbles;
	// wallhack
	SLineOfSightFlags LineOfSightFlags;
	int activationKey = 0;
	float fOrigDrawDistance;
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
	void init() override;
	void save(Json::Value &data) override;
	void read(Json::Value &data) override;
	void everyTickAction(const crTickLocalPlayerInfo& info) override;
	void onDrawGUI() override;
	void switchHack() override;
	void onWndProc(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info) override;
	bool onRPCIncoming(stRakNetHookParams* params, const crTickLocalPlayerInfo& info) override;
	void onDrawHack(const crTickLocalPlayerInfo& info) override;
	void onDrawSettings() override;
};