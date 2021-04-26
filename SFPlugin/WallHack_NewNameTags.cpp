#include "WallHack_NewNameTags.h"

FORCEINLINE void DrawLine(D3DCOLOR clrPlayerColor, CVector2D* start, CVector2D* end)
{
	SF->getRender()->DrawPolygon(start->fX, start->fY, 3, 3, 0.f, 10, clrPlayerColor);
	SF->getRender()->DrawLine(start->fX, start->fY, end->fX, end->fY, 1, clrPlayerColor);
}

WallHack::WallHack(const char* name)
{
	hackName = name;
}

ChatBubble::ChatBubble(UINT16 PlayerID,
	UINT32 color,
	UINT32 expiretime,
	float drawDistance,
	char* message)
{
	this->PlayerID = PlayerID;
	this->color = color;
	this->timer = expiretime;
	this->drawDistance = drawDistance;
	strcpy_s(this->message, message);
}

void WallHack::release()
{
	SF->getSAMP()->getInfo()->pSettings->byteNoNametagsBehindWalls = 1;
	SF->getSAMP()->getInfo()->pSettings->fNameTagsDistance = fOrigDrawDistance;
}

void WallHack::init()
{
	this->isEnable = true;
	LineOfSightFlags.bCheckBuildings = true;
	LineOfSightFlags.bCheckObjects = true;
	LineOfSightFlags.bCheckPeds = false;
	LineOfSightFlags.bCheckVehicles = true;
	LineOfSightFlags.bCheckCarTires = true;
	font.Init();
}
void WallHack::save(Json::Value &data)
{
	data["WallHack"] = wallHack;
	data["ActivationKey"] = activationKey;
	data["wallhackPresets"]["bDrawBones"] = bDrawBones;
	data["wallhackPresets"]["bShowGun"] = bShowGun;
	data["wallhackPresets"]["bDrawBones"] = bShowVeh;
	data["wallhackPresets"]["bShowScore"] = bShowScore;
	data["NameTags"]["iBoxHight"] = iBoxHight;
	data["NameTags"]["iYBoxOffset"] = iYBoxOffset;
	data["NameTags"]["fYChatBubleOffset"] = fYChatBubleOffset;
	data["NameTags"]["fNameTagYOffset"] = fNameTagYOffset;
	font.save(data);
}
void WallHack::read(Json::Value &data)
{

	wallHack = data["WallHack"].asBool();

	activationKey = data["ActivationKey"].asInt();
	bDrawBones = data["wallhackPresets"]["bDrawBones"].asBool();
	bShowGun = data["wallhackPresets"]["bShowGun"].asBool();
	bShowVeh = data["wallhackPresets"]["bDrawBones"].asBool();
	bShowScore = data["wallhackPresets"]["bShowScore"].asBool();
	iBoxHight = data["NameTags"]["iBoxHight"].asInt();
	iYBoxOffset = data["NameTags"]["iYBoxOffset"].asInt();
	fYChatBubleOffset = data["NameTags"]["fYChatBubleOffset"].asFloat();
	fNameTagYOffset = data["NameTags"]["fNameTagYOffset"].asFloat();
	font.read(data);
}
void WallHack::everyTickAction(const crTickLocalPlayerInfo& info)
{
	static int iGameState = 0;
	if (iGameState != SF->getSAMP()->getInfo()->iGameState)
	{
		iGameState = SF->getSAMP()->getInfo()->iGameState;
		if (iGameState == 15 || iGameState == 14)
			fOrigDrawDistance = SF->getSAMP()->getInfo()->pSettings->fNameTagsDistance;
	}
	if (SF->getSAMP()->getInfo()->pSettings->byteShowNameTags != 0)
		SF->getSAMP()->getInfo()->pSettings->byteShowNameTags = 0;
}
void WallHack::onDrawGUI()
{

	if (ImGui::Checkbox(hackName.c_str(), &wallHack))
		this->switchHack();
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, 0);
}
void WallHack::switchHack()
{
	if (drawWallHack)
	{
		SF->getSAMP()->getInfo()->pSettings->byteNoNametagsBehindWalls = 0;
		SF->getSAMP()->getInfo()->pSettings->fNameTagsDistance = 300.0f;
	}
	else
	{
		SF->getSAMP()->getInfo()->pSettings->byteNoNametagsBehindWalls = 1;
		SF->getSAMP()->getInfo()->pSettings->fNameTagsDistance = fOrigDrawDistance;
	}
}
void WallHack::onWndProc(WPARAM wParam, UINT msg, const crTickLocalPlayerInfo& info)
{
	if (msg != WM_KEYDOWN && msg != WM_LBUTTONDOWN && msg != WM_SYSKEYDOWN)
		return;

	if (activationKey != 0 && wParam == activationKey)
	{
		drawWallHack ^= true;
		switchHack();
		notify("Wall Hack", drawWallHack);
	}
}
bool WallHack::onRPCIncoming(stRakNetHookParams* params, const crTickLocalPlayerInfo& info)
{
	if (params->packetId != 59)
		return true;
	UINT16 playerid; UINT32 color; float drawDistance; UINT32 expiretime; UINT8 textLength; char text[256];
	params->bitStream->ResetReadPointer();
	params->bitStream->Read(playerid);
	params->bitStream->Read(color);
	params->bitStream->Read(drawDistance);
	params->bitStream->Read(expiretime);
	params->bitStream->Read(textLength);
	params->bitStream->Read(text, textLength);
	text[textLength] = '\0';
	params->bitStream->ResetReadPointer();
	for (size_t i = 0; i < chatBubbles.size(); i++)
		if (chatBubbles[i].PlayerID == playerid)
			chatBubbles.erase(chatBubbles.begin() + i);
	chatBubbles.emplace_back(ChatBubble(playerid, color, GetTickCount() + expiretime, drawDistance, text));

	return false;
}
void WallHack::onDrawHack(const crTickLocalPlayerInfo& info)
{
	for (int i = 0; i < 1000; i++)
	{
		if (!Players::isPlayerExist(i))
			continue;
		CVector PedPos;
		GAME->GetPools()->GetPed((DWORD*)SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped)->GetTransformedBonePosition(eBone::BONE_HEAD, &PedPos);

		CMatrix matrix;
		GAME->GetCamera()->GetMatrix(&matrix);
		float fDistance = Lippets::Numbers::getDistanceBetween(PedPos.fX, PedPos.fY, PedPos.fZ, matrix.vPos.fX, matrix.vPos.fY, matrix.vPos.fZ);

		if (drawWallHack || fDistance <= fOrigDrawDistance)
		{
		}
		else
			continue;

		PedPos.fZ += fNameTagYOffset + (fDistance * 0.05f);
		CVector onScreenPos;
		D3D::CalcScreenCoors(&PedPos, &onScreenPos);
		if (onScreenPos.fZ < 1.f)
			continue;
		if (drawWallHack || GAME->GetWorld()->IsLineOfSightClear(&matrix.vPos, &PedPos, LineOfSightFlags))
		{
		}
		else
			continue;
		uint8 Cr, Cg, Cb, Ca;
		SF->getRender()->ARGB_To_A_R_G_B(SF->getSAMP()->getPlayers()->GetPlayerColor(i), Ca, Cr, Cg, Cb);
		D3DCOLOR clrPlayerColor = D3DCOLOR_ARGB(255, Cr, Cg, Cb);
		float fFontHeight = font.f->DrawHeight();


		char szBuffer[128];

		if (SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->iAFKState)
			sprintf_s(szBuffer, "[AFK] %s (%d)", SF->getSAMP()->getPlayers()->GetPlayerName(i), i);
		else
			sprintf_s(szBuffer, "%s (%d)", SF->getSAMP()->getPlayers()->GetPlayerName(i), i);

		font.f->Print(szBuffer, clrPlayerColor, (onScreenPos.fX - font.f->DrawLength(szBuffer) / 2.0f), onScreenPos.fY);
		uint8 iYO = 0;

		if (SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->fActorArmor > 0.f)
		{
			iYO += iYBoxOffset;
			SF->getRender()->DrawBorderedBox(onScreenPos.fX - 25, onScreenPos.fY + fFontHeight + iYO, 50, iBoxHight, 0xD8000000, 1, 0xFF000000);
			SF->getRender()->DrawBorderedBox(onScreenPos.fX - 25, onScreenPos.fY + fFontHeight + iYO, SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->fActorArmor * 0.5f, iBoxHight, 0xFFFFFFFF, 1, 0xFF000000);
			iYO += iBoxHight;
		}
		iYO += iYBoxOffset;
		SF->getRender()->DrawBorderedBox(onScreenPos.fX - 25, onScreenPos.fY + fFontHeight + iYO, 50, iBoxHight, 0xD8000000, 1, 0xFF000000);
		float health = SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->fActorHealth;
		if (health > 100.f)
			health = 100.f;
		SF->getRender()->DrawBorderedBox(onScreenPos.fX - 25, onScreenPos.fY + fFontHeight + iYO, health * 0.5f, iBoxHight, 0xFFFF0000, 1, 0xFF000000);



		if (drawWallHack && (bShowGun || bDrawBones || bShowVeh))
		{
			CPed* ped = GAME->GetPools()->GetPed((DWORD*)SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped);
			CVector2D* vecBonePos;
			CVector2D vecBonePosRIGHT = Players::getBonePosOnScreen(ped, BONE_RIGHTSHOULDER);
			CVector2D vecBonePosLEFT = Players::getBonePosOnScreen(ped, BONE_LEFTSHOULDER);
			if (vecBonePosRIGHT.fX > vecBonePosLEFT.fX)
				vecBonePos = &vecBonePosRIGHT;
			else
				vecBonePos = &vecBonePosLEFT;
			char whbuffer[256];
			memset(whbuffer, 0, 256);
			if (bShowGun)
			{

				strcat_s(whbuffer, Stuff::WeaponsNames[SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->onFootData.byteCurrentWeapon]);
				strcat_s(whbuffer, " \n");
			}
			if (bShowVeh)
			{
				if (Players::isPlayerInCar(i))
					strcat_s(whbuffer, Stuff::VehiclesNames[SF->getSAMP()->getVehicles()->pGTA_Vehicle[SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->sVehicleID]->base.model_alt_id - 400]);
				else
					strcat_s(whbuffer, "Onfoot");
				strcat_s(whbuffer, " \n");
			}
			if (bShowScore)
			{
				char buff[32];
				sprintf_s(buff, "Score %d", SF->getSAMP()->getPlayers()->pRemotePlayer[i]->iScore);
				strcat_s(whbuffer, buff);
			}
			font.f->Print(whbuffer,
				clrPlayerColor,
				vecBonePos->fX + 10.f, vecBonePos->fY - 10.f);
			if (bDrawBones)
			{
				CVector2D UPPERTORSO = Players::getBonePosOnScreen(ped, BONE_UPPERTORSO);
				CVector2D PELVIS = Players::getBonePosOnScreen(ped, BONE_PELVIS); // Œœ“»Ã»«≈…ÿŒÕ!

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_HEAD),
					&Players::getBonePosOnScreen(ped, BONE_NECK));

				DrawLine(clrPlayerColor, &UPPERTORSO,
					&Players::getBonePosOnScreen(ped, BONE_RIGHTSHOULDER));

				DrawLine(clrPlayerColor, &UPPERTORSO,
					&Players::getBonePosOnScreen(ped, BONE_LEFTSHOULDER));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_RIGHTSHOULDER),
					&Players::getBonePosOnScreen(ped, BONE_RIGHTELBOW));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_LEFTSHOULDER),
					&Players::getBonePosOnScreen(ped, BONE_LEFTELBOW));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_RIGHTELBOW),
					&Players::getBonePosOnScreen(ped, BONE_RIGHTWRIST));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_LEFTELBOW),
					&Players::getBonePosOnScreen(ped, BONE_LEFTWRIST));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_RIGHTWRIST),
					&Players::getBonePosOnScreen(ped, BONE_RIGHTHAND));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_LEFTWRIST),
					&Players::getBonePosOnScreen(ped, BONE_LEFTHAND));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_NECK),
					&UPPERTORSO);

				DrawLine(clrPlayerColor, &UPPERTORSO,
					&Players::getBonePosOnScreen(ped, BONE_SPINE1));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_SPINE1),
					&PELVIS);

				DrawLine(clrPlayerColor, &PELVIS,
					&Players::getBonePosOnScreen(ped, eBone::BONE_LEFTHIP));

				DrawLine(clrPlayerColor, &PELVIS,
					&Players::getBonePosOnScreen(ped, eBone::BONE_RIGHTHIP));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_LEFTHIP),
					&Players::getBonePosOnScreen(ped, eBone::BONE_LEFTKNEE));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_RIGHTHIP),
					&Players::getBonePosOnScreen(ped, eBone::BONE_RIGHTKNEE));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_LEFTKNEE),
					&Players::getBonePosOnScreen(ped, eBone::BONE_LEFTANKLE));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_RIGHTKNEE),
					&Players::getBonePosOnScreen(ped, eBone::BONE_RIGHTANKLE));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_LEFTANKLE),
					&Players::getBonePosOnScreen(ped, eBone::BONE_LEFTFOOT));

				DrawLine(clrPlayerColor, &Players::getBonePosOnScreen(ped, BONE_RIGHTANKLE),
					&Players::getBonePosOnScreen(ped, eBone::BONE_RIGHTFOOT));
			}
		}

	}
	for (size_t i = 0; i < chatBubbles.size(); i++)
	{
		if (chatBubbles[i].timer < GetTickCount())
		{
			for (size_t b = i; b < chatBubbles.size() - 1U; b++)
				chatBubbles[b] = chatBubbles[b + 1];
			chatBubbles.resize(chatBubbles.size() - 1U);
		}
		else
		{
			if (!Players::isPlayerExist(chatBubbles[i].PlayerID))
				continue;
			CVector PedPos;
			GAME->GetPools()->GetPed((DWORD*)SF->getSAMP()->getPlayers()->pRemotePlayer[chatBubbles[i].PlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped)->GetTransformedBonePosition(eBone::BONE_HEAD, &PedPos);
			CMatrix matrix;
			GAME->GetCamera()->GetMatrix(&matrix);
			float fDistance = Lippets::Numbers::getDistanceBetween(PedPos.fX, PedPos.fY, PedPos.fZ, matrix.vPos.fX, matrix.vPos.fY, matrix.vPos.fZ);
			if (fDistance > chatBubbles[i].drawDistance)
				continue;
			PedPos.fZ += fNameTagYOffset + (fDistance * 0.05f);
			CVector onScreenPos;
			D3D::CalcScreenCoors(&PedPos, &onScreenPos);
			if (onScreenPos.fZ < 1.f)
				continue;
			if (!GAME->GetWorld()->IsLineOfSightClear(&matrix.vPos, &PedPos, LineOfSightFlags))
				continue;
			uint8 Cr, Cg, Cb, Ca;
			SF->getRender()->ARGB_To_A_R_G_B(chatBubbles[i].color, Cr, Cg, Cb, Ca);
			D3DCOLOR clrPlayerColor = D3DCOLOR_ARGB(255, Cr, Cg, Cb);
			font.f->Print(chatBubbles[i].message, clrPlayerColor, (onScreenPos.fX - font.f->DrawLength(chatBubbles[i].message) / 2.0f), (onScreenPos.fY - font.f->DrawHeight()) - fYChatBubleOffset);
		}

	}

}
void WallHack::onDrawSettings()
{
	if (ImGui::BeginMenu("New Name Tags"))
	{
		ImGui::SliderFloat("Y Offset", &fNameTagYOffset, 0.0f, 1.0f);
		ImGui::SliderInt("Box Hight", &iBoxHight, 0, 15);
		ImGui::SliderFloat("Y ChatBuble Offset", &fYChatBubleOffset, 0.f, 50.f);
		ImGui::SliderInt("Y Box Offset", &iYBoxOffset, 0, 10);
		if (ImGui::BeginMenu("Wall Hack"))
		{
			ImGui::Checkbox("Draw Bones", &bDrawBones);
			ImGui::Checkbox("Show Gun", &bShowGun);
			ImGui::Checkbox("Show Vehicle", &bShowVeh);
			ImGui::Checkbox("Show Score", &bShowScore);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Font"))
		{
			if (ImGui::InputText("Font###tagsFont", font.FontName, 64))
			{
				font.Release();
				font.Init();
			}
			if (ImGui::SliderInt("Font Size###tagsSize", &font.FontSize, 0, 24))
			{
				font.Release();
				font.Init();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}

}