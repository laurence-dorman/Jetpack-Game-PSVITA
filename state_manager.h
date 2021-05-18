#pragma once

#include "mainmenu_state.h"
#include "ingame_state.h"
#include "pausemenu_state.h"

#include <vector>

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class Renderer3D;
	class AudioManager;
}

class Camera;

class StateManager
{
public:
	StateManager(gef::Platform* platform, gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d, gef::Font* font, Camera* camera, gef::AudioManager* audio_manager);
	~StateManager();

	bool Update(float frame_time, const gef::SonyController* controller);
	void Render();

	enum STATE {
		MENUSTATE = 0,
		INGAMESTATE = 1,
		PAUSEMENUSTATE = 2,
		HOWTOPLAYSTATE = 3,
		SETTINGSSTATE = 4,
		QUIT = 5,
	};

	void setState(STATE s);
	void quit();

private:
	std::vector<State*> states_;

	MainMenuState mainmenu_state_;
	InGameState ingame_state_;
	PauseMenuState pausemenu_state_;
	

	State* current_state_;
	gef::Platform* platform_;

	gef::Font* font_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;
	gef::AudioManager* audio_manager_;
	Camera* camera_;

};

