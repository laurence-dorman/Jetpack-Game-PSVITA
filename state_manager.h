#pragma once

#include "mainmenu_state.h"
#include "ingame_state.h"
#include "pausemenu_state.h"
#include "mainsettings_state.h"
#include "howto_state.h"
#include "splash_state.h"
#include "gameover_state.h"

#include "settings.h"

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
	StateManager(gef::Platform* platform, gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d, gef::Font* font, Camera* camera, gef::AudioManager* audio_manager, Settings* settings);
	~StateManager();

	bool Update(float frame_time, const gef::SonyController* controller);
	void Render();

	enum STATE {
		MENUSTATE,
		INGAMESTATE,
		PAUSEMENUSTATE,
		HOWTOPLAYSTATE,
		SETTINGSSTATE,
		SPLASHSTATE,
		GAMEOVERSTATE,
		QUIT
	};

	State* getState(int i) { return states_[i]; };

	void setState(STATE s);
	void quit();

	// state manager will also keep the pointer to settings object, so that any state can access the settings
	Settings* settings_;

private:
	std::vector<State*> states_; // vector which holds pointers to all of the states, so we can switch between them in "setState"

	// states
	MainMenuState mainmenu_state_;
	InGameState ingame_state_;
	PauseMenuState pausemenu_state_;
	HowToState howto_state_;
	MainSettingsState mainsettings_state_;
	SplashState splash_state_;
	GameOverState gameover_state_;

	State* current_state_; // holds pointer to current state

};

