#pragma once
#include "state.h"

class InGameState : public State
{
public:
	InGameState();
	~InGameState();

private:

	bool Update(float frame_time);
	void Render();
	void onEnter();
	void onExit();
	const char* getName();

	const char* name = "InGameState";
};

