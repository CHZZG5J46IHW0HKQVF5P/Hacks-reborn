#include "Files\Computer.h"

bool Lippets::Computer::isPathExits(const std::string &path)
{
    return std::experimental::filesystem::is_directory(path);
}
bool Lippets::Computer::isFileExits(const std::string &filename)
{
    return std::experimental::filesystem::exists(filename);
}
bool Lippets::Computer::createDirs(const std::string &path)
{
    return std::experimental::filesystem::create_directories(path);
}
// -std=c++17 -lstdc++fs
std::vector<std::experimental::filesystem::path> Lippets::Computer::GetDirContent(const char *path, const char *extension)
{
    std::vector<std::experimental::filesystem::path> arr;
    if (extension)
    {
        for (const auto &entry : fs::directory_iterator(path))
        {
            if (entry.path().extension() == extension)
                arr.emplace_back(entry.path());
        }
    }
    else
    {
        for (const auto &entry : fs::directory_iterator(path))
        {
            arr.emplace_back(entry.path());
        }
    }
    return arr;
}

void Lippets::Computer::WriteMem(void *address, void *bytes, size_t byteSize)
{
    DWORD NewProtection;
    VirtualProtect(address, byteSize, PAGE_EXECUTE_READWRITE, &NewProtection);
    memcpy(address, bytes, byteSize);
    VirtualProtect(address, byteSize, NewProtection, &NewProtection);
}
void Lippets::Computer::SetClipboardText(const std::string &txt)
{
    if (!OpenClipboard(0))
        return;

    // Remove the current Clipboard contents
    if (!EmptyClipboard())
        return;
    // Get the currently selected data
    HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, 64);
    strcpy_s((char *)hGlob, txt.length() + 1, txt.c_str());
    // For the appropriate data formats...
    if (SetClipboardData(CF_TEXT, hGlob) == NULL)
    {
        CloseClipboard();
        GlobalFree(hGlob);
        return;
    }
    CloseClipboard();
}

DWORD Lippets::Computer::FindProcessId(const std::string& processName)
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
uintptr_t Lippets::Computer::GetModuleBaseAddress(DWORD procId, const char* modName)
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