#include "menustate.h"

MenuState::MenuState(gef::SpriteRenderer* sprite_renderer, gef::Font* font) : 
	sprite_renderer_(sprite_renderer), 
	font_(font)
{

}

MenuState::~MenuState()
{
}

bool MenuState::Update(float frame_time, const gef::SonyController* controller) {
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
