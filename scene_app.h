#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <input/input_manager.h>
#include "state_manager.h"
#include "Camera.h"

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}

class State;

class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	
	bool Update(float frame_time);

	void Render();

private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();
    
	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;
	gef::InputManager* input_manager_;

	gef::SonyControllerInputManager* controller_manager_;

	StateManager* state_manager_;

	Camera* camera_;

	//
	// GAME DECLARATIONS
	//
	gef::Renderer3D* renderer_3d_;
	PrimitiveBuilder* primitive_builder_;


	// audio variables
	int sfx_id_;
	int sfx_voice_id_;

	float fps_;

};

#endif // _SCENE_APP_H
