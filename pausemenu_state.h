#pragma once
#include "state.h"

#include <input/sony_controller_input_manager.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include "system/platform.h"
#include <graphics/sprite.h>
#include <audio/audio_manager.h>
#include "load_texture.h"
#include <vector>

class StateManager;

class PauseMenuState : public State
{
public:
	PauseMenuState(gef::SpriteRenderer* sprite_renderer, gef::AudioManager* audio_manager, gef::Font* font, gef::Platform* platform, StateManager* state_manager);
	~PauseMenuState();

	void Update(float frame_time, const gef::SonyController* controller);
	void Render();
	void onEnter();
	void onExit();
	void Reset();

private:

	gef::Font* font_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Platform* platform_;
	StateManager* state_manager_;
	gef::AudioManager* audio_manager_;

	gef::Texture* button_icon_;
};

