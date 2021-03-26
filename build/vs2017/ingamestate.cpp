#include "ingamestate.h"

InGameState::InGameState()
{
}

InGameState::~InGameState()
{
}

bool InGameState::Update(float frame_time)
{
	return false;
}

void InGameState::Render()
{
}

void InGameState::onEnter()
{
}

void InGameState::onExit()
{
}

const char* InGameState::getName()
{
	return name;
}
