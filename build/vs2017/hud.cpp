#include "hud.h"
#include "system/debug_log.h"

#define INITIAL_WIDTH 365.f
#define INITIAL_POSITION gef::Vector4(365.f, 504.f, 0.f)
#define PLAYER_MAX_FUEL 30.f

HUD::HUD() :
	best_height_(0.f)
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

void HUD::Update(float fuel, float height)
{
	if (height > best_height_) { best_height_ = height; }; // update best_height_

	float time = fuel / PLAYER_MAX_FUEL; // normalise
	colour_.Lerp(gef::Vector4(1.0f, 0.0f, 0.0f), gef::Vector4(0.0f, 1.0f, 0.0f), time); // lerp between red and greed based on time (normalised fuel)

	fuel_bar_.set_width(INITIAL_WIDTH * time); // set width based on time (normalised fuel)
	fuel_bar_.set_position(gef::Vector4(INITIAL_POSITION.x() - (INITIAL_WIDTH - fuel_bar_.width()) / 2.f, INITIAL_POSITION.y(), 0.f)); // retain position after adjusting width

	fuel_bar_.set_colour(gef::Colour(colour_.x(), colour_.y(), colour_.z()).GetABGR()); // set colour from colour_ vector4 that we calculated
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

	font->RenderText(
		sprite_renderer,
		gef::Vector4(905.f, 480.f, 0.f),
		1.0f,
		0xffffffff,
		gef::TJ_RIGHT,
		"BEST HEIGHT: %.2fm", best_height_);
	
}
