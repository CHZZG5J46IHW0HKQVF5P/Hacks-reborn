#pragma once
#include "windows.h"
#include <string>
#include <vector>
#include <filesystem>
#include "tlhelp32.h"
namespace fs = std::filesystem;
namespace Lippets
{
	namespace Computer // Files & Memory
	{
		std::string getFileDirectoryPath(const std::string& filename);
		bool isPathExits(const std::string& path);
		bool isFileExits(const std::string& filename);
		bool createDirs(const std::string& path);
		// -std=c++17 -lstdc++fs
		std::vector<fs::path> GetDirContent(const char* path, const char* extension);
		template <typename T>
		void WriteMem(DWORD dwAddr, size_t size, T value, bool protection = true)
		{
			if (protection)
			{
				DWORD NewProtection;
				VirtualProtect((DWORD*)dwAddr, size, PAGE_EXECUTE_READWRITE, &NewProtection);
				*reinterpret_cast<T*>(dwAddr) = value;
				VirtualProtect((DWORD*)dwAddr, size, NewProtection, &NewProtection);
			}
			else
				*reinterpret_cast<T*>(dwAddr) = value;
		}
		DWORD FindProcessId(const std::string& processName);
		uintptr_t GetModuleBaseAddress(DWORD procId, const char* modName);
		void WriteMem(void* address, void* bytes, size_t byteSize);
		void SetClipboardText(const std::string& txt);
	} // namespace Computer
} // namespace Lippets
using Lippets::Computer::WriteMem;

inline bool Lippets::Computer::createDirs(const std::string& path)
{
	return fs::create_directories(path);
}

inline std::string Lippets::Computer::getFileDirectoryPath(const std::string& filename) {
	fs::path path = fs::canonical(filename);
	std::string buffer = path.string();
	buffer.erase(buffer.end() - filename.size(), buffer.end());
	return buffer;
}

inline bool Lippets::Computer::isPathExits(const std::string& path)
{
	return fs::is_directory(path);
}
inline bool Lippets::Computer::isFileExits(const std::string& filename)
{
	return fs::exists(filename);
}

// -std=c++17 -lstdc++fs
inline std::vector<fs::path> Lippets::Computer::GetDirContent(const char* path, const char* extension)
{
	std::vector<fs::path> arr;
	if (extension)
	{
		for (const auto& entry : fs::directory_iterator(path))
		{
			if (entry.path().extension() == extension)
				arr.emplace_back(entry.path());
		}
	}
	else
	{
		for (const auto& entry : fs::directory_iterator(path))
		{
			arr.emplace_back(entry.path());
		}
	}
	return arr;
}

inline void Lippets::Computer::WriteMem(void* address, void* bytes, size_t byteSize)
{
	DWORD NewProtection;
	VirtualProtect(address, byteSize, PAGE_EXECUTE_READWRITE, &NewProtection);
	memcpy(address, bytes, byteSize);
	VirtualProtect(address, byteSize, NewProtection, &NewProtection);
}
inline void Lippets::Computer::SetClipboardText(const std::string& txt)
{
	if (!OpenClipboard(0))
		return;

	// Remove the current Clipboard contents
	if (!EmptyClipboard())
		return;
	// Get the currently selected data
	HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, 64);
	strcpy_s((char*)hGlob, txt.length() + 1, txt.c_str());
	// For the appropriate data formats...
	if (SetClipboardData(CF_TEXT, hGlob) == NULL)
	{
		CloseClipboard();
		GlobalFree(hGlob);
		return;
	}
	CloseClipboard();
}

inline DWORD Lippets::Computer::FindProcessId(const std::string& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}
inline uintptr_t Lippets::Computer::GetModuleBaseAddress(DWORD procId, const char* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_stricmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}