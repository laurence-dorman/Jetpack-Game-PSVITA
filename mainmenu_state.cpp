#include "mainmenu_state.h"
#include "state_manager.h"

MainMenuState::MainMenuState(gef::SpriteRenderer* sprite_renderer, gef::AudioManager* audio_manager, gef::Font* font, gef::Platform* platform, StateManager* state_manager) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	state_manager_(state_manager),
	audio_manager_(audio_manager)
{

	menu_manager_ = new MenuManager(sprite_renderer_, font_, platform_, gef::Vector4(platform_->width() * 0.5f, platform_->height() * 0.3f, -1.0f), state_manager_, audio_manager_);

	float b_offset = 75.f;
	float b_scale = 0.8f;

	menu_manager_->addElement("START GAME", b_scale, b_offset, StateManager::STATE::INGAMESTATE, MenuElement::NORMAL);
	menu_manager_->addElement("HOW TO PLAY", b_scale, b_offset, StateManager::STATE::HOWTOPLAYSTATE, MenuElement::NORMAL);
	menu_manager_->addElement("SETTINGS", b_scale, b_offset, StateManager::STATE::SETTINGSSTATE, MenuElement::NORMAL);
	menu_manager_->addElement("QUIT GAME", b_scale, b_offset, StateManager::STATE::QUIT, MenuElement::NORMAL);
}

MainMenuState::~MainMenuState()
{
	delete menu_manager_;
	menu_manager_ = NULL;
}

void MainMenuState::onEnter()
{
	platform_->set_render_target_clear_colour(gef::Colour(0.1f, 0.6f, 0.7f, 1.f));
	
}

void MainMenuState::onExit()
{
	state_manager_->getState(StateManager::STATE::INGAMESTATE)->Reset();
}

void MainMenuState::Reset()
{
}


void MainMenuState::Update(float frame_time, const gef::SonyController* controller) {

	if (controller->buttons_pressed() & gef_SONY_CTRL_R2) {
		state_manager_->quit();
	}
	
	menu_manager_->Update(controller);

}

void MainMenuState::Render()
{
	sprite_renderer_->Begin();

	menu_manager_->Render();
	
	sprite_renderer_->End();
}

