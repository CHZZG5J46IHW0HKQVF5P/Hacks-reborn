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
	ImVec4 vec4Color = ImVec4(0, 0, 0, 0);
	CMFont font = CMFont("CustomRender");
	bool bRGB;
	bool bDrawLine;
	CVector onScreenPedCoords;
};

struct RenderPickup_ObjectData
{
	int id;
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

	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;

};

class Text3dRender : public RenderBase
{
public:
	std::string m_sRenderinName;
	std::vector<std::string > m_textToSearch;
	void render(Render3DTextData*);

	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;

};

class ObjectRender : public RenderBase
{
public:
	std::string m_sRenderinName;
	std::vector<int> m_ids;
	void render(RenderPickup_ObjectData*);

	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;

};



class RenderClass
{
private:
	std::vector<std::shared_ptr<ObjectRender>> m_objectsRenders;
	std::vector< std::shared_ptr<Text3dRender>> m_text3dRenders;
	std::vector<std::shared_ptr<PickupRender>> m_pickupRenders;
public:
	~RenderClass();
	RenderClass(const char*);

	void read(nlohmann::json&);
	void save(nlohmann::json&);

	bool areAnyObjectRendersEnabled();
	bool areAnyickupRendersEnabled();
	bool areAnyText3DRendersEnabled();
	void addObjectRender(ObjectRender*);
	void addPickupRender(PickupRender*);
	void addText3DRender(Text3dRender*);

	bool m_bIsEnabled = false;
	std::string m_sName;

	void drawEditor(size_t i);
	void drawMenu(size_t i);
	void renderPickups(RenderPickup_ObjectData*);
	void renderObjects(RenderPickup_ObjectData*);
	void render3DTexts(Render3DTextData*);

};






class CustomRender : public IHack
{
public:
	CustomRender(const char*);
	static inline CustomRenderData customRenderData;
private:
	bool m_bIsEditorWindowOpened = false;
	bool m_bIsMenuOpened = false;
	std::vector<RenderClass> m_classes;
	bool areAnyClassesEnabled();
	void drawMenu();
	void release() override;

	void save(nlohmann::json&) override;
	void read(nlohmann::json&) override;

	void onDrawGUI() override;
	void onDrawHack() override;

};