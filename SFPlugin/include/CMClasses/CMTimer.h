#pragma once
#include "windows.h"

class CMTimer
{
public:
	DWORD dwTimerValue = 0;
	bool isEnded();
	void setTimer(DWORD);
	void reset();
	DWORD getElapsedTime();
	bool wasReseted();

};

bool inline CMTimer::isEnded()
{
	return GetTickCount() > dwTimerValue;
}

bool inline CMTimer::wasReseted()
{
	return dwTimerValue == 0;
}

void inline CMTimer::setTimer(DWORD nowTimeOffset)
{
	dwTimerValue = GetTickCount() + nowTimeOffset;
}

DWORD inline CMTimer::getElapsedTime()
{
	return GetTickCount() - dwTimerValue;
}

void inline CMTimer::reset()
{
	dwTimerValue = 0;
}