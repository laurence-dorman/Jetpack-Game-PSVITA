#pragma once
#include "state.h"
class MenuState : public State
{
public:
	MenuState();
	~MenuState();

	bool Update(float frame_time, const gef::SonyController* controller);
	void Render();
	void onEnter();
	void onExit();

private:

};

