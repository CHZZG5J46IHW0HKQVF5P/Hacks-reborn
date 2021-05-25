#pragma once
#include "windows.h"
#include <string>
#include <vector>
#include <filesystem>
#include "tlhelp32.h"
namespace fs = std::experimental::filesystem;
namespace Lippets
{
	namespace Computer // Files & Memory
	{
		bool isPathExits(const std::string &path);
		bool isFileExits(const std::string &filename);
		bool createDirs(const std::string &path);
		// -std=c++17 -lstdc++fs
		std::vector<std::experimental::filesystem::path> GetDirContent(const char *path, const char *extension);
		template <typename T>
		void WriteMem(DWORD dwAddr, size_t size, T value, bool protection = true)
		{
			if (protection)
			{
				DWORD NewProtection;
				VirtualProtect((DWORD *)dwAddr, size, PAGE_EXECUTE_READWRITE, &NewProtection);
				*reinterpret_cast<T *>(dwAddr) = value;
				VirtualProtect((DWORD *)dwAddr, size, NewProtection, &NewProtection);
			}
			else
				*reinterpret_cast<T *>(dwAddr) = value;
		}
		DWORD FindProcessId(const std::string& processName);
		uintptr_t GetModuleBaseAddress(DWORD procId, const char* modName);
		void WriteMem(void *address, void *bytes, size_t byteSize);
		void SetClipboardText(const std::string &txt);
	} // namespace Computer
} // namespace Lippets
using Lippets::Computer::WriteMem;