#pragma once
#include "state.h"
class MenuState : public State
{
public:
	MenuState();
	~MenuState();

private:

	bool Update(float frame_time);
	void Render();
	void onEnter();
	void onExit();
	const char* getName();

	const char* name = "MenuState";

};

