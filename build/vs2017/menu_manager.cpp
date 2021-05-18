#include "menu_manager.h"
#include "state_manager.h"

MenuManager::MenuManager(gef::SpriteRenderer* sprite_renderer, gef::Font* font, gef::Platform* platform, gef::Vector4 pos, StateManager* state_manager, gef::AudioManager* audio_manager) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	pos_(pos),
	string_length(0),
	position_(0),
	state_manager_(state_manager),
	audio_manager_(audio_manager)
{
	audio_manager_->LoadSample("menu_moved.wav", *platform_);
	audio_manager_->LoadSample("menu_select.wav", *platform_);
}

MenuManager::~MenuManager()
{
	for (auto e : elements_) {
		delete e;
	}
	elements_.clear();
}

void MenuManager::Update(const gef::SonyController* controller)
{
	if (controller->buttons_pressed() & gef_SONY_CTRL_DOWN) {
		
		audio_manager_->PlaySample(0, 0);
		elements_[position_]->setSelected(false);

		 position_ < elements_.size() - 1 ? position_++ : position_ = 0;

		elements_[position_]->setSelected(true);
	}
	if (controller->buttons_pressed() & gef_SONY_CTRL_UP) {
		audio_manager_->PlaySample(0, 0);
		elements_[position_]->setSelected(false);

		position_ > 0 ? position_-- : position_ = elements_.size() - 1;

		elements_[position_]->setSelected(true);
	}

	if (controller->buttons_pressed() & gef_SONY_CTRL_SQUARE) {
		if (elements_[position_]->getState() == StateManager::QUIT) {
			state_manager_->quit();
			return;
		}
		audio_manager_->PlaySample(1, 0);
		state_manager_->setState(static_cast<StateManager::STATE>(elements_[position_]->getState()));
	}
	
	for (auto e : elements_) {
		e->Update();
	}
	

}

void MenuManager::Render()
{
	for (auto e : elements_) {
		e->Render();
	}
}

void MenuManager::addElement(const char* text, float offset, int state)
{
	if (strlen(text) > string_length) {
		string_length = strlen(text);

		for (auto e: elements_) {
			e->setSize(string_length);
		}
	}

	float position_y = pos_.y() + (elements_.size() * offset);

	MenuElement* element = new MenuElement(text, gef::Vector4(pos_.x(), position_y, pos_.z(), pos_.w()), string_length, platform_, font_, sprite_renderer_, state);

	if (elements_.empty()) {
		element->setSelected(true);
	}

	elements_.push_back(element);
}
