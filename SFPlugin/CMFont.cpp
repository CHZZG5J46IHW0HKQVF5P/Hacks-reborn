#include "CMFont.h"

CMFont::CMFont(const char* thisname)
{
	strcpy_s(name, thisname);
}
void CMFont::Init(char* szFontName, int size, DWORD flags)
{
	if (f == nullptr)
		f = SF->getRender()->CreateNewFont(szFontName, size, 13);//flags);
}
void CMFont::Init()
{
	if (f == nullptr)
		f = SF->getRender()->CreateNewFont(FontName, FontSize, 13);//Flags);
}
void CMFont::Release()
{
	if (f != nullptr)
	{
		SF->getRender()->ReleaseFont(f);
		f = nullptr;
	}
}
void CMFont::ReInit()
{
	Release();
	Init();
}
void CMFont::save(Json::Value &data)
{
	data["Fonts"][name]["FontName"] = FontName;
	data["Fonts"][name]["FontSize"] = FontSize;
}
void CMFont::read(Json::Value &data)
{
	strcpy(FontName, data["Fonts"][name]["FontName"].asCString());
	FontSize = data["Fonts"][name]["FontSize"].asInt();

}