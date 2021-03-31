#pragma once
#include "state.h"

#include <input/sony_controller_input_manager.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include "system/platform.h"
#include <graphics/sprite.h>
#include "load_texture.h"
#include <vector>


class MenuState : public State
{
public:
	MenuState(gef::SpriteRenderer* sprite_renderer, gef::Font* font, gef::Platform* platform, std::vector<State*> &states);
	~MenuState();

	State* Update(float frame_time, const gef::SonyController* controller);
	void Render();
	void onEnter();
	void onExit();

private:

	gef::Font* font_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Platform* platform_;

	//
	// FRONTEND DECLARATIONS
	//
	gef::Texture* button_icon_;

	std::vector<State*> &states_;
};

