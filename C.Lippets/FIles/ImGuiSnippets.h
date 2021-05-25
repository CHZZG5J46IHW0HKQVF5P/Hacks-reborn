#pragma once
#ifdef IMGUI_API
#include "KeyboardMouse.h"
#include <string>
#include <cstring>

namespace Lippets
{
	namespace ImGuiSnippets
	{
		inline void BeginFullWindowMenu(const char* name, float weight, float hight, float x, float y)
		{
			ImGui::SetNextWindowPos(ImVec2(x, y));
			ImGui::SetNextWindowSize(ImVec2(weight, hight));
			ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_WindowRounding, 0.f);
			ImGui::Begin(name, NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			ImGui::PopStyleVar();
		}
		inline  bool BorderedInputInt(const char* label, int* v, int min, int max, int step, int step_fast)
		{
			bool r = ImGui::InputInt(label, v, step, step_fast, 0);
			if (*v <= min)
				*v = min;
			if (*v >= max)
				*v = max;
			return r;
		}

		//     bool KeyButton2(int& key, int& iLastPressedKey, int &Spliter)
		//     {
				 //static std::unordered_map<int, std::string> *keys = nullptr;
				 //if (!keys)
				 //{
				 //	keys = new std::unordered_map<int, std::string>;
				 //	Lippets::KeyNames::initKeys(keys);
				 //}
				 //Spliter++;
		//         char szKey[64];
		//         bool ret = false;
		//         if (key > 0 && key < 223)
		//             sprintf_s(szKey, "%s###keybutton%d", (*keys)[key].c_str(), Spliter);
		//         else
		//         {
		//             sprintf_s(szKey, "...###keybutton%d", Spliter);
		//             if (iLastPressedKey != 0 && iLastPressedKey != 1)
		//             {
		//                 key = iLastPressedKey;
		//                 iLastPressedKey = 0;
		//                 ret = true;
		//             }
		//         }
		//         if (ImGui::Button(szKey))
		//         {
		//             ret = true;
		//             key = 0;
		//         }
		//         return ret;
		//     }
		inline bool KeyButton(int& key, int &Spliter)
		{
			Spliter++;
			static std::unordered_map<int, std::string> *keys = nullptr;
			if (!keys)
			{
				keys = new std::unordered_map<int, std::string>;
				Lippets::KeyNames::initKeys(keys);
			}
			char szKey[64];
			if (key > 3 && key < 223)
			{

				sprintf_s(szKey, "%s###%dkeybutton%d", keys->at(key).c_str(), key, Spliter);
			}
			else
			{
				sprintf_s(szKey, "...###%dkeybutton%d", key, Spliter);
				for (int i = 4; i < 223; i++)
				{
					//if (i == 16 || i == 17 || i == 18)
					//    continue;
					GetAsyncKeyState(i);
					if (GetAsyncKeyState(i))
					{
						key = i;
						return true;
					}
				}
			}
			if (ImGui::Button(szKey))
				key = 0;

			return false;
		}
		inline void RainBowSeparator(float& flRainbow, float flSpeed, int height)
		{
			ImVec2 pos = ImGui::GetCursorPos();
			ImVec2 wpos = ImGui::GetWindowPos();
			pos.x += wpos.x;
			pos.y += wpos.y;
			ImDrawList* windowDrawList = ImGui::GetWindowDrawList();
			float w = ImGui::GetWindowWidth();
			flRainbow += flSpeed;
			if (flRainbow > 1.f)
				flRainbow = 0.f;
			for (int i = 0; i < w; i++)
			{
				float hue = (1.f / (float)w) * i;
				hue -= flRainbow;
				if (hue < 0.f)
					hue += 1.f;
				windowDrawList->AddRectFilled(ImVec2(pos.x + i, pos.y), ImVec2(pos.x + w, pos.y + height), ImColor::HSV(hue, 1.f, 1.f));
			}
			pos = ImGui::GetCursorPos();
			ImGui::SetCursorPos(ImVec2(pos.x, pos.y + height * 2.f));
		}
		inline void HelpMarker(const char* desc, bool sameline)
		{
			if (sameline)
				ImGui::SameLine();
			ImGui::TextDisabled("(?)");
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(desc);
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
		}
		inline void HelpMarker2(const std::string &desc, bool sameline)
		{
			if (sameline)
				ImGui::SameLine();
			ImGui::TextDisabled("(?)");
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(desc.c_str());
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
		}
	} // namespace ImGuiSnippets
} // namespace Lippets
#endif