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
	enum TYPE {
		NORMAL, TOGGLE, SLIDER
	};

	MenuElement(const char* text, gef::Vector4 pos, float scale, float size, gef::Platform* platform, gef::Font* font, gef::SpriteRenderer* sprite_renderer, int state, TYPE type);
	MenuElement(const char* text, gef::Vector4 pos, float scale, float size, gef::Platform* platform, gef::Font* font, gef::SpriteRenderer* sprite_renderer, TYPE type, int* slider_value);
	MenuElement(const char* text, gef::Vector4 pos, float scale, float size, gef::Platform* platform, gef::Font* font, gef::SpriteRenderer* sprite_renderer, TYPE type, bool* toggle);

	void Render();
	void Update();
	void setSize(float size);

	void setSelected(bool b) { selected_ = b; };

	int getState() { return state_; };

	TYPE getType() { return type_; };

	void addValue(int i) { *value_ += i; if (*value_ < 0) *value_ = 0; if (*value_ > 10) *value_ = 10; };

	void Toggle() { *toggle_ ? *toggle_ = false : *toggle_ = true; };

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

	int* value_;
	bool* toggle_;

	TYPE type_;
};

