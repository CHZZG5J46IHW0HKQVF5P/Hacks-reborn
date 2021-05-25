#include "CMClasses/CMReplacer.h"
#include "C:\Lippets\FIles\Strings.h"


CMReplacer::~CMReplacer()
{
	for (auto&& var : this->m_AdditionVaribles)
		delete var.second;
}
void* CMReplacer::getAdditionVarible(const char* key)
{
	return m_AdditionVaribles.at(key);
}

CMReplacer* CMReplacer::addAdditionVarible(const char* key, void* varPtr)
{
	m_AdditionVaribles.insert(std::make_pair(key, varPtr));
	return this;
}

void CMReplacer::removeAdditionVarible(const char* key)
{
	m_AdditionVaribles.erase(key);
}

CMReplacer* CMReplacer::addReplacement(const char* tag, std::function<std::string()> replaceer)
{
	m_ReplacemetsMap.insert(std::make_pair(tag, replaceer));
	return this;
}

void CMReplacer::removeReplacement(const char* key)
{
	m_ReplacemetsMap.erase(key);
}

void CMReplacer::replace(std::string& replaceIn)
{
	for (auto&& replacer : m_ReplacemetsMap)
	{
		char buff[100];
		memset(buff, 0, 100);
		strcat(buff, m_Postprefix);
		strcat(buff, replacer.first);
		strcat(buff, m_Postprefix);
		Lippets::Strings::replace(replaceIn, buff, replacer.second());
	}
}