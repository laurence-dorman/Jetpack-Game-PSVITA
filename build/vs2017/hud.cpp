#include "hud.h"
#include "system/debug_log.h"

#define INITIAL_WIDTH 365.f
#define INITIAL_POSITION gef::Vector4(365.f, 504.f, 0.f)

HUD::HUD()
{
	colour_.set_value(0.f, 1.f, 0.f);

	gef::Colour button_colour(colour_.x(), colour_.y(), colour_.z(), 1.f);

	fuel_bar_.set_colour(button_colour.GetABGR());
	fuel_bar_.set_position(INITIAL_POSITION);
	fuel_bar_.set_width(INITIAL_WIDTH);
	fuel_bar_.set_height(40.f);
}

HUD::~HUD()
{
}

void HUD::Update(float fuel)
{
	float time = fuel / 50.f;
	colour_.Lerp(gef::Vector4(1.0f, 0.0f, 0.0f), gef::Vector4(0.0f, 1.0f, 0.0f), time);

	fuel_bar_.set_width(INITIAL_WIDTH * time);
	fuel_bar_.set_position(gef::Vector4(INITIAL_POSITION.x() - (INITIAL_WIDTH - fuel_bar_.width()) / 2.f, INITIAL_POSITION.y(), 0.f));

	fuel_bar_.set_colour(gef::Colour(colour_.x(), colour_.y(), colour_.z()).GetABGR());

	
}

void HUD::Render(gef::SpriteRenderer* sprite_renderer, gef::Font* font)
{
	font->RenderText(
		sprite_renderer,
		gef::Vector4(100.f, 480.f, 0.f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"FUEL:");

	sprite_renderer->DrawSprite(fuel_bar_);
	
}
