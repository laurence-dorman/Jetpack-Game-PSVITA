#include "pausemenu_state.h"

#include "state_manager.h"

PauseMenuState::PauseMenuState(gef::SpriteRenderer* sprite_renderer, gef::AudioManager* audio_manager, gef::Font* font, gef::Platform* platform, StateManager* state_manager) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	state_manager_(state_manager),
	audio_manager_(audio_manager)
{
	button_icon_ = CreateTextureFromPNG("playstation-circle-dark-icon.png", *platform_);
}

PauseMenuState::~PauseMenuState()
{
	delete button_icon_;
	button_icon_ = NULL;
}

void PauseMenuState::onEnter()
{
	
}

void PauseMenuState::onExit()
{
	
}


void PauseMenuState::Update(float frame_time, const gef::SonyController* controller) {
	if (controller->buttons_pressed() & gef_SONY_CTRL_CIRCLE) {
		
		state_manager_->setState(StateManager::INGAMESTATE);
	}
	if (controller->buttons_pressed() & gef_SONY_CTRL_R2) {
		state_manager_->setState(StateManager::MENUSTATE);
	}
}

void PauseMenuState::Render()
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

