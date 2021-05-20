#include "menu_element.h"

MenuElement::MenuElement(const char* text, gef::Vector4 pos, float scale, float size, gef::Platform* platform, gef::Font* font, gef::SpriteRenderer* sprite_renderer, int state, TYPE type) :
	pos_(pos),
	text_scale_(scale),
	size_(size),
	platform_(platform),
	text_(text),
	font_(font),
	sprite_renderer_(sprite_renderer),
	selected_(false),
	state_(state),
	default_text_scale_(text_scale_),
	big_text_scale_(text_scale_*1.1f),
	type_(type),
	toggle_(false),
	value_(0)
{
	setSize(size);
	
}

MenuElement::MenuElement(const char* text, gef::Vector4 pos, float scale, float size, gef::Platform* platform, gef::Font* font, gef::SpriteRenderer* sprite_renderer, TYPE type, int* slider_value, int min, int max) :
	pos_(pos),
	text_scale_(scale),
	size_(size),
	platform_(platform),
	text_(text),
	font_(font),
	sprite_renderer_(sprite_renderer),
	selected_(false),
	default_text_scale_(text_scale_),
	big_text_scale_(text_scale_ * 1.1f),
	type_(type),
	toggle_(false),
	value_(slider_value),
	min_(min),
	max_(max)
{
	setSize(size);

}

MenuElement::MenuElement(const char* text, gef::Vector4 pos, float scale, float size, gef::Platform* platform, gef::Font* font, gef::SpriteRenderer* sprite_renderer, TYPE type, bool* toggle) :
	pos_(pos),
	text_scale_(scale),
	size_(size),
	platform_(platform),
	text_(text),
	font_(font),
	sprite_renderer_(sprite_renderer),
	selected_(false),
	default_text_scale_(text_scale_),
	big_text_scale_(text_scale_ * 1.1f),
	type_(type),
	toggle_(toggle),
	value_(0)
{
	setSize(size);

}

void MenuElement::Update() // if selected, increase size and alpha
{
	if (selected_) {
		updateSprite(1.1f, 0.8f);
		text_scale_ = big_text_scale_;
	}
	else {
		updateSprite(1.0f, 0.5f);
		text_scale_ = default_text_scale_;
	}
}

void MenuElement::setSize(float size)
{
	size_ = size;

	updateSprite(size_, 0.5f);
}

void MenuElement::updateSprite(float scale, float alpha)
{
	float button_width = 500.f * scale * text_scale_;
	float button_height = button_width * 0.15f;

	gef::Colour button_colour(0.f, 0.f, 0.f, alpha);

	sprite_.set_colour(button_colour.GetABGR());
	sprite_.set_position(pos_);
	sprite_.set_width(button_width);
	sprite_.set_height(button_height);

	text_pos_ = gef::Vector4(pos_.x(), pos_.y() - (button_height / 2.5f), pos_.z(), pos_.w());
}


void MenuElement::Render()
{
	sprite_renderer_->DrawSprite(sprite_); // draw "button"

	// render button text
	font_->RenderText(
		sprite_renderer_,
		text_pos_,
		text_scale_,
		0xffffffff,
		gef::TJ_CENTRE,
		text_);

	if (type_ == TOGGLE)  // if toggle button, render state based on toggle_ pointer
	{
		font_->RenderText(
			sprite_renderer_,
			text_pos_ + gef::Vector4(float((int)strlen(text_) * 16), 0.f, 0.f),
			text_scale_,
			*toggle_ ? 0xff00ff00 : 0xff0000ff, // if true, green, else red
			gef::TJ_CENTRE,
			"[%s]", *toggle_ ? "ON" : "OFF"); // if true, "ON", else "OFF"
	}
	else if (type_ == SLIDER) 
	{
		font_->RenderText(
			sprite_renderer_,
			text_pos_ + gef::Vector4(float((int)strlen(text_) * 11), 0.f, 0.f),
			text_scale_,
			0xff00ff00,
			gef::TJ_CENTRE,
			"[%i]", *value_);
	}
}


