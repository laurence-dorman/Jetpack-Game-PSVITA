#pragma once

#include "menustate.h"
#include "ingamestate.h"

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

	MenuState menu_state_;
	InGameState in_game_state_;

	State* current_state_;
	gef::Platform* platform_;

	gef::Font* font_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;
	Camera* camera_;

};

