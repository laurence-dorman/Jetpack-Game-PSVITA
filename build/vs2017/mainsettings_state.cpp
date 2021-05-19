#include "mainsettings_state.h"
#include "state_manager.h"
#include <system/debug_log.h>

MainSettingsState::MainSettingsState(gef::SpriteRenderer* sprite_renderer, gef::AudioManager* audio_manager, gef::Font* font, gef::Platform* platform, StateManager* state_manager) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	state_manager_(state_manager),
	audio_manager_(audio_manager),
	master_volume_(5),
	b_music_(true),
	b_sfx_(true)
{
	menu_manager_ = new MenuManager(sprite_renderer_, font_, platform_, gef::Vector4(platform_->width() * 0.5f, platform_->height() * 0.3f, -1.0f), state_manager_, audio_manager_);

	float b_offset = 75.f;
	float b_scale = 0.75f;

	menu_manager_->addElement("MASTER VOLUME", b_scale, b_offset, StateManager::STATE::MENUSTATE, MenuElement::SLIDER, &master_volume_);
	menu_manager_->addElement("MUSIC", b_scale, b_offset, StateManager::STATE::MENUSTATE, MenuElement::TOGGLE, &b_music_);
	menu_manager_->addElement("SOUNDS", b_scale, b_offset, StateManager::STATE::MENUSTATE, MenuElement::TOGGLE, &b_sfx_);
	menu_manager_->addElement("BACK", b_scale, b_offset, StateManager::STATE::MENUSTATE, MenuElement::NORMAL);

}

MainSettingsState::~MainSettingsState()
{
	delete menu_manager_;
	menu_manager_ = NULL;
}

void MainSettingsState::onEnter()
{
	menu_manager_->Reset();
}

void MainSettingsState::onExit()
{
}

void MainSettingsState::Reset()
{
}

void MainSettingsState::Update(float frame_time, const gef::SonyController* controller)
{
	gef::DebugOut("MASTER VOLUME: %i\nMUSIC: %s\nSFX: %s\n", master_volume_, b_music_ ? "ON" : "OFF", b_sfx_ ? "ON" : "OFF");
	menu_manager_->Update(controller);
}

void MainSettingsState::Render()
{
	sprite_renderer_->Begin();

	menu_manager_->Render();

	sprite_renderer_->End();
}


