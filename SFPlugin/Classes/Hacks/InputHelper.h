#pragma once
#include "Hack.h"


HACK_CLASS(InputHelper)
{
public:
	InputHelper(const char* name);
private:
	CMFont font = CMFont("Chat Helper");
	int offsetY = 0;
	int offsetX = 0;
	OVERRIDE_INIT;
	void onDrawGUI() override;
	void onDrawHack( ) override;
	
	OVERRIDE_SAVE_READ;

};