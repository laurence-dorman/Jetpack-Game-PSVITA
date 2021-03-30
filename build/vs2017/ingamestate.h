#pragma once
#include "state.h"

class InGameState : public State
{
public:
	InGameState(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d, gef::Font* font);
	~InGameState();

	bool Update(float frame_time, const gef::SonyController* controller);
	void Render();
	void onEnter();
	void onExit();

private:

	gef::Font* font_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;
};

