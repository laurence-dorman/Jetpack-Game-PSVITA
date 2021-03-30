#pragma once
#include "state.h"

class InGameState : public State
{
public:
	InGameState();
	~InGameState();

	bool Update(float frame_time, const gef::SonyController* controller);
	void Render();
	void onEnter();
	void onExit();

private:
};

