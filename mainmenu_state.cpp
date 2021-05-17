#include "mainmenu_state.h"
#include "system/debug_log.h"
#include "state_manager.h"

MainMenuState::MainMenuState(gef::SpriteRenderer* sprite_renderer, gef::Font* font, gef::Platform* platform, StateManager* state_manager) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	state_manager_(state_manager)
{
	button_icon_ = CreateTextureFromPNG("playstation-circle-dark-icon.png", *platform_);

	menu_manager_ = new MenuManager(sprite_renderer_, font_, platform_, gef::Vector4(platform_->width() * 0.5f, platform_->height() * 0.35f, -1.0f), state_manager_);

	int button_offset = 75.f;

	menu_manager_->addElement("START GAME", button_offset, StateManager::STATE::INGAMESTATE);
	menu_manager_->addElement("HOW TO PLAY", button_offset, StateManager::STATE::HOWTOPLAYSTATE);
	menu_manager_->addElement("SETTINGS", button_offset, StateManager::STATE::SETTINGSSTATE);
	menu_manager_->addElement("QUIT GAME", button_offset, StateManager::STATE::QUIT);
}

MainMenuState::~MainMenuState()
{
	delete button_icon_;
	button_icon_ = NULL;

	delete menu_manager_;
	menu_manager_ = NULL;
}

void MainMenuState::onEnter()
{
	
}

void MainMenuState::onExit()
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

