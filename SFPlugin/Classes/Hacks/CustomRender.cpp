#include "CustomRender.h"


void RenderClass::drawEditor(size_t spl)
{
	ImGui::InputText("Class Name", &m_sName);
	// PickUps
	if (ImGui::CollapsingHeader("Pickups"))
	{
		if (ImGui::Button("Create New Pickup Render"))
			m_pickupRenders.emplace_back(PickupRender());
		for (size_t i = 0; i < m_pickupRenders.size(); i++)
		{
			auto&& pickupRender = m_pickupRenders[i];
			char buff[128];

			sprintf(buff, "%s###pickupEditor%d%d", pickupRender.m_sName.c_str(), spl, i);
			ImGui::Bullet();
			if (ImGui::TreeNode(buff))
			{
				sprintf(buff, "Delete###pickupdeletebtn%d%d", spl, i);
				if (ImGui::Button(buff))
				{
					m_pickupRenders.erase(m_pickupRenders.begin() + i);
					i--;
				}
				sprintf(buff, "Name###pickupname%d%d", spl, i);
				ImGui::InputText(buff, &pickupRender.m_sName);
				sprintf(buff, "Rendering Name###pickuprenderingname%d%d", spl, i);
				ImGui::InputText(buff, &pickupRender.m_sRenderinName);

				if (ImGui::CollapsingHeader("IDs"))
				{
					if (ImGui::Button("+"))
						pickupRender.m_ids.push_back(0);
					for (size_t id = 0; id < pickupRender.m_ids.size(); id++)
					{
						char buff[128];
						sprintf(buff, "ID###idInputInt%d%d%d", spl, i, id);
						ImGui::InputInt(buff, &pickupRender.m_ids[id]);
						ImGui::SameLine();
						sprintf(buff, "-###picksremovebtn%d%d%d", spl, i, id);
						if (ImGui::Button(buff))
							pickupRender.m_ids.erase(pickupRender.m_ids.begin() + i);
					}
				}
				ImGui::TreePop();
			}
		}
	}
	// Objects
	if (ImGui::CollapsingHeader("Objects"))
	{
		if (ImGui::Button("Create New Object Render"))
			m_objectsRenders.emplace_back(ObjectRender());
		for (size_t i = 0; i < m_objectsRenders.size(); i++)
		{
			auto&& objectRender = m_objectsRenders[i];
			char buff[128];

			sprintf(buff, "%s###objectEditor%d%d", objectRender.m_sName.c_str(), spl, i);
			ImGui::Bullet();
			if (ImGui::TreeNode(buff))
			{
				sprintf(buff, "Delete###objectdeletebtn%d%d", spl, i);
				if (ImGui::Button(buff))
				{

					m_objectsRenders.erase(m_objectsRenders.begin() + i);
					i--;
				}
				sprintf(buff, "Name###obhectname%d%d", spl, i);
				ImGui::InputText(buff, &objectRender.m_sName);
				sprintf(buff, "Rendering Name###objectrenderingname%d%d", spl, i);
				ImGui::InputText(buff, &objectRender.m_sRenderinName);


				if (ImGui::CollapsingHeader("IDs"))
				{
					if (ImGui::Button("+"))
						objectRender.m_ids.push_back(0);
					for (size_t id = 0; id < objectRender.m_ids.size(); id++)
					{
						char buff[128];
						sprintf(buff, "ID###idInputInt%d%d%d", spl, i, id);
						ImGui::InputInt(buff, &objectRender.m_ids[id]);
						ImGui::SameLine();
						sprintf(buff, "-###objsremovebtn%d%d", i, id);
						if (ImGui::Button(buff))
							objectRender.m_ids.erase(objectRender.m_ids.begin() + i);
					}
				}
				ImGui::TreePop();
			}
		}
	}
	// 3dTexts
	if (ImGui::CollapsingHeader("3dTexts"))
	{
		if (ImGui::Button("Create New 3DText Render"))
			m_text3dRenders.emplace_back(Text3dRender());
		for (size_t i = 0; i < m_text3dRenders.size(); i++)
		{
			auto&& text3dRender = m_text3dRenders[i];
			char buff[128];

			sprintf(buff, "%s###3dtextEditor%d%d", text3dRender.m_sName.c_str(), spl, i);
			ImGui::Bullet();
			if (ImGui::TreeNode(buff))
			{
				sprintf(buff, "Delete###3dtextdeletebtn%d%d", spl, i);
				if (ImGui::Button(buff))
				{
					m_text3dRenders.erase(m_text3dRenders.begin() + i);
					i--;
				}
				sprintf(buff, "Name###3dtextname%d%d", spl, i);
				ImGui::InputText(buff, &text3dRender.m_sName);
				sprintf(buff, "Rendering Name###3dtextRenderinsname%d%d", spl, i);
				ImGui::InputText(buff, &text3dRender.m_sRenderinName);

				if (ImGui::CollapsingHeader("Texts"))
				{
					sprintf(buff, "+###plusText%d%d", spl, i);
					if (ImGui::Button(buff))
						text3dRender.m_textToSearch.emplace_back("");
					for (size_t id = 0; id < text3dRender.m_textToSearch.size(); id++)
					{
						char buff[128];
						sprintf(buff, "Text###%d%d%d", spl, i, id);
						ImGui::InputText(buff, &text3dRender.m_textToSearch[id]);
						ImGui::SameLine();
						sprintf(buff, "-###3DTEXTremovebtn%d%d%d", spl, i, id);
						if (ImGui::Button(buff))
							text3dRender.m_textToSearch.erase(text3dRender.m_textToSearch.begin() + i);
					}
				}
				ImGui::TreePop();
			}

		}
	}

}

void RenderClass::drawMenu(size_t i)
{

	char buff[128];
	memset(buff, 0, 128);
	sprintf(buff, "%s###classCheckbox%d", m_sName.c_str(), i);
	ImGui::Checkbox(buff, &m_bIsEnabled);

	sprintf(buff, "Objects###classObjectsPopup%d", i);
	if (ImGui::BeginPopupContextItem(buff))
	{
		char buff2[128];
		for (size_t j = 0; j < m_objectsRenders.size(); j++)
		{
			sprintf(buff2, "%s###object%dInClass%d", m_objectsRenders[j].m_sName.c_str(), j, i);
			ImGui::Checkbox(buff2, &m_objectsRenders[j].m_bIsEnabled);
		}
		for (size_t j = 0; j < m_pickupRenders.size(); j++)
		{
			sprintf(buff2, "%s###pickup%dInClass%d", m_pickupRenders[j].m_sName.c_str(), j, i);
			ImGui::Checkbox(buff2, &m_pickupRenders[j].m_bIsEnabled);
		}
		for (size_t j = 0; j < m_text3dRenders.size(); j++)
		{
			sprintf(buff2, "%s###text3d%dInClass%d", m_text3dRenders[j].m_sName.c_str(), j, i);
			ImGui::Checkbox(buff2, &m_text3dRenders[j].m_bIsEnabled);
		}

		ImGui::EndPopup();
	}

}

void CustomRender::drawMenu()
{
	if (ImGui::Begin("Custom Render Menu", &m_bIsMenuOpened))
	{
		for (size_t i = 0; i < m_classes.size(); i++)
			m_classes[i].drawMenu(i);
		ImGui::End();
	}
}

void CustomRender::onDrawGUI()
{
	ImGui::Checkbox("CustomRender", &m_bEnabled);
	if (ImGui::IsItemClicked())
		m_bIsMenuOpened = true;
	ImGui::SameLine();
	ImGui::Checkbox("Editor###customRenderEditorCb", &m_bIsEditorWindowOpened);
	ImGui::SameLine();
	ImGui::Checkbox("Menu###customRenderEditorMenu", &m_bDrawMenu);
	if (m_bDrawMenu)
		drawMenu();
	if (m_bIsEditorWindowOpened)
	{
		ImGui::Begin("EDITOR");
		// Create Object Menu
		{
			if (ImGui::BeginMenu("Create"))
			{

				static char name[128];
				ImGui::InputText("Class Name", name, 128);
				if (ImGui::Button("Create"))
					m_classes.emplace_back(RenderClass(name));

				ImGui::EndMenu();
			}
		}

		char buff[128];
		static int iChoosenClassToEdit = -1;

		for (size_t i = 0; i < m_classes.size(); i++)
		{
			ImGui::TextColored(ImVec4(0, 1, 0, 1), m_classes[i].m_sName.c_str());
			if (ImGui::IsItemClicked())
				iChoosenClassToEdit = i;
			ImGui::SameLine();
			sprintf(buff, "Delete###deleteclassBTN%d", i);
			if (ImGui::Button(buff))
				m_classes.erase(m_classes.begin() + i);
		}
		if (iChoosenClassToEdit != -1)
		{
			ImGui::Begin("Editor");

			m_classes[iChoosenClassToEdit].drawEditor(iChoosenClassToEdit);

			ImGui::End();
		}

		ImGui::End();
	}
}

bool CustomRender::areAnyClassesEnabled()
{
	for (auto&& classR : m_classes)
		if (classR.m_bIsEnabled)
			return true;
	return false;
}

void CustomRender::onDrawHack()
{
	if (!areAnyClassesEnabled())
		return;
	D3D::CalcScreenCoords(PEDSELF->GetPosition(), &customRenderData.onScreenPedCoords);

	for (int i = 0; i < SAMP_MAX_OBJECTS; i++)
	{

		if (!Pools::isObjectExist(i))
			continue;

		static RenderPickup_ObjectData ObjectData;
		CVector vecWorld;
		vecWorld.fX = object[i]->pGTAEntity->base.matrix[4 * 3];
		vecWorld.fY = object[i]->pGTAEntity->base.matrix[4 * 3 + 1];
		vecWorld.fZ = object[i]->pGTAEntity->base.matrix[4 * 3 + 2];

		D3D::CalcScreenCoords(&vecWorld, &ObjectData.onScreenCoords);

		if (ObjectData.onScreenCoords.fZ < 0.01f)
			continue;
		ObjectData.fDistance = Stuff::getDistanceBetween(PEDSELF->GetPosition(), vecWorld);
		ObjectData.id = i;
		ObjectData.iModel = object[i]->iModel;
		for (auto&& classR : m_classes)
			if (classR.m_bIsEnabled)
				if (classR.areAnyObjectRendersEnabled())
					classR.renderObjects(&ObjectData);
	}


	for (int i = 0; i < SAMP_MAX_PICKUPS; i++)
	{

		if (!Pools::isPickupExist(i))
			continue;

		static RenderPickup_ObjectData PickupData;
		CVector vecWorld;
		vecWorld.fX = pickup[i].fPosition[0];
		vecWorld.fY = pickup[i].fPosition[1];
		vecWorld.fZ = pickup[i].fPosition[2];
		D3D::CalcScreenCoords(&vecWorld, &PickupData.onScreenCoords);
		if (PickupData.onScreenCoords.fZ < 0.01f)
			continue;

		PickupData.fDistance = Stuff::getDistanceBetween(PEDSELF->GetPosition(), vecWorld);
		PickupData.id = i;
		PickupData.iModel = pickup[i].iModelID;
		for (auto&& classR : m_classes)
			if (classR.m_bIsEnabled)
				if (classR.areAnyickupRendersEnabled())
					classR.renderPickups(&PickupData);
	}

	for (int i = 0; i < SAMP_MAX_3DTEXTS; i++)
	{
		if (!Pools::is3DTextExist(i))
			continue;
		static Render3DTextData Text3DData;
		CVector vecWorld;
		vecWorld.fX = text3d[i].fPosition[0];
		vecWorld.fY = text3d[i].fPosition[1];
		vecWorld.fZ = text3d[i].fPosition[2];
		D3D::CalcScreenCoords(&vecWorld, &Text3DData.onScreenCoords);
		if (Text3DData.onScreenCoords.fZ < 0.01f)
			continue;
		Text3DData.fDistance = Stuff::getDistanceBetween(PEDSELF->GetPosition(), vecWorld);
		Text3DData.id = i;
		Text3DData.szText = text3d[i].pText;
		for (auto&& classR : m_classes)
			if (classR.m_bIsEnabled)
				if (classR.areAnyText3DRendersEnabled())
					classR.render3DTexts(&Text3DData);
	}

}

void CustomRender::read(nlohmann::json& data)
{
	m_bEnabled = data["CustomRender"].get<bool>();
	size_t i = 0;
	while (true)
	{
		if (data["class"][std::to_string(i).c_str()].is_null())
			break;
		m_classes.emplace_back(RenderClass("dummy"));
		m_classes[i].read(data["class"][std::to_string(i).c_str()]);
		i++;
	}
}
void CustomRender::save(nlohmann::json& data)
{
	data["CustomRender"] = m_bEnabled;
	for (size_t i = 0; i < m_classes.size(); i++)
		m_classes[i].save(data["class"][std::to_string(i).c_str()]);

}
void ObjectRender::save(nlohmann::json& data)
{
	data["IDS"] = m_ids;
	data["name"] = m_sName;
	data["renderingName"] = m_sRenderinName;
	data["enabled"] = m_bIsEnabled;
}
void ObjectRender::read(nlohmann::json& data)
{
	m_ids = data["IDS"].get<std::vector<int>>();
	m_sName = data["name"].get<std::string>();
	m_sRenderinName = data["renderingName"].get<std::string>();
	m_bIsEnabled = data["enabled"].get<bool>();

}
void PickupRender::save(nlohmann::json& data)
{
	data["IDS"] = m_ids;
	data["name"] = m_sName;
	data["renderingName"] = m_sRenderinName;
	data["enabled"] = m_bIsEnabled;
}
void PickupRender::read(nlohmann::json& data)
{
	m_ids = data["IDS"].get<std::vector<int>>();
	m_sName = data["name"].get<std::string>();
	m_sRenderinName = data["renderingName"].get<std::string>();
	m_bIsEnabled = data["enabled"].get<bool>();
}
void Text3dRender::save(nlohmann::json& data)
{
	data["enabled"] = m_bIsEnabled;
	data["texts"] = m_textToSearch;
	data["name"] = m_sName;
	data["renderingName"] = m_sRenderinName;
}
void Text3dRender::read(nlohmann::json& data)
{
	m_textToSearch = data["texts"].get<std::vector<std::string>>();
	m_sName = data["name"].get<std::string>();
	m_sRenderinName = data["renderingName"].get<std::string>();
	m_bIsEnabled = data["enabled"].get<bool>();
}
void RenderClass::save(nlohmann::json& data)
{
	data["name"] = m_sName;
	data["enabled"] = m_bIsEnabled;
	for (size_t i = 0; i < m_objectsRenders.size(); i++)
		m_objectsRenders[i].save(data["rendersObj"][std::to_string(i).c_str()]);
	for (size_t i = 0; i < m_pickupRenders.size(); i++)
		m_pickupRenders[i].save(data["rendersPick"][std::to_string(i).c_str()]);
	for (size_t i = 0; i < m_text3dRenders.size(); i++)
		m_text3dRenders[i].save(data["renders3DText"][std::to_string(i).c_str()]);
}
void RenderClass::read(nlohmann::json& data)
{
	m_sName = data["name"].get<std::string>();
	m_bIsEnabled = data["enabled"].get<bool>();
	size_t i = 0;
	while (true)
	{
		if (data["rendersObj"][std::to_string(i).c_str()].is_null())
			break;
		m_objectsRenders.emplace_back(ObjectRender());
		m_objectsRenders[i].read(data["rendersObj"][std::to_string(i).c_str()]);
		i++;
	}
	i = 0;
	while (true)
	{
		if (data["rendersPick"][std::to_string(i).c_str()].is_null())
			break;
		m_pickupRenders.emplace_back(PickupRender());
		m_pickupRenders[i].read(data["rendersPick"][std::to_string(i).c_str()]);
		i++;
	}
	i = 0;
	while (true)
	{
		if (data["renders3DText"][std::to_string(i).c_str()].is_null())
			break;

		m_text3dRenders.emplace_back(Text3dRender());
		m_text3dRenders[i].read(data["renders3DText"][std::to_string(i).c_str()]);
		i++;
	}
}
void RenderClass::renderPickups(RenderPickup_ObjectData* pRenderPickupData)
{
	for (auto&& pRender : m_pickupRenders)
		if (pRender.m_bIsEnabled)
			pRender.render(pRenderPickupData);
}
void RenderClass::renderObjects(RenderPickup_ObjectData* pRenderObjectData)
{
	for (auto&& pRender : m_objectsRenders)
		if (pRender.m_bIsEnabled)
			pRender.render(pRenderObjectData);
}
void RenderClass::render3DTexts(Render3DTextData* p3DTextData)
{
	for (auto&& pRender : m_text3dRenders)
		if (pRender.m_bIsEnabled)
			pRender.render(p3DTextData);
}

CustomRender::CustomRender(const char* szName)
{
	this->m_sHackName = szName;
	m_bEnabled = false;
	this->customRenderData.vec4Color.w = 1.f;
	this->customRenderData.vec4Color.z = 1.f;
	this->customRenderData.font.Init();
}
RenderClass::RenderClass(const char* szName)
{
	m_sName = szName;
}
void ObjectRender::render(RenderPickup_ObjectData* pRenderObjectData)
{
	if (std::find(m_ids.begin(), m_ids.end(), pRenderObjectData->iModel) != m_ids.end())
	{
		UINT32 color = ImGui::ColorConvertFloat4ToU32(CustomRender::customRenderData.vec4Color);

		SF->getRender()->DrawLine(pRenderObjectData->onScreenCoords.fX,
			pRenderObjectData->onScreenCoords.fY, CustomRender::customRenderData.onScreenPedCoords.fX,
			CustomRender::customRenderData.onScreenPedCoords.fY, 1, color);

		SF->getRender()->DrawPolygon(pRenderObjectData->onScreenCoords.fX,
			pRenderObjectData->onScreenCoords.fY, 3, 3, 0.0, 8, color);

		char buf[128];
		sprintf(buf, "%s {ffffff}[%1.f]", Lippets::Strings::UTF8_to_CP1251(m_sRenderinName).c_str(), pRenderObjectData->fDistance);
		CustomRender::customRenderData.font.f->Print(buf, color, pRenderObjectData->onScreenCoords.fX + 5, pRenderObjectData->onScreenCoords.fY - 7, false);
	}
}
void Text3dRender::render(Render3DTextData* p3DTextData)
{
	for (auto&& toSearch : m_textToSearch)
		if (!strstr(p3DTextData->szText, (toSearch).c_str()))
			return;

	UINT32 color = ImGui::ColorConvertFloat4ToU32(CustomRender::customRenderData.vec4Color);

	SF->getRender()->DrawLine(p3DTextData->onScreenCoords.fX,
		p3DTextData->onScreenCoords.fY, CustomRender::customRenderData.onScreenPedCoords.fX,
		CustomRender::customRenderData.onScreenPedCoords.fY, 1, color);

	SF->getRender()->DrawPolygon(p3DTextData->onScreenCoords.fX,
		p3DTextData->onScreenCoords.fY, 3, 3, 0.0, 8, color);

	char buf[128];
	sprintf(buf, "%s {ffffff}[%1.f]", (m_sName).c_str(), p3DTextData->fDistance);
	CustomRender::customRenderData.font.f->Print(buf, color, p3DTextData->onScreenCoords.fX + 5, p3DTextData->onScreenCoords.fY - 7, false);

}
void PickupRender::render(RenderPickup_ObjectData* pRenderPickupData)
{
	if (std::find(m_ids.begin(), m_ids.end(), pRenderPickupData->iModel) != m_ids.end())
	{
		UINT32 color = ImGui::ColorConvertFloat4ToU32(CustomRender::customRenderData.vec4Color);

		SF->getRender()->DrawLine(pRenderPickupData->onScreenCoords.fX,
			pRenderPickupData->onScreenCoords.fY, CustomRender::customRenderData.onScreenPedCoords.fX,
			CustomRender::customRenderData.onScreenPedCoords.fY, 1, color);

		SF->getRender()->DrawPolygon(pRenderPickupData->onScreenCoords.fX,
			pRenderPickupData->onScreenCoords.fY, 3, 3, 0.0, 8, color);

		char buf[128];
		sprintf(buf, "%s {ffffff}[%1.f]", (m_sRenderinName).c_str(), pRenderPickupData->fDistance);
		CustomRender::customRenderData.font.f->Print(buf, color, pRenderPickupData->onScreenCoords.fX + 5, pRenderPickupData->onScreenCoords.fY - 7, false);
	}
}
bool RenderClass::areAnyObjectRendersEnabled()
{
	for (auto&& pRender : m_objectsRenders)
		if (pRender.m_bIsEnabled)
			return true;
	return false;
}
bool RenderClass::areAnyickupRendersEnabled()
{
	for (auto&& pRender : m_pickupRenders)
		if (pRender.m_bIsEnabled)
			return true;
	return false;
}
bool RenderClass::areAnyText3DRendersEnabled()
{
	for (auto&& pRender : m_text3dRenders)
		if (pRender.m_bIsEnabled)
			return true;
	return false;
}