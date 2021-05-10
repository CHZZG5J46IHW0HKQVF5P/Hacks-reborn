#pragma once
#include "map"
#include "future"

class CMReplacer
{
private:
	const char *postprefix = "*";
	std::map<const char*, void*> additionVaribles; // key - cstr; void* - var pointer
	std::map <const char*, std::function < std::string()>> replacemetsMap;
public:
	~CMReplacer();
	void* getAdditionVarible(const char*);
	CMReplacer* addAdditionVarible(const char*, void*);
	void removeAdditionVarible(const char*);
	CMReplacer* addReplacement(const char*, std::function<std::string()>);
	void removeReplacement(const char*);
	std::string replace(std::string);
};