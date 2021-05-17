#pragma once

#include "HacksManager.h"


namespace GFuncs
{
	bool isHackWorking(const char* szHackName);
	void resortPlayersByDistance(std::vector<std::pair<int, float>>* arrPtr, bool bInvert);

	template<class T>
	bool isHackWorking()
	{
		auto&& hacks = HacksManager::getInstance()->getHacks();
		for (auto&& hack : *hacks)
		{
			auto var = dynamic_cast<T*>(std::get<IHack*>(hack));
			if (var != nullptr)
				return var->isHackWorking();
		}
		return nullptr;
	}


	template<class T>
	T* getHackPtr()
	{
		auto&& hacks = HacksManager::getInstance()->getHacks();
		for (auto&& hack : *hacks)
		{
			auto var = dynamic_cast<T*>(std::get<IHack*>(hack));
			if (var != nullptr)
				return var;
		}
		return nullptr;
	}

};