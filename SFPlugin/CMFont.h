#pragma once

class CMFont
{
public:
	char name[32] = { '0' };
	char FontName[64] = { '0' };
	int FontSize = 0;
	stFontInfo* f = nullptr;
	CMFont(const char* thisname)
	{
		strcpy_s(name, thisname);
	}
	void Init(char* szFontName, int size, DWORD flags)
	{
		if (f == nullptr)
			f = SF->getRender()->CreateNewFont(szFontName, size, 13);//flags);
	}
	void Init()
	{
		if (f == nullptr)
			f = SF->getRender()->CreateNewFont(FontName, FontSize, 13);//Flags);
	}
	void Release()
	{
		if (f != nullptr)
		{
			SF->getRender()->ReleaseFont(f);
			f = nullptr;
		}
	}
	void ReInit()
	{
		Release();
		Init();
	}
	void save(Json::Value &data)
	{
		data["Fonts"][name]["FontName"] = FontName;
		data["Fonts"][name]["FontSize"] = FontSize;
	}
	void read(Json::Value &data)
	{
		strcpy(FontName, data["Fonts"][name]["FontName"].asCString());
		FontSize = data["Fonts"][name]["FontSize"].asInt();

	}
};