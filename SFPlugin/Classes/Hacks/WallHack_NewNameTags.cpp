#include "WallHack_NewNameTags.h"
#include "GlobalFuncs.h"

FORCEINLINE void DrawLine(D3DCOLOR playerColor, CVector2D* start, CVector2D* end)
{
	SF->getRender()->DrawPolygon(start->fX, start->fY, 3, 3, 0.f, 10, playerColor);
	SF->getRender()->DrawLine(start->fX, start->fY, end->fX, end->fY, 1, playerColor);
}

FORCEINLINE void DrawCIRCLEatGameCoords(D3DCOLOR color, const CVector& coords)
{
	CVector screenCoords;
	D3D::CalcScreenCoords(&coords, &screenCoords);

	SF->getRender()->DrawPolygon(screenCoords.fX, screenCoords.fY, 3, 3, 0.f, 10, color);
}

WallHack::WallHack(const char* szHackName)
{
	m_sHackName = szHackName;
	m_bEnabled = true;
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
	font.Init();
}
void WallHack::save(nlohmann::json &data)
{
	SERIALIZE_FIELD_JSON(wallHack);
	SERIALIZE_FIELD_JSON(activationKey);
	SERIALIZE_FIELD_JSON(bDrawBones);
	SERIALIZE_FIELD_JSON(bShowGun);
	SERIALIZE_FIELD_JSON(bShowVeh);
	SERIALIZE_FIELD_JSON(bShowScore);
	SERIALIZE_FIELD_JSON(iBoxHight);
	SERIALIZE_FIELD_JSON(iYBoxOffset);
	SERIALIZE_FIELD_JSON(fYChatBubleOffset);
	SERIALIZE_FIELD_JSON(fNameTagYOffset);
	font.save(data);
}
void WallHack::read(nlohmann::json &data)
{

	DESERIALIZE_FIELD_JSON(wallHack);
	DESERIALIZE_FIELD_JSON(activationKey);
	DESERIALIZE_FIELD_JSON(bDrawBones);
	DESERIALIZE_FIELD_JSON(bShowGun);
	DESERIALIZE_FIELD_JSON(bShowVeh);
	DESERIALIZE_FIELD_JSON(bShowScore);
	DESERIALIZE_FIELD_JSON(iBoxHight);
	DESERIALIZE_FIELD_JSON(iYBoxOffset);
	DESERIALIZE_FIELD_JSON(fYChatBubleOffset);
	DESERIALIZE_FIELD_JSON(fNameTagYOffset);
	font.read(data);

	ASSIGN_VAR_VALUE_IF_EQUALS_ZEROF(fNameTagYOffset, 0.3059999942779541f);
	ASSIGN_VAR_VALUE_IF_EQUALS_ZERO(iBoxHight, 7);
	ASSIGN_VAR_VALUE_IF_EQUALS_ZERO(iYBoxOffset, 4);
}
void WallHack::everyTickAction()
{
	static int iGameState = 0;
	if (iGameState != SF->getSAMP()->getInfo()->iGameState)
	{
		iGameState = SF->getSAMP()->getInfo()->iGameState;
		if (iGameState == 15 || iGameState == 14)
			fOrigDrawDistance = SF->getSAMP()->getInfo()->pSettings->fNameTagsDistance;
	}
	SF->getSAMP()->getInfo()->pSettings->byteShowNameTags = 0;
}
void WallHack::onDrawGUI()
{

	if (ImGui::Checkbox("WallHack", &wallHack))
		this->switchHack();
	if (ImGui::BeginPopupContextItem())
	{

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
		ImGui::EndPopup();
	}
	ImGui::SameLine();
	Lippets::ImGuiSnippets::KeyButton(activationKey, g::keyButtonSplitter);
	ImGui::Checkbox("Dont Draw NameTags", &bNoNameTags);
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
bool WallHack::onWndProc()
{
	if (!g::pKeyEventInfo->bDown)
		return true;

	if (activationKey != 0 && g::pKeyEventInfo->iKeyID == activationKey)
	{
		drawWallHack = !drawWallHack;
		switchHack();
		notify("Wall Hack", drawWallHack);
	}
	return true;
}
bool WallHack::onRPCIncoming(stRakNetHookParams* params)
{
	if (params->packetId != ScriptRPCEnumeration::RPC_ScrChatBubble)
		return true;
	UINT16 playerid; UINT32 color; float drawDistance; UINT32 expiretime; UINT8 textLength; char *text;
	params->bitStream->ResetReadPointer();
	params->bitStream->Read(playerid);
	params->bitStream->Read(color);
	params->bitStream->Read(drawDistance);
	params->bitStream->Read(expiretime);
	params->bitStream->Read(textLength);
	text = new char[textLength];
	params->bitStream->Read(text, textLength);
	text[textLength] = '\0';
	params->bitStream->ResetReadPointer();
	for (auto&& iterator = chatBubbles.begin(); iterator != chatBubbles.end(); iterator++)
		if (iterator->PlayerID == playerid)
			chatBubbles.erase(iterator);
	chatBubbles.emplace_back(ChatBubble(playerid, color, GetTickCount() + expiretime, drawDistance, text));

	delete[] text;
	return false;
}
void WallHack::onDrawHack()
{
	if (!bNoNameTags || drawWallHack)
	{
											  
		GFuncs::resortPlayersByDistance(&g::pInfo->nearestPlayers, true);
		for (auto&& player : g::pInfo->nearestPlayers)//(int i = 0; i < 1000; i++)
		{
			const int i = player.id;
			CVector PedPos;
			GAME->GetPools()->GetPed((DWORD*)SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped)->GetTransformedBonePosition(eBone::BONE_HEAD, &PedPos);

			CMatrix matrix;
			GAME->GetCamera()->GetMatrix(&matrix);
			float fDistance = Lippets::Numbers::getDistanceBetween(PedPos.fX, PedPos.fY, PedPos.fZ, matrix.vPos.fX, matrix.vPos.fY, matrix.vPos.fZ);

			if (!drawWallHack)
				if (fDistance > fOrigDrawDistance)
					continue;


			PedPos.fZ += fNameTagYOffset + (fDistance * 0.05f);
			CVector onScreenPos;
			D3D::CalcScreenCoords(&PedPos, &onScreenPos);
			if (onScreenPos.fZ < 1.f)
				continue;

			if (!drawWallHack)
				if (!GAME->GetWorld()->IsLineOfSightClear(&matrix.vPos, &PedPos, g::LineOfSightFlags))
					continue;

			uint8 Cr, Cg, Cb, Ca;
			SF->getRender()->ARGB_To_A_R_G_B(SF->getSAMP()->getPlayers()->GetPlayerColor(i), Ca, Cr, Cg, Cb);
			D3DCOLOR playerColor = D3DCOLOR_ARGB(255, Cr, Cg, Cb);
			float fFontHeight = font.f->DrawHeight();
			char szBuffer[128];

			if (SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->iAFKState)
				sprintf(szBuffer, "[AFK] %s (%d)", SF->getSAMP()->getPlayers()->GetPlayerName(i), i);
			else
				sprintf(szBuffer, "%s (%d)", SF->getSAMP()->getPlayers()->GetPlayerName(i), i);

			font.f->Print(szBuffer, playerColor, (onScreenPos.fX - font.f->DrawLength(szBuffer) / 2.0f), onScreenPos.fY);
			uint16 iYO = 0;

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
				CPed* ped = GAME->GetPools()->GetPed((DWORD*)player.pActorInfo);
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
					if (Players::isPlayerInCar(player.pActorInfo))
						strcat_s(whbuffer, Stuff::VehiclesNames[SF->getSAMP()->getPlayers()->pRemotePlayer[i]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle->base.model_alt_id - 400]);
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
					playerColor,
					vecBonePos->fX + 10.f, vecBonePos->fY - 10.f);
				if (bDrawBones)
				{
					CVector2D UPPERTORSO = Players::getBonePosOnScreen(ped, BONE_UPPERTORSO);
					CVector2D PELVIS = Players::getBonePosOnScreen(ped, BONE_PELVIS); // ÎÏÒÈÌÈÇÅÉØÎÍ!

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_HEAD),
						&Players::getBonePosOnScreen(ped, BONE_NECK));

					DrawLine(playerColor, &UPPERTORSO,
						&Players::getBonePosOnScreen(ped, BONE_RIGHTSHOULDER));

					DrawLine(playerColor, &UPPERTORSO,
						&Players::getBonePosOnScreen(ped, BONE_LEFTSHOULDER));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_RIGHTSHOULDER),
						&Players::getBonePosOnScreen(ped, BONE_RIGHTELBOW));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_LEFTSHOULDER),
						&Players::getBonePosOnScreen(ped, BONE_LEFTELBOW));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_RIGHTELBOW),
						&Players::getBonePosOnScreen(ped, BONE_RIGHTWRIST));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_LEFTELBOW),
						&Players::getBonePosOnScreen(ped, BONE_LEFTWRIST));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_RIGHTWRIST),
						&Players::getBonePosOnScreen(ped, BONE_RIGHTHAND));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_LEFTWRIST),
						&Players::getBonePosOnScreen(ped, BONE_LEFTHAND));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_NECK),
						&UPPERTORSO);

					DrawLine(playerColor, &UPPERTORSO,
						&Players::getBonePosOnScreen(ped, BONE_SPINE1));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_SPINE1),
						&PELVIS);

					DrawLine(playerColor, &PELVIS,
						&Players::getBonePosOnScreen(ped, eBone::BONE_LEFTHIP));

					DrawLine(playerColor, &PELVIS,
						&Players::getBonePosOnScreen(ped, eBone::BONE_RIGHTHIP));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_LEFTHIP),
						&Players::getBonePosOnScreen(ped, eBone::BONE_LEFTKNEE));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_RIGHTHIP),
						&Players::getBonePosOnScreen(ped, eBone::BONE_RIGHTKNEE));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_LEFTKNEE),
						&Players::getBonePosOnScreen(ped, eBone::BONE_LEFTANKLE));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_RIGHTKNEE),
						&Players::getBonePosOnScreen(ped, eBone::BONE_RIGHTANKLE));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_LEFTANKLE),
						&Players::getBonePosOnScreen(ped, eBone::BONE_LEFTFOOT));

					DrawLine(playerColor, &Players::getBonePosOnScreen(ped, BONE_RIGHTANKLE),
						&Players::getBonePosOnScreen(ped, eBone::BONE_RIGHTFOOT));
				}
			}

		}
	}
	for (auto&& iterator = chatBubbles.begin(); iterator != chatBubbles.end(); iterator++)
	{
		if (iterator->timer < GetTickCount())
			chatBubbles.erase(iterator);
		else
		{
			if (!Players::isPlayerExist(iterator->PlayerID))
				continue;
			CVector PedPos;
			GAME->GetPools()->GetPed((DWORD*)SF->getSAMP()->getPlayers()->pRemotePlayer[iterator->PlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped)->GetTransformedBonePosition(eBone::BONE_HEAD, &PedPos);
			CMatrix matrix;
			GAME->GetCamera()->GetMatrix(&matrix);
			float fDistance = Lippets::Numbers::getDistanceBetween(PedPos.fX, PedPos.fY, PedPos.fZ, matrix.vPos.fX, matrix.vPos.fY, matrix.vPos.fZ);
			if (fDistance > iterator->drawDistance)
				continue;
			PedPos.fZ += fNameTagYOffset + (fDistance * 0.05f);
			CVector onScreenPos;
			D3D::CalcScreenCoords(&PedPos, &onScreenPos);
			if (onScreenPos.fZ < 1.f)
				continue;
			if (!GAME->GetWorld()->IsLineOfSightClear(&matrix.vPos, &PedPos, g::LineOfSightFlags))
				continue;
			uint8 Cr, Cg, Cb, Ca;
			SF->getRender()->ARGB_To_A_R_G_B(iterator->color, Cr, Cg, Cb, Ca);
			D3DCOLOR playerColor = D3DCOLOR_ARGB(255, Cr, Cg, Cb);
			font.f->Print(iterator->message, playerColor, (onScreenPos.fX - font.f->DrawLength(iterator->message) / 2.0f), (onScreenPos.fY - font.f->DrawHeight()) - fYChatBubleOffset);
		}

	}
}
