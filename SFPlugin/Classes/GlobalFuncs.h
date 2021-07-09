#pragma once

#include "HacksManager.h"

class HacksManager;
namespace GFuncs
{
	template<typename T>
	inline T* getHackPtr()
	{
		static const auto&& hacks = HacksManager::getInstance()->getHacks();
		for (auto&& hack : *hacks)
		{
			auto var = dynamic_cast<T*>(std::get<IHack*>(hack));
			if (var != nullptr)
				return var;
		}
		return nullptr;
	}

};