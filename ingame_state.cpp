#include "ingame_state.h"

#include "state_manager.h"

#define SKY_R 0.0f
#define SKY_G 0.5f
#define SKY_B 0.92f
#define SPACE_HEIGHT 500.f

InGameState::InGameState(gef::SpriteRenderer* sprite_renderer, gef::AudioManager* audio_manager, gef::Renderer3D* renderer_3d, gef::Font* font, Camera* camera, gef::Platform* platform, StateManager* state_manager) :
	sprite_renderer_(sprite_renderer),
	renderer_3d_(renderer_3d),
	font_(font),
	camera_(camera),
	world_(NULL),
	player_(NULL),
	platform_(platform),
	state_manager_(state_manager),
	audio_manager_(audio_manager)
	
{
	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(*platform_);

	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(*platform_);

	player_ = new Player(); // init player

	stars_manager_ = new StarsManager(platform_, 1000);

	particles_manager_ = new ParticleManager(platform_);
	particles_manager_->setTarget(player_);

	SetupLights();

	// initialise the physics world
	b2Vec2 gravity(0.0f, -9.81f);
	world_ = new b2World(gravity);

	player_->Init(primitive_builder_, world_, platform_, audio_manager_);

	camera_->setTarget(player_);

	sky_colour_ = gef::Colour(SKY_R, SKY_G, SKY_B, 1.0f);

	platform_->set_render_target_clear_colour(sky_colour_);

	cloud_manager_ = new CloudManager(platform);

	fuel_manager_ = new FuelManager(world_, platform, &bodies_scheduled_for_removal_);

	HUD_ = new HUD();

	InitGround();
}

InGameState::~InGameState()
{
	// destroying the physics world also destroys all the objects within it
	delete world_;
	world_ = NULL;

	delete ground_mesh_;
	ground_mesh_ = NULL;

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete stars_manager_;
	stars_manager_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete particles_manager_;
	particles_manager_ = NULL;

	delete cloud_manager_;
	cloud_manager_ = NULL;
	
	delete fuel_manager_;
	fuel_manager_ = NULL;
}

void InGameState::onEnter()
{
	
}

void InGameState::onExit()
{
	
}

void InGameState::Update(float frame_time, const gef::SonyController* controller)
{
	for (int i = 0; i < bodies_scheduled_for_removal_.size(); i++) {
		world_->DestroyBody(bodies_scheduled_for_removal_[i]);
	}

	bodies_scheduled_for_removal_.clear();

	UpdateSimulation(frame_time, controller);
	UpdateSky();

	camera_->Update(frame_time);
	particles_manager_->Update(frame_time);
	cloud_manager_->Update(frame_time);
	fuel_manager_->Update(frame_time);

	HUD_->Update(player_->getFuel(), (player_->getPosition().y / 10.f) - 0.957f);

	if (controller->buttons_pressed() & gef_SONY_CTRL_R2) {
		state_manager_->setState(StateManager::PAUSEMENUSTATE);
	}

	if (controller->buttons_pressed() & gef_SONY_CTRL_TRIANGLE) {
		fuel_manager_->spawnFuel(world_, 1, player_->getPosition());
	}
	
}

void InGameState::UpdateSimulation(float frame_time, const gef::SonyController* controller)
{
	// update physics world
	float timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	world_->Step(timeStep, velocityIterations, positionIterations);

	// update object visuals from simulation data
	player_->Update(frame_time, controller, *state_manager_->settings_->difficulty_);

	height_ = player_->getPosition().y;

	// don't have to update the ground visuals as it is static

	// collision detection
	// get the head of the contact list
	b2Contact* contact = world_->GetContactList();
	// get contact count
	int contact_count = world_->GetContactCount();

	for (int contact_num = 0; contact_num < contact_count; ++contact_num)
	{
		if (contact->IsTouching())
		{
			// get the colliding bodies
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();

			// DO COLLISION RESPONSE HERE
			Player* player = NULL;

			GameObject* gameObjectA = NULL;
			GameObject* gameObjectB = NULL;

			gameObjectA = reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);
			gameObjectB = reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);

			if (gameObjectA)
			{
				if (gameObjectA->type() == PLAYER)
				{
					player = reinterpret_cast<Player*>(bodyA->GetUserData().pointer);

					// IF BODY B EXISTS
					// CHECK IF BODY B IS TYPE FUEL
					// IF TRUE, PLAYER_->ADDFUEL(5.F);
					// DELETE FUEL OBJECT
					
				}
			}

			if (gameObjectB)
			{
				if (gameObjectB->type() == PLAYER)
				{
					player = reinterpret_cast<Player*>(bodyB->GetUserData().pointer);
				}
			}

			if (player)
			{
				
				// take damage / play sound
			}
		}

		// Get next contact point
		contact = contact->GetNext();
	}
}

void InGameState::UpdateSky()
{
	sky_colour_.r = clamp(SKY_R - (player_->getPosition().y / SPACE_HEIGHT), 0.f, SKY_R);
	sky_colour_.g = clamp(SKY_G - (player_->getPosition().y / SPACE_HEIGHT), 0.f, SKY_G);
	sky_colour_.b = clamp(SKY_B - (player_->getPosition().y / SPACE_HEIGHT), 0.f, SKY_B);

	platform_->set_render_target_clear_colour(sky_colour_);
}

void InGameState::Reset()
{
	player_->Reset();
	camera_->Reset();
	cloud_manager_->Reset();
	particles_manager_->Reset();
}

void InGameState::Render()
{
	// projection
	renderer_3d_->set_projection_matrix(camera_->getProjectionMatrix());

	// view
	renderer_3d_->set_view_matrix(camera_->getViewMatrix());

	// draw 3d geometry
	renderer_3d_->Begin();

	//draw stars
	stars_manager_->Render(sprite_renderer_, clamp(player_->getPosition().y / SPACE_HEIGHT, 0.f, 1.f));


	// draw ground
	renderer_3d_->DrawMesh(ground_);

	// draw player
	renderer_3d_->DrawMesh(*player_);

	// draw particles
	particles_manager_->Render(renderer_3d_);

	// draw fuel
	fuel_manager_->Render(renderer_3d_, player_->getPosition());

	// draw clouds
	cloud_manager_->Render(renderer_3d_, gef::Vector4(player_->getPosition().x, player_->getPosition().y, 0.f));

	renderer_3d_->End();

	
	sprite_renderer_->Begin(false);
	HUD_->Render(sprite_renderer_, font_);
	sprite_renderer_->End();

}


void InGameState::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-200.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}

void InGameState::InitGround()
{
	// ground dimensions
	gef::Vector4 ground_half_dimensions(500.0f, 2.5f, 500.0f);

	// setup the mesh for the ground
	ground_mesh_ = primitive_builder_->CreateBoxMesh(ground_half_dimensions);
	ground_.set_mesh(ground_mesh_);

	// create a physics body
	b2BodyDef body_def;
	body_def.type = b2_staticBody;
	body_def.position = b2Vec2(0.0f, 0.0f);

	ground_body_ = world_->CreateBody(&body_def);

	// create the shape
	b2PolygonShape shape;
	shape.SetAsBox(ground_half_dimensions.x(), ground_half_dimensions.y());

	// create the fixture
	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;

	// create the fixture on the rigid body
	ground_body_->CreateFixture(&fixture_def);

	// update visuals from simulation data
	ground_.UpdateFromSimulation(ground_body_);
}
