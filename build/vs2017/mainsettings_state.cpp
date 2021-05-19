#include "mainsettings_state.h"
#include "state_manager.h"

MainSettingsState::MainSettingsState(gef::SpriteRenderer* sprite_renderer, gef::AudioManager* audio_manager, gef::Font* font, gef::Platform* platform, StateManager* state_manager) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	state_manager_(state_manager),
	audio_manager_(audio_manager)
{
	menu_manager_ = new MenuManager(sprite_renderer_, font_, platform_, gef::Vector4(platform_->width() * 0.5f, platform_->height() * 0.9f, -1.0f), state_manager_, audio_manager_);

	float b_offset = 75.f;
	float b_scale = 0.75f;

	menu_manager_->addElement("BACK", b_scale, b_offset, StateManager::STATE::MENUSTATE);

}

MainSettingsState::~MainSettingsState()
{
	delete menu_manager_;
	menu_manager_ = NULL;
}

void MainSettingsState::onEnter()
{
}

void MainSettingsState::onExit()
{
}

void MainSettingsState::Update(float frame_time, const gef::SonyController* controller)
{
	menu_manager_->Update(controller);
}

void MainSettingsState::Render()
{
	sprite_renderer_->Begin();

	menu_manager_->Render();

	sprite_renderer_->End();
}


