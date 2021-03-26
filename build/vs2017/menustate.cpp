#include "menustate.h"

MenuState::MenuState()
{
}

MenuState::~MenuState()
{
}

bool MenuState::Update(float frame_time) {
	return true;
}

void MenuState::Render()
{
}

void MenuState::onEnter()
{
}

void MenuState::onExit()
{
}

const char* MenuState::getName()
{
	return name;
}
