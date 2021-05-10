#pragma once
#include "windows.h"

class CMTimer
{
private:
	DWORD dwTimerValue = 0;
public:

	bool isEnded();
	void setTimer(DWORD);
	void reset();
	DWORD getElapsedTime();		 
};