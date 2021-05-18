#pragma once

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class Renderer3D;
	class SonyController;
}
class Camera;


class State
{
public:
	 State() {}
	 State(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d, gef::Font* font, Camera* camera, gef::Platform* platform) {} // 3d
	 State(gef::SpriteRenderer* sprite_renderer, gef::Font* font, gef::Platform* platform) {} // sprites
	~State() {}

	virtual void Update(float frame_time, const gef::SonyController* controller) = 0;
	virtual void Render() = 0;
	virtual void onEnter() = 0;
	virtual void onExit() = 0;

private:
	
};

