#pragma once

#include "mainmenu_state.h"
#include "ingame_state.h"

#include <vector>

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class Renderer3D;
}

class Camera;

class StateManager
{
public:
	StateManager(gef::Platform* platform, gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d, gef::Font* font, Camera* camera);
	~StateManager();

	bool Update(float frame_time, const gef::SonyController* controller);
	void Render();
	void setState(State* state);

private:
	std::vector<State*> states;

	MainMenuState mainmenu_state_;
	InGameState ingame_state_;

	State* current_state_;
	State* old_state_;
	gef::Platform* platform_;

	gef::Font* font_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;
	Camera* camera_;

};

