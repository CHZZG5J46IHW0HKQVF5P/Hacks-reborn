#pragma once
#include "map"
#include "future"

class CMReplacer
{
private:
	const char *m_Postprefix = "*";
	std::map<const char*, void*> m_AdditionVaribles; // key - cstr; void* - var pointer
	std::map <const char*, std::function < std::string()>> m_ReplacemetsMap;
public:
	~CMReplacer();
	void* getAdditionVarible(const char*);
	CMReplacer* addAdditionVarible(const char*, void*);
	void removeAdditionVarible(const char*);
	CMReplacer* addReplacement(const char*, std::function<std::string()>);
	void removeReplacement(const char*);
	void replace(std::string&);
};