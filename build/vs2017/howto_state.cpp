#include "howto_state.h"
#include "state_manager.h"

HowToState::HowToState(gef::SpriteRenderer* sprite_renderer, gef::AudioManager* audio_manager, gef::Font* font, gef::Platform* platform, StateManager* state_manager) :
	sprite_renderer_(sprite_renderer),
	font_(font),
	platform_(platform),
	state_manager_(state_manager),
	audio_manager_(audio_manager)
{
	menu_manager_ = new MenuManager(sprite_renderer_, font_, platform_, gef::Vector4(platform_->width() * 0.5f, platform_->height() * 0.9f, -1.0f), state_manager_, audio_manager_);

	float b_offset = 0.f;
	float b_scale = 0.75f;

	menu_manager_->addElement("BACK", b_scale, b_offset, StateManager::STATE::MENUSTATE, MenuElement::NORMAL);
}

HowToState::~HowToState()
{
	delete menu_manager_;
	menu_manager_ = NULL;
}

void HowToState::onEnter()
{
}

void HowToState::onExit()
{
}

void HowToState::Reset()
{
}

void HowToState::Update(float frame_time, const gef::SonyController* controller)
{
	menu_manager_->Update(controller);
}

void HowToState::Render()
{
	sprite_renderer_->Begin();

	menu_manager_->Render();

	font_->RenderText(
		sprite_renderer_,
		gef::Vector4(platform_->width() * 0.5f, 50.f, 1),
		1.f,
		0xffffffff,
		gef::TJ_CENTRE,
		"X TO ACTIVATE THRUSTERS"
	);

	font_->RenderText(
		sprite_renderer_,
		gef::Vector4(platform_->width() * 0.5f, 100.f, 1),
		1.f,
		0xffffffff,
		gef::TJ_CENTRE,
		"LEFT STICK TO CONTROL JETPACK"
	);

	font_->RenderText(
		sprite_renderer_,
		gef::Vector4(platform_->width() * 0.5f, 150.f, 1),
		1.f,
		0xffffffff,
		gef::TJ_CENTRE,
		"START TO PAUSE"
	);

	font_->RenderText(
		sprite_renderer_,
		gef::Vector4(platform_->width() * 0.5f, 200.f, 1),
		1.f,
		0xffffffff,
		gef::TJ_CENTRE,
		"COLLECT FUEL CANISTERS"
	);

	sprite_renderer_->End();
}


