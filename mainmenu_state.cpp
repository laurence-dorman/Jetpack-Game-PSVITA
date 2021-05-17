#include "mainmenu_state.h"
#include "system/debug_log.h"

MainMenuState::MainMenuState(gef::SpriteRenderer* sprite_renderer, gef::Font* font, gef::Platform* platform, std::vector<State*> &states) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	states_(states)
{
	button_icon_ = CreateTextureFromPNG("playstation-circle-dark-icon.png", *platform_);

	menu_manager_ = new MenuManager(sprite_renderer_, font_, platform_, gef::Vector4(platform_->width() * 0.5f, platform_->height() * 0.35f, -1.0f));


	menu_manager_->addElement("START GAME", 70);
	menu_manager_->addElement("SETTINGS", 70);
	menu_manager_->addElement("QUIT GAME", 70);
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


State* MainMenuState::Update(float frame_time, const gef::SonyController* controller) {
	if (controller->buttons_pressed() & gef_SONY_CTRL_CIRCLE) {
		
		return states_[INGAMESTATE];
	}
	if (controller->buttons_pressed() & gef_SONY_CTRL_R2) {
		return NULL;
	}

	menu_manager_->Update(controller);

	return this;
}

void MainMenuState::Render()
{
	sprite_renderer_->Begin();

	menu_manager_->Render();
	
	sprite_renderer_->End();
}

