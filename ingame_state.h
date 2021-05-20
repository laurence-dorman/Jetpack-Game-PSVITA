#pragma once
#include "state.h"

#include <input/sony_controller_input_manager.h>
#include <graphics/sprite_renderer.h>
#include <graphics/renderer_3d.h>
#include "camera.h"
#include "primitive_builder.h"
#include "Player.h"
#include <box2d/Box2D.h>
#include "game_object.h"
#include "graphics/scene.h"
#include <audio/audio_manager.h>
#include "model_loader.h"
#include <system/debug_log.h>
#include "utilities.h"
#include "stars_manager.h"
#include "particle_manager.h"
#include "cloud_manager.h"
#include "fuel_manager.h"
#include "hud.h"

#include <vector>

class StateManager;

class InGameState : public State
{
public:
	InGameState(gef::SpriteRenderer* sprite_renderer, gef::AudioManager* audio_manager, gef::Renderer3D* renderer_3d, gef::Font* font, Camera* camera, gef::Platform* platform, StateManager* state_manager);
	~InGameState();

	void Update(float frame_time, const gef::SonyController* controller);
	void Render();
	void onEnter();
	void onExit();
	void SetupLights();
	void InitGround();
	void UpdateSimulation(float frame_time, const gef::SonyController* controller);
	void UpdateSky();
	void Reset();

private:

	gef::Font* font_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;
	Camera* camera_;
	PrimitiveBuilder* primitive_builder_;
	gef::Platform* platform_;
	StateManager* state_manager_;
	gef::AudioManager* audio_manager_;
	FuelManager* fuel_manager_;

	HUD* HUD_;
	
	// create the physics world
	b2World* world_;

	// player variables
	Player* player_;

	float height_;

	gef::Colour sky_colour_;

	CloudManager* cloud_manager_;
	
	StarsManager* stars_manager_;
	ParticleManager* particles_manager_;

	// ground variables
	gef::Mesh* ground_mesh_;
	GameObject ground_;
	b2Body* ground_body_;

	ModelLoader* model_loader_;

	std::vector<b2Body*> bodies_scheduled_for_removal_;

	float death_timer_;
	
};

