#include "menu_manager.h"

MenuManager::MenuManager(gef::SpriteRenderer* sprite_renderer, gef::Font* font, gef::Platform* platform, gef::Vector4 pos) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	pos_(pos),
	string_length(0),
	position_(0)
{

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
		elements_[position_]->setSelected(false);

		 position_ < elements_.size() - 1 ? position_++ : position_ = 0;

		elements_[position_]->setSelected(true);
	}
	if (controller->buttons_pressed() & gef_SONY_CTRL_UP) {
		elements_[position_]->setSelected(false);

		position_ > 0 ? position_-- : position_ = elements_.size() - 1;

		elements_[position_]->setSelected(true);
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

void MenuManager::addElement(const char* text, float offset)
{
	if (strlen(text) > string_length) {
		string_length = strlen(text);

		for (auto e: elements_) {
			e->setSize(string_length);
		}
	}

	float position_y = pos_.y() + (elements_.size() * offset);

	MenuElement* element = new MenuElement(text, gef::Vector4(pos_.x(), position_y, pos_.z(), pos_.w()), string_length, platform_, font_, sprite_renderer_);

	if (elements_.empty()) {
		element->setSelected(true);
	}

	elements_.push_back(element);
}
