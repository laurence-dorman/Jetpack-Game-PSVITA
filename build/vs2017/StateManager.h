#pragma once

#include "menustate.h"
#include "ingamestate.h"

class StateManager
{
public:
	StateManager();
	~StateManager();

	bool Update(float frame_time, const gef::SonyController* controller);
	void Render();
	void setState(State* state);

private:

	MenuState menu_state_;
	InGameState in_game_state_;

	State* current_state_;

};

