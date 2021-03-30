#pragma once
#include "state.h"

class MenuState : public State
{
public:
	MenuState(gef::SpriteRenderer* sprite_renderer, gef::Font* font);
	~MenuState();

	bool Update(float frame_time, const gef::SonyController* controller);
	void Render();
	void onEnter();
	void onExit();

private:

	gef::Font* font_;
	gef::SpriteRenderer* sprite_renderer_;
};

