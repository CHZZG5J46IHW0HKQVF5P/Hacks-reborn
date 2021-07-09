#pragma once
#include "windows.h"
#include <thread>
#include <unordered_map>
#include <string>
namespace Lippets
{
	struct KeyEvenByWndProc
	{
		int iKeyID = 0;
		bool bDown = 0;
		bool init(UINT msg, WPARAM wParam);
		inline KeyEvenByWndProc() {}
	};
	namespace KeyBoard
	{
		std::string  GetKeyName(UINT KEY);
		void  GetKeyName(UINT KEY, char* outbuffer);
		UINT  GetScanCodeByVK(UINT VK);
		UINT  GetVKCodeByScan(UINT SCAN);
		void  SendKeyRelease(UINT key, ULONG_PTR dwExtraInfo);
		void  SendKeyPress(UINT key, ULONG_PTR dwExtraInfo);
		void  SendKeyPressed(UINT key, std::chrono::milliseconds delay, ULONG_PTR dwExtraInfo);
		std::string  GetKeyBoardLocaleName();
	} // namespace KeyBoard
	namespace Mouse
	{

		struct LLMouseProc
		{
			int iMouseButton = 0;
			bool bDown = false;
			bool bInitialized = false;

			LLMouseProc(WPARAM wParam, PMSLLHOOKSTRUCT params);
		};

		std::string  GetMouseKeyName(UINT8 btn);
		void  SendMouseKeyPressed(UINT8 btn, ULONG_PTR dwExtraInfo);
		void  SendMouseKeyRelease(UINT8 btn, ULONG_PTR dwExtraInfo);
		void  SendMouseKeyPress(UINT8 btn, ULONG_PTR dwExtraInfo);
		void  SendMouseKeyPress(UINT8 btn, std::chrono::milliseconds delay, ULONG_PTR dwExtraInfo);

	} // namespace Mouse
	namespace KeyNames
	{
		struct Key
		{
			int wKeyID;
			std::string name;
		};
		std::unordered_map<int, std::string>  initKeys();
		void  initKeys(std::unordered_map<int, std::string>* keys);
	}; // namespace Names
} // namespace Lippets"



inline bool  Lippets::KeyEvenByWndProc::init(UINT msg, WPARAM wParam)
{
	this->bDown = 0;
	this->iKeyID = 0;
	{
		if (msg == WM_LBUTTONDOWN)
		{
			iKeyID = 1;
			bDown = true;
			return true;
		}
		if (msg == WM_LBUTTONUP)
		{
			iKeyID = 1;
			bDown = false;
			return true;
		}
	}
	{
		if (msg == WM_RBUTTONDOWN)
		{
			iKeyID = 4;
			bDown = true;
			return true;
		}
		if (msg == WM_RBUTTONUP)
		{
			iKeyID = 4;
			bDown = false;
			return true;
		}
	}
	{
		if (msg == WM_MBUTTONDOWN)
		{
			iKeyID = 2;
			bDown = true;
			return true;
		}
		if (msg == WM_MBUTTONUP)
		{
			iKeyID = 2;
			bDown = false;
			return true;
		}
	}
	{
		if (msg == WM_XBUTTONDOWN)
		{

			switch (GET_XBUTTON_WPARAM(wParam))
			{
			case XBUTTON1:
				iKeyID = 5;
				break;
			case XBUTTON2:
				iKeyID = 6;
				break;
			default:
				break;
			}

			bDown = true;
			return true;
		}
		if (msg == WM_XBUTTONUP)
		{

			switch (GET_XBUTTON_WPARAM(wParam))
			{
			case XBUTTON1:
				iKeyID = 5;
				break;
			case XBUTTON2:
				iKeyID = 6;
				break;
			default:
				break;
			}
			bDown = false;
			return true;
		}
	}

	if (msg == WM_KEYDOWN || msg == WM_LBUTTONDOWN || msg == WM_SYSKEYDOWN || msg == WM_MBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_XBUTTONDOWN)
	{
		iKeyID = wParam;
		bDown = true;
		return true;
	}

	if (msg == WM_KEYUP || msg == WM_LBUTTONUP || msg == WM_SYSKEYUP || msg == WM_MBUTTONUP || msg == WM_RBUTTONUP || msg == WM_XBUTTONUP)
	{
		iKeyID = wParam;
		bDown = false;
		return true;
	}
	return false;
}

inline Lippets::Mouse::LLMouseProc::LLMouseProc(WPARAM wParam, PMSLLHOOKSTRUCT params)
{
	bInitialized = true;
	switch (wParam)
	{
	case WM_XBUTTONUP:
		bDown = false;
		if (params->mouseData == 65536) // X2
			iMouseButton = 6;
		else if (params->mouseData == 131072) // X1
			iMouseButton = 5;
		break;
	case WM_XBUTTONDOWN:
		bDown = true;
		if (params->mouseData == 65536) // X2
			iMouseButton = 6;
		else if (params->mouseData == 131072) // X1
			iMouseButton = 5;
		break;
	case WM_MBUTTONDOWN:
		iMouseButton = 2;
		bDown = true;
		break;
	case WM_MBUTTONUP:
		iMouseButton = 2;
		bDown = false;
		break;
	case WM_LBUTTONDOWN:
		iMouseButton = 1;
		bDown = true;
		break;
	case WM_LBUTTONUP:
		iMouseButton = 1;
		bDown = false;
		break;
	case WM_RBUTTONDOWN:
		iMouseButton = 4;
		bDown = true;
		break;
	case WM_RBUTTONUP:
		iMouseButton = 4;
		bDown = false;
		break;
	default:
		bInitialized = false;
		break;
	}
}
inline std::string Lippets::KeyBoard::GetKeyName(UINT KEY)
{
	char outbuffer[65];
	GetKeyNameTextA((MapVirtualKeyA(KEY, MAPVK_VK_TO_VSC) << 16), outbuffer, 64);
	return outbuffer;
}
inline void Lippets::KeyBoard::GetKeyName(UINT KEY, char* outbuffer)
{
	GetKeyNameTextA((MapVirtualKeyA(KEY, MAPVK_VK_TO_VSC) << 16), outbuffer, strlen(outbuffer) - 1);
}
inline UINT Lippets::KeyBoard::GetScanCodeByVK(UINT VK)
{
	return MapVirtualKeyA(VK, MAPVK_VK_TO_VSC);
}
inline UINT Lippets::KeyBoard::GetVKCodeByScan(UINT SCAN)
{
	return MapVirtualKeyA(SCAN, MAPVK_VSC_TO_VK);
}
inline void Lippets::KeyBoard::SendKeyRelease(UINT key, ULONG_PTR dwExtraInfo)
{
	keybd_event(key, GetScanCodeByVK(key), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, dwExtraInfo);
}
inline void Lippets::KeyBoard::SendKeyPress(UINT key, ULONG_PTR dwExtraInfo)
{
	keybd_event(key, GetScanCodeByVK(key), KEYEVENTF_EXTENDEDKEY | 0, dwExtraInfo);
}
inline void Lippets::KeyBoard::SendKeyPressed(UINT key, std::chrono::milliseconds delay, ULONG_PTR dwExtraInfo)
{
	SendKeyPress(key, dwExtraInfo);
	std::this_thread::sleep_for(delay);
	SendKeyPress(key, dwExtraInfo);
}
inline std::string Lippets::KeyBoard::GetKeyBoardLocaleName()
{
	char OutBuff[64];
	GetKeyboardLayoutNameA(OutBuff);
	GetLocaleInfoA(strtol(OutBuff, (char**)OutBuff[strlen(OutBuff)], 16), 0x00000002, OutBuff, 64);
	return OutBuff;
}

inline std::string Lippets::Mouse::GetMouseKeyName(UINT8 btn)
{
	switch (btn)
	{
	case 1:
		return "LBUTTON";

	case 2:
		return "RBUTTON";

	case 4:
		return "MBUTTON";

	default:
		return "???";
	}
}
inline void Lippets::Mouse::SendMouseKeyPressed(UINT8 btn, ULONG_PTR dwExtraInfo)
{
	switch (btn)
	{
	case 1:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, dwExtraInfo);
		break;

	case 2:
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, dwExtraInfo);
		break;

	case 4:
		mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, dwExtraInfo);
		break;

	default:
		return;
	}
}
inline void Lippets::Mouse::SendMouseKeyRelease(UINT8 btn, ULONG_PTR dwExtraInfo)
{
	switch (btn)
	{
	case 1:
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, dwExtraInfo);
		break;

	case 2:
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, dwExtraInfo);
		break;

	case 4:
		mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, dwExtraInfo);
		break;

	default:
		return;
	}
}
inline void Lippets::Mouse::SendMouseKeyPress(UINT8 btn, ULONG_PTR dwExtraInfo)
{
	SendMouseKeyPressed(btn, dwExtraInfo);
	SendMouseKeyRelease(btn, dwExtraInfo);
}
inline void Lippets::Mouse::SendMouseKeyPress(UINT8 btn, std::chrono::milliseconds delay, ULONG_PTR dwExtraInfo)
{
	SendMouseKeyPressed(btn, dwExtraInfo);
	std::this_thread::sleep_for(delay);
	SendMouseKeyRelease(btn, dwExtraInfo);
}

inline std::unordered_map<int, std::string> Lippets::KeyNames::initKeys()
{
	static const Key tmpkeys[] = {
		{0, "UNKNOWN"},
		{1, "LBUTTON"},
		{2, "MBUTTON"},
		{4, "RBUTTON"},
		{5, "XBUTTON1"},
		{6, "XBUTTON2"},
		{112, "F1"},
		{113, "F2"},
		{114, "F3"},
		{115, "F4"},
		{116, "F5"},
		{117, "F6"},
		{118, "F7"},
		{119, "F8"},
		{120, "F9"},
		{121, "F10"},
		{122, "F11"},
		{123, "F12"},
		{32, "SPACE"},
		{8, "BackSpace"},
		{9, "TAB"},
		{13, "Enter"},
		{16, "Shift"},
		{17, "Ctrl"},
		{18, "Alt"},
		{20, "CapsLock"},
		{27, "ESCAPE"},
		{45, "INSERT"},
		{33, "PageUp"},
		{34, "PageDown"},
		{35, "END"},
		{36, "HOME"},
		{37, "LEFT"},
		{38, "UP"},
		{39, "RIGHT"},
		{40, "DOWN"},
		{46, "Delete"},
		{44, "PrintScreen"},
		{145, "ScrollLock"},
		{48, "0"},
		{49, "1"},
		{50, "2"},
		{51, "3"},
		{52, "4"},
		{53, "5"},
		{54, "6"},
		{55, "7"},
		{56, "8"},
		{57, "9"},
		{192, "~"},
		{189, "_"},
		{187, "="},
		{219, "["},
		{221, "]"},
		{186, ";"},
		{220, "|"},
		{188, ","},
		{190, "."},
		{191, "/"},
		{65, "A"},
		{66, "B"},
		{67, "C"},
		{68, "D"},
		{69, "E"},
		{70, "F"},
		{71, "G"},
		{72, "H"},
		{73, "I"},
		{74, "J"},
		{75, "K"},
		{76, "L"},
		{77, "M"},
		{78, "N"},
		{79, "O"},
		{80, "P"},
		{81, "Q"},
		{82, "R"},
		{83, "S"},
		{84, "T"},
		{85, "U"},
		{86, "V"},
		{87, "W"},
		{88, "X"},
		{89, "Y"},
		{90, "Z"},
		{96, "NUMPAD0"},
		{97, "NUMPAD1"},
		{98, "NUMPAD2"},
		{99, "NUMPAD3"},
		{100, "NUMPAD4"},
		{101, "NUMPAD5"},
		{102, "NUMPAD6"},
		{103, "NUMPAD7"},
		{104, "NUMPAD8"},
		{105, "NUMPAD9"},
		{106, "MULTIPLY"},
		{107, "ADD"},
		{108, "SUBTRACT"},
		{109, "DECIMAL"},
		{110, "DIVIDE"},
	};
	std::unordered_map<int, std::string> toReturn;
	for (int i = 0; i < 100; i++)
		toReturn.insert(toReturn.begin(), std::make_pair(tmpkeys[i].wKeyID, tmpkeys[i].name));
	return toReturn;
}
inline void Lippets::KeyNames::initKeys(std::unordered_map<int, std::string>* keys)
{
	static const Key tmpkeys[] = {
		{0, "UNKNOWN"},
		{1, "LBUTTON"},
		{2, "MBUTTON"},
		{4, "RBUTTON"},
		{5, "XBUTTON1"},
		{6, "XBUTTON2"},
		{112, "F1"},
		{113, "F2"},
		{114, "F3"},
		{115, "F4"},
		{116, "F5"},
		{117, "F6"},
		{118, "F7"},
		{119, "F8"},
		{120, "F9"},
		{121, "F10"},
		{122, "F11"},
		{123, "F12"},
		{32, "SPACE"},
		{8, "BackSpace"},
		{9, "TAB"},
		{13, "Enter"},
		{16, "Shift"},
		{17, "Ctrl"},
		{18, "Alt"},
		{20, "CapsLock"},
		{27, "ESCAPE"},
		{45, "INSERT"},
		{33, "PageUp"},
		{34, "PageDown"},
		{35, "END"},
		{36, "HOME"},
		{37, "LEFT"},
		{38, "UP"},
		{39, "RIGHT"},
		{40, "DOWN"},
		{46, "Delete"},
		{44, "PrintScreen"},
		{145, "ScrollLock"},
		{48, "0"},
		{49, "1"},
		{50, "2"},
		{51, "3"},
		{52, "4"},
		{53, "5"},
		{54, "6"},
		{55, "7"},
		{56, "8"},
		{57, "9"},
		{192, "~"},
		{189, "_"},
		{187, "="},
		{219, "["},
		{221, "]"},
		{186, ";"},
		{220, "|"},
		{188, ","},
		{190, "."},
		{191, "/"},
		{65, "A"},
		{66, "B"},
		{67, "C"},
		{68, "D"},
		{69, "E"},
		{70, "F"},
		{71, "G"},
		{72, "H"},
		{73, "I"},
		{74, "J"},
		{75, "K"},
		{76, "L"},
		{77, "M"},
		{78, "N"},
		{79, "O"},
		{80, "P"},
		{81, "Q"},
		{82, "R"},
		{83, "S"},
		{84, "T"},
		{85, "U"},
		{86, "V"},
		{87, "W"},
		{88, "X"},
		{89, "Y"},
		{90, "Z"},
		{96, "NUMPAD0"},
		{97, "NUMPAD1"},
		{98, "NUMPAD2"},
		{99, "NUMPAD3"},
		{100, "NUMPAD4"},
		{101, "NUMPAD5"},
		{102, "NUMPAD6"},
		{103, "NUMPAD7"},
		{104, "NUMPAD8"},
		{105, "NUMPAD9"},
		{106, "MULTIPLY"},
		{107, "ADD"},
		{108, "SUBTRACT"},
		{109, "DECIMAL"},
		{110, "DIVIDE"},
	};
	for (int i = 0; i < 100; i++)
		keys->insert(keys->begin(), std::make_pair(tmpkeys[i].wKeyID, tmpkeys[i].name));
}