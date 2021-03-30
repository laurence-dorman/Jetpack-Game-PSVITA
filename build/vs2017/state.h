#pragma once

#include "input/sony_controller_input_manager.h"

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}

class State
{
public:
	 State() {}
	~State() {}

	virtual bool Update(float frame_time, const gef::SonyController* controller) = 0;
	virtual void Render() = 0;
	virtual void onEnter() = 0;
	virtual void onExit() = 0;

protected:
	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;

private:
	
};

