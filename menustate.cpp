#include "menustate.h"

MenuState::MenuState(gef::SpriteRenderer* sprite_renderer, gef::Font* font, gef::Platform* platform, std::vector<State*> &states) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	states_(states)
{
	button_icon_ = CreateTextureFromPNG("playstation-cross-dark-icon.png", *platform_);
}

MenuState::~MenuState()
{
	delete button_icon_;
	button_icon_ = NULL;
}

void MenuState::onEnter()
{
	button_icon_ = CreateTextureFromPNG("playstation-cross-dark-icon.png", *platform_);
}

void MenuState::onExit()
{
	
}


State* MenuState::Update(float frame_time, const gef::SonyController* controller) {
	if (controller->buttons_pressed() & gef_SONY_CTRL_SQUARE) {
		return states_[INGAMESTATE];
	}
	if (controller->buttons_pressed() & gef_SONY_CTRL_R2) {
		return NULL;
	}
	return this;
}

void MenuState::Render()
{
	sprite_renderer_->Begin();

	// render "PRESS" text
	font_->RenderText(
		sprite_renderer_,
		gef::Vector4(platform_->width() * 0.5f, platform_->height() * 0.5f - 64.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"PRESS");

	// Render button icon
	gef::Sprite button;
	button.set_texture(button_icon_);
	button.set_position(gef::Vector4(platform_->width() * 0.5f, platform_->height() * 0.5f, -0.99f));
	button.set_height(32.0f);
	button.set_width(32.0f);
	sprite_renderer_->DrawSprite(button);


	// render "TO START" text
	font_->RenderText(
		sprite_renderer_,
		gef::Vector4(platform_->width() * 0.5f, platform_->height() * 0.5f + 16.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"TO START");


	//DrawHUD();
	sprite_renderer_->End();
}

