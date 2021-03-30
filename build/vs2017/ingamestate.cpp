#include "ingamestate.h"

InGameState::InGameState(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d, gef::Font* font) :
	sprite_renderer_(sprite_renderer),
	renderer_3d_(renderer_3d),
	font_(font)
{
}

InGameState::~InGameState()
{
}

bool InGameState::Update(float frame_time, const gef::SonyController* controller)
{

	return true;
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