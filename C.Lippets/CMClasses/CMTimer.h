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

};