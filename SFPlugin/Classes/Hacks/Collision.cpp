#include "Collision.h"
#include "GlobalFuncs.h"
#include "SampSnipps/cheat_funcs.h"

#define HOOKPOS_PlayerCollision 0x0054BCEE

CollisionHack* pCollisionHack;

DEFAULT_HACK_CONSTRUCTOR(CollisionHack)

bool CollisionCheck(object_base *obj1, object_base *obj2)
{
	return (obj2->nType == 3 || obj2->nType == 2) &&
		((obj1->nType == 2 && pCollisionHack->m_bIsVehicleCollisionEnabled) ||
		(obj1->nType == 3 && pCollisionHack->m_bIsPedsCollisionEnabled) ||
			(obj1->nType == 4 && pCollisionHack->m_bIsObjectsCollisionEnabled));
}

void __declspec (naked) HOOK_PlayerCollision(void)
{

	static object_base *_obj1, *_obj2;
	static DWORD RETURN_ovrwr = 0x54CEFC, RETURN_process = 0x0054BCF4, RETURN_noProcessing = 0x54CF8D;
	__asm
	{
		jz hk_PlCol_process
		jmp RETURN_ovrwr
	}

hk_PlCol_process:
	__asm
	{
		pushad
		mov _obj2, esi // processing collision of *_info (esi)
		mov _obj1, edi // with *_info (edi)
	}


	if (!pCollisionHack->isHackWorking())
		goto hk_PlCol_processCol;

	// process collision if cheat not enabled
	//goto hk_PlCol_processCol;

	// already crashed, if true
	if (_obj1 == nullptr || _obj2 == nullptr)
		goto hk_PlCol_noCol;

	// check for disable collision
	if (CollisionCheck(_obj1, _obj2))
		goto hk_PlCol_noCol;


	if (pCollisionHack->m_bIsBuildingsCollisionEnabled)
	{
		__asm popad;
		__asm jmp RETURN_ovrwr
	}


hk_PlCol_processCol:
	__asm popad
	__asm jmp RETURN_process

	hk_PlCol_noCol :
				   __asm popad
				   __asm jmp RETURN_noProcessing

}


void CollisionHack::onDrawGUI()
{

	ImGui::Checkbox("Collision", &m_bEnabled);

	if (ImGui::BeginPopupContextItem("Collision Menu"))
	{
		ImGui::Checkbox("Vehicles Collision", &m_bIsVehicleCollisionEnabled);

		ImGui::Checkbox("Peds Collision", &m_bIsPedsCollisionEnabled);

		ImGui::Checkbox("Objects Collision", &m_bIsObjectsCollisionEnabled);

		ImGui::Checkbox("Buildings Collision", &m_bIsBuildingsCollisionEnabled);

		ImGui::EndPopup();
	}


}

void CollisionHack::init()
{
	pCollisionHack = GFuncs::getHackPtr<CollisionHack>();

	memcpy_safe(patch, (void *)HOOKPOS_PlayerCollision, 6);
	SF->getGame()->createHook((void *)HOOKPOS_PlayerCollision, HOOK_PlayerCollision, DETOUR_TYPE_JMP, 6);
}

void CollisionHack::release()
{
	memcpy_safe((void *)HOOKPOS_PlayerCollision, patch, 6);
}



void CollisionHack::save(nlohmann::json& data)
{

	SERIALIZE_FIELD_JSON_(m_sHackName, m_bEnabled);
	SERIALIZE_FIELD_JSON(m_bIsBuildingsCollisionEnabled);
	SERIALIZE_FIELD_JSON(m_bIsObjectsCollisionEnabled);
	SERIALIZE_FIELD_JSON(m_bIsPedsCollisionEnabled);
	SERIALIZE_FIELD_JSON(m_bIsVehicleCollisionEnabled);

}




void CollisionHack::read(nlohmann::json& data)
{
	DESERIALIZE_FIELD_JSON_(m_sHackName, m_bEnabled);
	DESERIALIZE_FIELD_JSON(m_bIsBuildingsCollisionEnabled);
	DESERIALIZE_FIELD_JSON(m_bIsObjectsCollisionEnabled);
	DESERIALIZE_FIELD_JSON(m_bIsObjectsCollisionEnabled);
	DESERIALIZE_FIELD_JSON(m_bIsPedsCollisionEnabled);
	DESERIALIZE_FIELD_JSON(m_bIsVehicleCollisionEnabled);
}