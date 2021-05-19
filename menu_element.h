#pragma once

#include "graphics/sprite_renderer.h"
#include "graphics/sprite.h"
#include "graphics/colour.h"
#include "graphics/font.h"
#include "system/platform.h"

#include "state.h"
#include <string>


class MenuElement
{
public:
	MenuElement(const char* text, gef::Vector4 pos, float scale, float size, gef::Platform* platform, gef::Font* font, gef::SpriteRenderer* sprite_renderer, int state);

	void Render();
	void Update();
	void setSize(float size);

	void setSelected(bool b) { selected_ = b; };

	int getState() { return state_; };

private:
	void updateSprite(float scale, float alpha);

	gef::Vector4 pos_;
	gef::Vector4 text_pos_;
	gef::Sprite sprite_;
	gef::Platform* platform_;
	gef::Font* font_;
	gef::SpriteRenderer* sprite_renderer_;

	int state_;

	const char* text_;
	float size_;
	float text_scale_;
	float default_text_scale_;
	float big_text_scale_;

	bool selected_;
};

