#pragma once
#include "Hack.h"
#include <memory>
#include "C:\\Lippets\\FIles\\LUtils.h"
#define pickup SF->getSAMP()->getInfo()->pPools->pPickup->pickup
#define object SF->getSAMP()->getInfo()->pPools->pObject->object
#define text3d SF->getSAMP()->getInfo()->pPools->pText3D->textLabel
class RenderBase
{
public:
	bool m_bIsEnabled = true;
	std::string m_sName;
	virtual void read(nlohmann::json&) {};
	virtual void save(nlohmann::json&) {};
};

struct CustomRenderData
{
	float  vec4Color[4] = { 0.f,0.f,0.f,1.f };
	CMFont font = CMFont("CustomRender");
	bool bDrawLine;
	CVector onScreenPedCoords;
};

struct RenderPickup_ObjectData
{
	int iModel;
	float fDistance;
	CVector onScreenCoords;
};

struct Render3DTextData
{
	int id;
	char* szText;
	float fDistance;
	CVector onScreenCoords;
};

class PickupRender : public RenderBase
{
public:
	std::string m_sRenderinName;
	std::vector<int> m_ids;
	void render(RenderPickup_ObjectData*);

	OVERRIDE_SAVE_READ;

};

class Text3dRender : public RenderBase
{
public:
	std::string m_sRenderinName;
	std::vector<std::string > m_textToSearch;
	void render(Render3DTextData*);
	OVERRIDE_SAVE_READ;
};

class ObjectRender : public RenderBase
{
public:
	std::string m_sRenderinName;
	std::vector<int> m_ids;
	void render(RenderPickup_ObjectData*);
	OVERRIDE_SAVE_READ;
};



class RenderClass
{
private:
	std::vector<ObjectRender> m_objectsRenders;
	std::vector<Text3dRender> m_text3dRenders;
	std::vector<PickupRender> m_pickupRenders;
public:
	bool m_bIsEnabled = false;

	std::string m_sName;

	RenderClass(const char*);

	void read(nlohmann::json&);
	void save(nlohmann::json&);

	bool areAnyObjectRendersEnabled();
	bool areAnyickupRendersEnabled();
	bool areAnyText3DRendersEnabled();

	void drawEditor(size_t i);
	void drawMenu(size_t i);
	void renderPickups(RenderPickup_ObjectData*);
	void renderObjects(RenderPickup_ObjectData*);
	void render3DTexts(Render3DTextData*);
};






HACK_CLASS(CustomRender)
{
public:
	CustomRender(const char*);
	static inline CustomRenderData customRenderData;
private:
	bool m_bIsEditorWindowOpened = false;
	bool m_bIsMenuOpened = false;
	bool m_bDrawMenu = false;
	std::vector<RenderClass> m_classes;
	bool areAnyClassesEnabled();
	void drawMenu();

	OVERRIDE_SAVE_READ;
	OVERRIDE_DRAWGUI;
	OVERRIDE_DRAW_HACK;

};