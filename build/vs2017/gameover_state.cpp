#include "gameover_state.h"
#include "state_manager.h"

GameOverState::GameOverState(gef::SpriteRenderer* sprite_renderer, gef::AudioManager* audio_manager, gef::Font* font, gef::Platform* platform, StateManager* state_manager) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	state_manager_(state_manager),
	audio_manager_(audio_manager)
{
	menu_manager_ = new MenuManager(sprite_renderer_, font_, platform_, gef::Vector4(platform_->width() * 0.5f, platform_->height() * 0.6f, -1.0f), state_manager_, audio_manager_);

	float b_offset = 75.f;
	float b_scale = 0.8f;
	
	menu_manager_->addElement("MAIN MENU", b_scale, b_offset, StateManager::STATE::MENUSTATE, MenuElement::NORMAL);
}

GameOverState::~GameOverState()
{
	delete menu_manager_;
	menu_manager_ = NULL;
}

void GameOverState::Update(float frame_time, const gef::SonyController* controller)
{
	menu_manager_->Update(controller);
}

void GameOverState::Render()
{
	sprite_renderer_->Begin();

	font_->RenderText(
		sprite_renderer_,
		gef::Vector4(platform_->width() * 0.5f, platform_->height() * 0.2f, 0.f),
		2.f,
		0xffffffff,
		gef::TJ_CENTRE,
		"GAME OVER");

	menu_manager_->Render();

	sprite_renderer_->End();
}

void GameOverState::onEnter()
{
	platform_->set_render_target_clear_colour(gef::Colour(0.1f, 0.6f, 0.7f, 1.f));
}

void GameOverState::onExit()
{
}

void GameOverState::Reset()
{
}
