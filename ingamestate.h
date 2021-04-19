#pragma once
#include "state.h"

#include <input/sony_controller_input_manager.h>
#include <graphics/sprite_renderer.h>
#include <graphics/renderer_3d.h>
#include "Camera.h"
#include "primitive_builder.h"
#include "Player.h"
#include <box2d/Box2D.h>
#include "game_object.h"
#include "graphics/scene.h"
#include "model_loader.h"
#include <system/debug_log.h>
#include "utilities.h"

class InGameState : public State
{
public:
	InGameState(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d, gef::Font* font, Camera* camera, gef::Platform* platform, std::vector<State*> &states);
	~InGameState();

	State* Update(float frame_time, const gef::SonyController* controller);
	void Render();
	void onEnter();
	void onExit();
	void SetupLights();
	void InitGround();
	void UpdateSimulation(float frame_time, const gef::SonyController* controller);
	void UpdateSky();

private:

	gef::Font* font_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;
	Camera* camera_;
	PrimitiveBuilder* primitive_builder_;
	gef::Platform* platform_;
	
	// create the physics world
	b2World* world_;

	// player variables
	Player* player_;

	gef::Colour sky_colour_;
	

	// ground variables
	gef::Mesh* ground_mesh_;
	GameObject ground_;
	b2Body* ground_body_;

	ModelLoader* model_loader_;
	
	std::vector<State*>& states_;
};

