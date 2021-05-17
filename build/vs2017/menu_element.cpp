#include "menu_element.h"

MenuElement::MenuElement(const char* text, gef::Vector4 pos, float size, gef::Platform* platform, gef::Font* font, gef::SpriteRenderer* sprite_renderer) :
	pos_(pos),
	size_(size),
	platform_(platform),
	text_(text),
	font_(font),
	sprite_renderer_(sprite_renderer),
	selected_(false)
{
	setSize(size);
}

void MenuElement::Update()
{
	if (selected_) {
		updateSprite(1.2f, 0.8f);
	}
	else {
		updateSprite(1.0f, 0.5f);
	}
}

void MenuElement::setSize(float size)
{
	size_ = size;

	updateSprite(1.0f, 0.5f);
}

void MenuElement::updateSprite(float scale, float alpha)
{
	float button_width = size_ * 40.f * scale;
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
	sprite_renderer_->DrawSprite(sprite_);

	font_->RenderText(
		sprite_renderer_,
		text_pos_,
		1.f,
		0xffffffff,
		gef::TJ_CENTRE,
		text_);
}


