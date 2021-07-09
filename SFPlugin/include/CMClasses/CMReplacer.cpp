#include "CMClasses/CMReplacer.h"
#include "Files\Strings.h"


CMReplacer::~CMReplacer()
{
	for (auto&& var : this->m_Variables)
		delete var.second;
}
void* CMReplacer::getVariable(const char* key)
{
	return m_Variables.at(key);
}

CMReplacer* CMReplacer::addVariable(const char* key, void* varPtr)
{
	m_Variables.insert(std::make_pair(key, varPtr));
	return this;
}

void CMReplacer::removeVariable(const char* key)
{
	m_Variables.erase(key);
}

CMReplacer* CMReplacer::addReplacement(const char* tag, std::function<std::string()> replaceer)
{
	m_ReplacementsMap.insert(std::make_pair(tag, replaceer));
	return this;
}

void CMReplacer::removeReplacement(const char* key)
{
	m_ReplacementsMap.erase(key);
}

void CMReplacer::replace(std::string& replaceIn)
{
	for (auto&& replacer : m_ReplacementsMap)
	{
		char buff[100];
		memset(buff, 0, 100);
		strcat_s(buff, m_Postprefix);
		strcat_s(buff, replacer.first);
		strcat_s(buff, m_Postprefix);
		Lippets::Strings::replace(replaceIn, buff, replacer.second());
	}
}