#include "mainmenu_state.h"
#include "system/debug_log.h"

MainMenuState::MainMenuState(gef::SpriteRenderer* sprite_renderer, gef::Font* font, gef::Platform* platform, std::vector<State*> &states) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	states_(states)
{
	button_icon_ = CreateTextureFromPNG("playstation-circle-dark-icon.png", *platform_);
}

MainMenuState::~MainMenuState()
{
	delete button_icon_;
	button_icon_ = NULL;
}

void MainMenuState::onEnter()
{
	
}

void MainMenuState::onExit()
{
	
}


State* MainMenuState::Update(float frame_time, const gef::SonyController* controller) {
	if (controller->buttons_pressed() & gef_SONY_CTRL_CIRCLE) {
		
		return states_[INGAMESTATE];
	}
	if (controller->buttons_pressed() & gef_SONY_CTRL_R2) {
		return NULL;
	}
	return this;
}

void MainMenuState::Render()
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
		"TO RESUME");


	//DrawHUD();
	sprite_renderer_->End();
}

