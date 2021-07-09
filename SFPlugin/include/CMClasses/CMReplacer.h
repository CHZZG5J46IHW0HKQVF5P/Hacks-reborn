#pragma once
#include "map"
#include "future"

class CMReplacer
{
private:
	const char *m_Postprefix = "*";
	std::map<const char*, void*> m_Variables; // key - cstr; void* - var pointer
	std::map <const char*, std::function < std::string()>> m_ReplacementsMap;
public:
	~CMReplacer();
	void* getVariable(const char*);
	CMReplacer* addVariable(const char*, void*);
	void removeVariable(const char*);
	CMReplacer* addReplacement(const char*, std::function<std::string()>);
	void removeReplacement(const char*);
	void replace(std::string&);
};