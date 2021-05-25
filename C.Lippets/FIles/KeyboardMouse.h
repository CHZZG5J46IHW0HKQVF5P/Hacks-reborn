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
		void init(UINT msg, WPARAM wParam);
		KeyEvenByWndProc() {}
	};
    namespace KeyBoard
    {
        std::string GetKeyName(UINT KEY);
        void GetKeyName(UINT KEY, char *outbuffer);
        UINT GetScanCodeByVK(UINT VK);
        UINT GetVKCodeByScan(UINT SCAN);
        void SendKeyRelease(UINT key, ULONG_PTR dwExtraInfo);
        void SendKeyPressed(UINT key, ULONG_PTR dwExtraInfo);
        void SendKeyPress(UINT key, std::chrono::milliseconds delay, ULONG_PTR dwExtraInfo);
        std::string GetKeyBoardLocaleName();
    } // namespace KeyBoard
    namespace Mouse
    {
		
        struct LLMouseProc
        {
            int iMouseButton;
            bool bDown;
            bool bInitialized = false;
            LLMouseProc(WPARAM wParam, PMSLLHOOKSTRUCT params);
        };
		std::string GetMouseKeyName(UINT8 btn);
		void SendMouseKeyPressed(UINT8 btn, ULONG_PTR dwExtraInfo);
		void SendMouseKeyRelease(UINT8 btn, ULONG_PTR dwExtraInfo);
		void SendMouseKeyPress(UINT8 btn, ULONG_PTR dwExtraInfo);
		void SendMouseKeyPress(UINT8 btn, std::chrono::milliseconds delay, ULONG_PTR dwExtraInfo);

    } // namespace Mouse
    namespace KeyNames
    {
        struct Key
        {
            int wKeyID;
            std::string name;
        };
        void initKeys(std::unordered_map<int, std::string> *keys);
    }; // namespace Names
} // namespace Lippets"