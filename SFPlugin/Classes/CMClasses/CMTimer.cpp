#include "CMTimer.h"

bool CMTimer::isEnded()
{
	return GetTickCount() > dwTimerValue;
}

void CMTimer::setTimer(DWORD nowTimeOffset)
{
	dwTimerValue = GetTickCount() + nowTimeOffset;
}

DWORD CMTimer::getElapsedTime()
{
	return GetTickCount() - dwTimerValue;
}

void CMTimer::reset()
{
	dwTimerValue = 0;
}