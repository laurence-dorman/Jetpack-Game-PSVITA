#pragma once

#include <input/sony_controller_input_manager.h>
#include "graphics/sprite_renderer.h"
#include "graphics/sprite.h"
#include "system/platform.h"
#include "graphics/font.h"
#include "menu_element.h"

#include <vector>

class MenuManager
{
public:
	MenuManager(gef::SpriteRenderer* sprite_renderer, gef::Font* font, gef::Platform* platform, gef::Vector4 pos);
	~MenuManager();

	void Update(const gef::SonyController* controller);
	void Render();

	void addElement(const char* text, float size);

private:
	gef::Font* font_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Platform* platform_;
	gef::Vector4 pos_;

	int string_length;

	int position_;

	std::vector<MenuElement*> elements_;

};

