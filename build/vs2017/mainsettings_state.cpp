#include "mainsettings_state.h"
#include "state_manager.h"

MainSettingsState::MainSettingsState(gef::SpriteRenderer* sprite_renderer, gef::AudioManager* audio_manager, gef::Font* font, gef::Platform* platform, StateManager* state_manager, Settings* settings) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	state_manager_(state_manager),
	audio_manager_(audio_manager),
	settings_(settings)
{
	menu_manager_ = new MenuManager(sprite_renderer_, font_, platform_, gef::Vector4(platform_->width() * 0.5f, platform_->height() * 0.3f, -1.0f), state_manager_, audio_manager_);

	float b_offset = 75.f;
	float b_scale = 0.75f;

	menu_manager_->addElement("MASTER VOLUME", b_scale, b_offset, MenuElement::SLIDER, settings_->master_volume_);
	menu_manager_->addElement("MUSIC", b_scale, b_offset, MenuElement::TOGGLE, settings_->b_music_);
	menu_manager_->addElement("SND FX", b_scale, b_offset, MenuElement::TOGGLE, settings_->b_sfx_);
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

	menu_manager_->Update(controller);

	audio_manager_->SetMasterVolume(float(*settings_->master_volume_ * 10));

	gef::VolumeInfo music_volume_info;
	music_volume_info.volume = *settings_->b_music_ ? 100.f : 0.f;

	audio_manager_->SetMusicVolumeInfo(music_volume_info);

	gef::VolumeInfo sfx_volume_info;
	sfx_volume_info.volume = *settings_->b_sfx_ ? 100.f : 0.f;

	audio_manager_->SetSampleVoiceVolumeInfo(0, sfx_volume_info);
	audio_manager_->SetSampleVoiceVolumeInfo(1, sfx_volume_info);
	audio_manager_->SetSampleVoiceVolumeInfo(2, sfx_volume_info);
}

void MainSettingsState::Render()
{
	sprite_renderer_->Begin();

	menu_manager_->Render();

	sprite_renderer_->End();
}


