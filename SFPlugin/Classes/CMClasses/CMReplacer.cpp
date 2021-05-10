#include "CMReplacer.h"
#include "C:\Lippets\FIles\SingleFile\Strings.h"


CMReplacer::~CMReplacer()
{
	for (auto&& var : this->additionVaribles)
		delete var.second;
}
void* CMReplacer::getAdditionVarible(const char* key)
{
	return additionVaribles.at(key);
}

CMReplacer* CMReplacer::addAdditionVarible(const char* key, void* varPtr)
{
	additionVaribles.insert(std::make_pair(key, varPtr));
	return this;
}

void CMReplacer::removeAdditionVarible(const char* key)
{
	additionVaribles.erase(key);
}

CMReplacer* CMReplacer::addReplacement(const char* tag, std::function<std::string()> replaceer)
{
	replacemetsMap.insert(std::make_pair(tag, replaceer));
	return this;
}

void CMReplacer::removeReplacement(const char* key)
{
	replacemetsMap.erase(key);
}

std::string CMReplacer::replace(std::string replaceIn)
{
	for (auto&& replacer : replacemetsMap)
	{
		char buff[100];
		memset(buff, 0, 100);
		strcat(buff, postprefix);
		strcat(buff, replacer.first);
		strcat(buff, postprefix);
		Lippets::Strings::replace(replaceIn, buff, replacer.second());
	}
	return replaceIn;
}