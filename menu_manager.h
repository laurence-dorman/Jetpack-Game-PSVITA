#pragma once

#include <input/sony_controller_input_manager.h>
#include "graphics/sprite_renderer.h"
#include "graphics/sprite.h"
#include "system/platform.h"
#include "graphics/font.h"
#include <audio/audio_manager.h>
#include "menu_element.h"

class StateManager;

#include <vector>

class MenuManager
{
public:
	MenuManager(gef::SpriteRenderer* sprite_renderer, gef::Font* font, gef::Platform* platform, gef::Vector4 pos, StateManager* state_manager, gef::AudioManager* audio_manager);
	~MenuManager();

	void Update(const gef::SonyController* controller);
	void Render();
	void Reset();

	void addElement(const char* text, float scale, float offset, int state, MenuElement::TYPE type);
	void addElement(const char* text, float scale, float offset, int state, MenuElement::TYPE type, int* slider_value);
	void addElement(const char* text, float scale, float offset, int state, MenuElement::TYPE type, bool* toggle);

private:
	gef::Font* font_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Platform* platform_;
	gef::Vector4 pos_;
	StateManager* state_manager_;
	gef::AudioManager* audio_manager_;

	int string_length;

	int position_;

	std::vector<MenuElement*> elements_;

};

