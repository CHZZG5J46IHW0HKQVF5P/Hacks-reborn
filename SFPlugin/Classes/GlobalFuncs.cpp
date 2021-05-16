#include "GlobalFuncs.h"


bool GFuncs::isHackWorking(const char* szHackName)
{
	auto&& hacks = HacksManager::getInstance()->getHacks();
	for (auto&& hack : *hacks)
		if (std::get<IHack*>(hack)->m_sHackName == szHackName)
			return std::get<IHack*>(hack)->isHackWorking();


	return false;
}

void GFuncs::resortPlayersByDistance(std::deque<std::pair<int, float>>* toSort, bool bInvert)
{
	if (bInvert)
		std::sort(toSort->begin(), toSort->end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b)
	{
		return (a.second > b.second);
	});
	else
		std::sort(toSort->begin(), toSort->end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b)
	{
		return (a.second < b.second);
	});
}



