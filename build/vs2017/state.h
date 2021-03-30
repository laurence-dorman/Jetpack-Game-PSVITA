#pragma once

#include "input/sony_controller_input_manager.h"

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class SpriteRenderer;
	class Font;
	class Renderer3D;
}


class State
{
public:
	 State() {}
	 State(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d, gef::Font* font) {}
	 State(gef::SpriteRenderer* sprite_renderer, gef::Font* font) {}
	~State() {}

	virtual bool Update(float frame_time, const gef::SonyController* controller) = 0;
	virtual void Render() = 0;
	virtual void onEnter() = 0;
	virtual void onExit() = 0;

private:
	
};

