#pragma once
#include "state.h"

#include <input/sony_controller_input_manager.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include "system/platform.h"
#include <graphics/sprite.h>
#include "load_texture.h"

#include "menu_manager.h"

#include <vector>


class MainMenuState : public State
{
public:
	MainMenuState(gef::SpriteRenderer* sprite_renderer, gef::Font* font, gef::Platform* platform, StateManager* state_manager);
	~MainMenuState();

	void Update(float frame_time, const gef::SonyController* controller);
	void Render();
	void onEnter();
	void onExit();

private:

	gef::Font* font_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Platform* platform_;
	StateManager* state_manager_;

	MenuManager* menu_manager_;

	gef::Texture* button_icon_;

};

