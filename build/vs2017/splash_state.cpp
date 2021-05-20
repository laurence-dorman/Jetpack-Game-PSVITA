#include "splash_state.h"
#include "state_manager.h"

SplashState::SplashState(gef::SpriteRenderer* sprite_renderer, gef::AudioManager* audio_manager, gef::Font* font, gef::Platform* platform, StateManager* state_manager) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	audio_manager_(audio_manager),
	state_manager_(state_manager),
	time_(0.f),
	scale_(10.f),
	played_(false)
{
}

SplashState::~SplashState()
{
}

void SplashState::onEnter()
{
	platform_->set_render_target_clear_colour(gef::Colour(0.f, 0.f, 0.f, 1.f));
}

void SplashState::onExit()
{
	
}

void SplashState::Reset()
{
}

void SplashState::Update(float frame_time, const gef::SonyController* controller)
{
	time_ += frame_time;

	if (scale_ >= 2.f) {
		scale_ -= frame_time*10;
	}
	else if (!played_) {
		played_ = true;
		audio_manager_->PlaySample(0);
	}
	

	if (time_ >= 3.f) {
		state_manager_->setState(StateManager::MENUSTATE);
	}
}

void SplashState::Render()
{
	sprite_renderer_->Begin();

	font_->RenderText(
		sprite_renderer_,
		gef::Vector4(platform_->width() * 0.5f, platform_->height() * 0.3f, 0.f),
		scale_,
		0xffffffff,
		gef::TJ_CENTRE,
		"JETPACK");

	sprite_renderer_->End();
}


